#include "LevelScene.h"
#include "Scene.h"
#include "GameEngine.h"
#include "Physics.h"

// all Level based stuff
Level::Level(const std::string name, GameEngine* gameEngine, const std::string fileName)
	: Scene(name, gameEngine), m_fileName(fileName) {
	init();
}

void Level::regInputs()
{
	//movement
	registerAction(Action{ sf::Keyboard::A });
	registerAction(Action{ sf::Keyboard::D });
	registerAction(Action{ sf::Keyboard::W });

	// DEBUG
	registerAction(Action{ sf::Keyboard::T });
	registerAction(Action{ sf::Keyboard::C });
	registerAction(Action{ sf::Keyboard::G });

	//menu
	registerAction(Action{ sf::Keyboard::Escape });
}

void Level::init()
{
	showGrid = false;
	deltaTime = 1.f / 60.f;

	regInputs();

	initGrid();
	initLevel();
	initPlayer();
}

void Level::initGrid()
{
	auto x_size = m_gameEngine->window()->getSize().x;
	auto y_size = m_gameEngine->window()->getSize().y;

	unsigned pos_y = 0;
	unsigned pos_x = 0;

	for (unsigned collumn{ 0 }; collumn < x_size; collumn += 64) {
		
		for (unsigned row{ 0 }; row < y_size; row += 64) {

			auto gridEnt = m_entManager.addEntity(TAG::GRID);

			gridEnt->addComponent<CBoundingBox>(sf::Vector2f{ 64, 64 });
			gridEnt->getComponent<CBoundingBox>().b_shape.setPosition(collumn, row);

			gridEnt->addComponent<CText>("( " + std::to_string(pos_x) + " , " + std::to_string(pos_y) + " )",
				m_gameEngine->getAssets().getFont("Grid"), 15);
			auto& b_pos = gridEnt->getComponent<CBoundingBox>().b_shape.getPosition();
			gridEnt->getComponent<CText>().text.setPosition(b_pos.x + 5.f, b_pos.y + 5.f);
			pos_y++;

		}
		pos_y = 0;
		pos_x++;
	}
}

void Level::initLevel()
{
	// Level will be created using .txt file
	auto ent = m_entManager.addEntity(TAG::TILE);

	ent->addComponent<CBoundingBox>(sf::Vector2f{ 704.f, 64.f });
	ent->getComponent<CBoundingBox>().b_shape.setPosition(sf::Vector2f{ 64.f, 64.f * 7 });

	auto ent2 = m_entManager.addEntity(TAG::TILE);

	ent2->addComponent<CBoundingBox>(sf::Vector2f{ 640.f, 64.f });
	ent2->getComponent<CBoundingBox>().b_shape.setPosition(sf::Vector2f{ 64.f, 64.f * 4 });

	auto ent3 = m_entManager.addEntity(TAG::TILE);

	ent3->addComponent<CBoundingBox>(sf::Vector2f{ 128.f, 64.f });
	ent3->getComponent<CBoundingBox>().b_shape.setPosition(sf::Vector2f{ 64.f * 12, 64.f * 6 });

}

void Level::initPlayer()
{
	m_player = m_entManager.addEntity(TAG::PLAYER);

	m_player->addComponent<CBoundingBox>(sf::Vector2f{ 32.f, 32.f });
	m_player->getComponent<CBoundingBox>().b_shape.setPosition(sf::Vector2f{ 64.f * 2, 64.f * 6 });
	m_player->addComponent<CInput>();
	m_player->addComponent<CTransformable>();
	
	m_player->getComponent<CTransformable>().speedLimit = 0.9f;
	m_player->getComponent<CTransformable>().speed = sf::Vector2f{ 0.f,0.f };
}

void Level::renderGrid(sf::RenderTarget& target)
{
	for (auto& ent : m_entManager.getAllByTag(TAG::GRID)) {
		target.draw(ent->getComponent<CBoundingBox>().b_shape);
		target.draw(ent->getComponent<CText>().text);
	}
}

void Level::renderLevel(sf::RenderTarget& target)
{
	for (auto& ent : m_entManager.getAllByTag(TAG::TILE)) {

		target.draw(ent->getComponent<CBoundingBox>().b_shape);

	}

}

void Level::renderPlayer(sf::RenderTarget& target)
{
	target.draw(m_player->getComponent<CBoundingBox>().b_shape);
}

void Level::updatePlayerSpeed()
{
	if (m_player->getComponent<CTransformable>().onGround) {
		m_player->getComponent<CTransformable>().speed.y = 0.f;
	}

	//speed on x side

	float& p_speedX = m_player->getComponent<CTransformable>().speed.x;
	float& p_speedY = m_player->getComponent<CTransformable>().speed.y;

	if (m_player->getComponent<CInput>().RIGHT) {

		p_speedX += 2.5f * deltaTime;
		if (p_speedX > m_player->getComponent<CTransformable>().speedLimit) {
			p_speedX = m_player->getComponent<CTransformable>().speedLimit;
		}

	}

	if (m_player->getComponent<CInput>().LEFT) {

		p_speedX += -2.5f * deltaTime ;

		if (p_speedX < -m_player->getComponent<CTransformable>().speedLimit) {

			p_speedX = -m_player->getComponent<CTransformable>().speedLimit;
		}

	}

	else {
		if (p_speedX > 0) {
			p_speedX -= 1.f * deltaTime;
			if (p_speedX <= 0) {
				p_speedX = 0;
			}
		}

		else if (p_speedX < 0) {

			p_speedX += 1.f * deltaTime;
			if (p_speedX >= 0) {
				p_speedX = 0;
			}

		}

	}

	// update gravity


	if (m_player->getComponent<CInput>().UP && m_player->getComponent<CTransformable>().onGround) {
		m_player->getComponent<CTransformable>().onGround = false;
		p_speedY = -125.f * deltaTime;
	}
	else if(!m_player->getComponent<CTransformable>().onGround){
		p_speedY += 9.8f * deltaTime;
	}

}

void Level::updatePlayerInput(Action action)
{

	if (action.keyCode() == sf::Keyboard::D) {
		m_player->getComponent<CInput>().RIGHT = action.status();
		
	}
	else if (action.keyCode() == sf::Keyboard::A) {
		m_player->getComponent<CInput>().LEFT = action.status();
	}
	
	if (action.keyCode() == sf::Keyboard::W) {
		m_player->getComponent<CInput>().UP = action.status();
		
	}

}

void Level::updateCollision()
{

	for (auto& e : m_entManager.getAllByTag(TAG::TILE)) {

		if (Physics::isColliding(m_player->getComponent<CBoundingBox>().b_shape, e->getComponent<CBoundingBox>().b_shape)) {

			auto& ent_player = m_player->getComponent<CBoundingBox>().b_shape;

			auto& ent_shape = e->getComponent<CBoundingBox>().b_shape;

			float offset_y = Physics::getVertSquare(ent_player, ent_shape);

			if (offset_y < 0.f && !m_player->getComponent<CTransformable>().onGround) {
					
				std::cout << "CALL JUMP COLLISION\n";

				sf::Vector2f newPos{ ent_player.getPosition().x, ent_shape.getPosition().y + ent_shape.getGlobalBounds().height };

				m_player->getComponent<CBoundingBox>().b_shape.setPosition(newPos);

				m_player->getComponent<CTransformable>().speed.y = 9.8 * deltaTime;

				m_player->getComponent<CTransformable>().onGround = false;
			}
			else if (offset_y > 0.f){

				std::cout << "CALL GROUND COLLISION\n";

				sf::Vector2f newPos{ ent_player.getPosition().x, ent_shape.getPosition().y - ent_player.getGlobalBounds().height };
				m_player->getComponent<CBoundingBox>().b_shape.setPosition(newPos);
				m_player->getComponent<CTransformable>().speed.y = 0;

				m_player->getComponent<CTransformable>().onGround = true;

			}
					
		}

	}

}

void Level::sDoAction(Action action)
{

	if (action.keyCode() == sf::Keyboard::Escape && action.status()) {

		m_gameEngine->ChangeScene("MainMenu");
		m_keys.clear();
		return;
	}

	if (action.keyCode() == sf::Keyboard::G && action.status()) {

		showGrid = !showGrid;
	}

	updatePlayerInput(action);
	

	m_player->getComponent<CBoundingBox>().b_shape.move(m_player->getComponent<CTransformable>().speed);

}

void Level::sRender(sf::RenderTarget& target)
{
	if (showGrid) {
		renderGrid(target);
	}
	renderLevel(target);
	renderPlayer(target);
}

void Level::update()
{
	for (auto& action : m_keys)
	{
		if (m_keys.size() == 0) {
			return;
		}
		sDoAction(action);
		if (action.keyCode() == sf::Keyboard::G) {

			action.setStatus(false);
		}
		
	}
	
	if (m_keys.size() != 0) {

		updatePlayerSpeed();

		updateCollision();

	}



}
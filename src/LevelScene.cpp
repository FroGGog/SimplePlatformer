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

	for (unsigned collumn{ 0 }; collumn < x_size; collumn += 32) {
		
		for (unsigned row{ 0 }; row < y_size; row += 32) {

			auto gridEnt = m_entManager.addEntity(TAG::GRID);

			gridEnt->addComponent<CBoundingBox>(sf::Vector2f{ 32, 32 });
			gridEnt->getComponent<CBoundingBox>().b_shape.setPosition(collumn, row);

			gridEnt->addComponent<CText>("( " + std::to_string(pos_x) + " , " + std::to_string(pos_y) + " )",
				m_gameEngine->getAssets().getFont("Grid"), 7);
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

	for (int j{ 0 }; j < 2; j++) {

		for (int i{ 0 }; i < 32; i++) {

			auto ent = m_entManager.addEntity(TAG::TILE);

			ent->addComponent<CBoundingBox>(sf::Vector2f{ 32.f, 32.f });
			ent->addComponent<CSprite>(m_gameEngine->getAssets().getTexture("Brick"), sf::Vector2f{ 2.f,2.f });

			ent->getComponent<CBoundingBox>().b_shape.setPosition(sf::Vector2f{ 32.f * i, 32.f * (18.f + (float)j) });

			ent->getComponent<CBoundingBox>().updateCenter();

			ent->getComponent<CSprite>().m_sprite.setPosition(ent->getComponent<CBoundingBox>().center.x, ent->getComponent<CBoundingBox>().center.y - 1.f);

		}

	}

	for (int i{ 0 }; i < 6; i++) {

		auto ent = m_entManager.addEntity(TAG::TILE);

		ent->addComponent<CBoundingBox>(sf::Vector2f{ 32.f, 32.f });
		ent->addComponent<CSprite>(m_gameEngine->getAssets().getTexture("Brick"), sf::Vector2f{ 2.f,2.f });

		ent->getComponent<CBoundingBox>().b_shape.setPosition(sf::Vector2f{ 32.f * (i + 2), 32.f * 15.f });

		ent->getComponent<CBoundingBox>().updateCenter();

		ent->getComponent<CSprite>().m_sprite.setPosition(ent->getComponent<CBoundingBox>().center.x, ent->getComponent<CBoundingBox>().center.y - 1.f);

	}

	auto ent = m_entManager.addEntity(TAG::BACK_TILE);

	ent->addComponent<CSprite>(m_gameEngine->getAssets().getTexture("Bush1"), sf::Vector2f{ 2.f,2.f });

	ent->getComponent<CSprite>().m_sprite.setOrigin(sf::Vector2f{ ent->getComponent<CSprite>().m_sprite.getPosition().x,
		ent->getComponent<CSprite>().m_sprite.getPosition().y + ent->getComponent<CSprite>().m_sprite.getGlobalBounds().height });
	ent->getComponent<CSprite>().m_sprite.setPosition(sf::Vector2f{32.f * 7, 32.f * 20.f + 5.f});


}

void Level::initPlayer()
{
	m_player = m_entManager.addEntity(TAG::PLAYER);

	m_player->addComponent<CBoundingBox>(sf::Vector2f{ 26.f, 26.f });
	m_player->getComponent<CBoundingBox>().b_shape.setPosition(sf::Vector2f{ 32.f * 3, 32.f * 8 });
	m_player->getComponent<CBoundingBox>().updateCenter();
	m_player->addComponent<CInput>();
	m_player->addComponent<CTransformable>();
	
	m_player->getComponent<CTransformable>().speedLimit = 0.9f;
	m_player->getComponent<CTransformable>().speed = sf::Vector2f{ 0.f,0.f };

	m_player->addComponent<CSprite>(m_gameEngine->getAssets().getTexture("MarioIDLE"), sf::Vector2f{ 2.f, 2.f });
	m_player->getComponent<CSprite>().m_sprite.setPosition(m_player->getComponent<CBoundingBox>().center.x,
		m_player->getComponent<CBoundingBox>().center.y - 1.f);
	
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
		target.draw(ent->getComponent<CSprite>().m_sprite);
	}

	for (auto& ent : m_entManager.getAllByTag(TAG::BACK_TILE)) {

		target.draw(ent->getComponent<CSprite>().m_sprite);

	}
}

void Level::renderPlayer(sf::RenderTarget& target)
{
	target.draw(m_player->getComponent<CBoundingBox>().b_shape);
	target.draw(m_player->getComponent<CSprite>().m_sprite);
}

void Level::updatePlayerSpeed()
{
	if (m_player->getComponent<CTransformable>().onGround) {
		m_player->getComponent<CTransformable>().speed.y = 0.f;
	}

	if (m_player->getComponent<CSprite>().right) {

		m_player->getComponent<CSprite>().m_sprite.setScale(sf::Vector2f{ 2.f, 2.f });

	}
	else {

		m_player->getComponent<CSprite>().m_sprite.setScale(sf::Vector2f{ -2.f, 2.f });


	}

	//speed on x side

	float& p_speedX = m_player->getComponent<CTransformable>().speed.x;
	float& p_speedY = m_player->getComponent<CTransformable>().speed.y;

	if (m_player->getComponent<CInput>().RIGHT) {

		m_player->getComponent<CSprite>().right = true;

		m_player->getComponent<CSprite>().m_sprite.setScale(sf::Vector2f{ 2.f, 2.f });

		p_speedX += 2.5f * deltaTime;
		if (p_speedX > m_player->getComponent<CTransformable>().speedLimit) {
			p_speedX = m_player->getComponent<CTransformable>().speedLimit;
		}

	}

	if (m_player->getComponent<CInput>().LEFT) {

		m_player->getComponent<CSprite>().right = false;

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
		if (p_speedY > 1.5f) {
			p_speedY = 1.5f;
		}
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
	bool g_collide = false;

	bool jump = false;
	bool fall = false;

	bool right = false;
	bool left = false;

	for (auto& e : m_entManager.getAllByTag(TAG::TILE)) {

		auto& b_shape = m_player->getComponent<CBoundingBox>().b_shape;
		m_player->getComponent<CBoundingBox>().center = sf::Vector2f{ b_shape.getPosition().x + b_shape.getGlobalBounds().width / 2,
				b_shape.getPosition().y + b_shape.getGlobalBounds().height / 2 };

		auto& ent_player = m_player->getComponent<CBoundingBox>().b_shape;

		auto& ent_shape = e->getComponent<CBoundingBox>().b_shape;

		if (Physics::isColliding(m_player->getComponent<CBoundingBox>().b_shape, e->getComponent<CBoundingBox>().b_shape)) {

			g_collide = true;

			float offset_y = Physics::getVertSquare(ent_player, ent_shape);
			float offset_x = Physics::getHorizSquare(ent_player, ent_shape);

			//jump collision
			if (offset_y < 0.f && !m_player->getComponent<CTransformable>().onGround && offset_x < 0.f) {

				jump = true;
			}

			//ground collision
			else if (offset_y > 0.f){

				fall = true;

			}

			//rifht collision
			if (offset_x > 0.f && m_player->getComponent<CTransformable>().onGround) {

				right = true;

			}

			//left collision
			else if(offset_x < 0.f && offset_x > -700.f){

				left = true;

			}
					
		}

		

		if (jump) {

			sf::Vector2f newPos{ ent_player.getPosition().x, ent_shape.getPosition().y + ent_shape.getGlobalBounds().height };

			m_player->getComponent<CBoundingBox>().b_shape.setPosition(newPos);
			m_player->getComponent<CSprite>().m_sprite.setPosition(m_player->getComponent<CBoundingBox>().center);

			m_player->getComponent<CTransformable>().speed.y = 9.8 * deltaTime;

			m_player->getComponent<CTransformable>().onGround = false;

		}

		else if (fall) {

			sf::Vector2f newPos{ ent_player.getPosition().x, ent_shape.getPosition().y - ent_player.getGlobalBounds().height };

			m_player->getComponent<CBoundingBox>().b_shape.setPosition(newPos);
			m_player->getComponent<CSprite>().m_sprite.setPosition(m_player->getComponent<CBoundingBox>().center.x, 
				m_player->getComponent<CBoundingBox>().center.y - 5.f);

			m_player->getComponent<CTransformable>().speed.y = 0.f;

			m_player->getComponent<CTransformable>().onGround = true;

		}

		else if (right && fall) {

			sf::Vector2f newPos{ ent_player.getPosition().x, ent_shape.getPosition().y - ent_player.getGlobalBounds().height };

			m_player->getComponent<CBoundingBox>().b_shape.setPosition(newPos);
			m_player->getComponent<CSprite>().m_sprite.setPosition(m_player->getComponent<CBoundingBox>().center);

			m_player->getComponent<CTransformable>().speed.y = 0.f;

			m_player->getComponent<CTransformable>().onGround = true;

		}

		else if (right) {

			sf::Vector2f newPos{ ent_shape.getPosition().x - ent_player.getGlobalBounds().width, ent_player.getPosition().y};

			m_player->getComponent<CBoundingBox>().b_shape.setPosition(newPos);
			m_player->getComponent<CSprite>().m_sprite.setPosition(m_player->getComponent<CBoundingBox>().center);

			m_player->getComponent<CTransformable>().speed.x = 0;

		}

		else if (left) {

			sf::Vector2f newPos{ ent_shape.getPosition().x + ent_shape.getGlobalBounds().width, ent_player.getPosition().y };

			m_player->getComponent<CBoundingBox>().b_shape.setPosition(newPos);
			m_player->getComponent<CSprite>().m_sprite.setPosition(m_player->getComponent<CBoundingBox>().center);

			m_player->getComponent<CTransformable>().speed.x = 0;

		}
		jump = false;
		fall = false;
		right = false;
		left = false;
	}

	if (!g_collide) {
		m_player->getComponent<CTransformable>().onGround = false;
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

	m_player->getComponent<CSprite>().m_sprite.move(m_player->getComponent<CTransformable>().speed);

}

void Level::sRender(sf::RenderTarget& target)
{
	target.clear(sf::Color{ 92, 148, 252, 255 });

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
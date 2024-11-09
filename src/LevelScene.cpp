#include "LevelScene.h"
#include "Scene.h"
#include "GameEngine.h"
#include "Physics.h"
#include "Animation.h"

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
	showCBoxes = false;
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
	if (m_scene_name == "LEVEL 1") {

		initLevel1();
	}
	else if (m_scene_name == "LEVEL 2") {

		initLevel2();
	}


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

	m_player->addComponent<CSprite>(m_gameEngine->getAssets().getTexture("MarioRun"), sf::Vector2f{ 2.f, 2.f });
	m_player->getComponent<CSprite>().m_sprite.setPosition(m_player->getComponent<CBoundingBox>().center.x,
		m_player->getComponent<CBoundingBox>().center.y - 1.f);

	anim = std::make_shared<Animation>(m_gameEngine->getAssets().getTexture("MarioRun"), 0.001f, 3.f);
	
}

void Level::initLevel1()
{

	for (int j{ 0 }; j < 2; j++) {

		for (int i{ 0 }; i < 32; i++) {

			addTile("Brick", sf::Vector2f{ 32.f * i, 32.f * (18.f + (float)j) });

		}

	}

	for (int i{ 0 }; i < 6; i++) {

		addTile("Brick", sf::Vector2f{ 32.f * i, 32.f * 15.f });

	}

	//pipes
	addPipe(3, sf::Vector2f{ 32.f * 15.f, 32.f * 18.f });
	addPipe(2, sf::Vector2f{ 32.f * 12.f, 32.f * 18.f });

	//add background tiles
	addBackTile("Bush1", sf::Vector2f{ 32.f * 7.f, 32.f * 20.f + 5.f });
	addBackTile("Bush1", sf::Vector2f{ 32.f * 15.f, 32.f * 20.f + 5.f });
	addBackTile("Bush2", sf::Vector2f{ 32.f * 2.f, 32.f * 19.f });
	addBackTile("Bush2", sf::Vector2f{ 32.f * 25.f, 32.f * 19.f });



}

void Level::initLevel2()
{

}

void Level::addBackTile(std::string texName, sf::Vector2f pos)
{
	auto ent = m_entManager.addEntity(TAG::BACK_TILE);

	ent->addComponent<CSprite>(m_gameEngine->getAssets().getTexture(texName), sf::Vector2f{ 2.f,2.f });

	ent->getComponent<CSprite>().m_sprite.setOrigin(sf::Vector2f{ ent->getComponent<CSprite>().m_sprite.getPosition().x,
		ent->getComponent<CSprite>().m_sprite.getPosition().y + ent->getComponent<CSprite>().m_sprite.getGlobalBounds().height });
	ent->getComponent<CSprite>().m_sprite.setPosition(pos);
}

void Level::addTile(std::string texName, sf::Vector2f pos)
{
	auto ent = m_entManager.addEntity(TAG::TILE);

	ent->addComponent<CBoundingBox>(sf::Vector2f{ 32.f, 32.f });
	ent->addComponent<CSprite>(m_gameEngine->getAssets().getTexture(texName), sf::Vector2f{ 2.f,2.f });

	ent->getComponent<CBoundingBox>().b_shape.setPosition(pos);

	ent->getComponent<CBoundingBox>().updateCenter();

	ent->getComponent<CSprite>().m_sprite.setPosition(ent->getComponent<CBoundingBox>().center.x,
		ent->getComponent<CBoundingBox>().center.y - 1.f);
}

void Level::addPipe(int lenght, sf::Vector2f l_pos)
{
	int l_lenght = lenght;
	for (int i{ l_lenght }; i > 0; i--) {

		addTile("PipeBL", sf::Vector2f{l_pos.x, l_pos.y - i * 32.f });
		addTile("PipeBR", sf::Vector2f{ l_pos.x + 32.f, l_pos.y - i * 32.f});

		if ((i - 1) <= 0) {

			addTile("PipeUL", sf::Vector2f{ l_pos.x, l_pos.y - (32 * (l_lenght + 1.f)) });
			addTile("PipeUR", sf::Vector2f{	l_pos.x + 32.f, l_pos.y - (32 * (l_lenght + 1.f)) });
		}
	}
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
	for (auto& ent : m_entManager.getAllByTag(TAG::BACK_TILE)) {

		target.draw(ent->getComponent<CSprite>().m_sprite);

	}

	for (auto& ent : m_entManager.getAllByTag(TAG::TILE)) {

		if (showCBoxes) {
			target.draw(ent->getComponent<CBoundingBox>().b_shape);
		}
		
		target.draw(ent->getComponent<CSprite>().m_sprite);
	}
}

void Level::renderPlayer(sf::RenderTarget& target)
{
	if (showCBoxes) {
		target.draw(m_player->getComponent<CBoundingBox>().b_shape);
	}
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

		m_player->getComponent<CSprite>().m_sprite.setTextureRect(anim->getAnimRect());

		m_player->getComponent<CSprite>().m_sprite.setScale(sf::Vector2f{ 2.f, 2.f });

		p_speedX += 2.5f * deltaTime;
		if (p_speedX > m_player->getComponent<CTransformable>().speedLimit) {
			p_speedX = m_player->getComponent<CTransformable>().speedLimit;
		}

	}

	else if (m_player->getComponent<CInput>().LEFT) {

		m_player->getComponent<CSprite>().right = false;

		m_player->getComponent<CSprite>().m_sprite.setTextureRect(anim->getAnimRect());

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

	if (p_speedX == 0) {
		m_player->getComponent<CSprite>().m_sprite.setTexture(m_gameEngine->getAssets().getTexture("MarioIDLE"));
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

		if (jump && left) {
			continue;
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

	if (action.keyCode() == sf::Keyboard::C && action.status()) {

		showCBoxes = !showCBoxes;

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
		if (action.keyCode() == sf::Keyboard::G || action.keyCode() == sf::Keyboard::C) {

			action.setStatus(false);
		}
		
	}
	
	if (m_keys.size() != 0) {

		updatePlayerSpeed();

		updateCollision();

		
	}
	anim->update();
}
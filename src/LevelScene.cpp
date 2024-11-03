#include "LevelScene.h"
#include "Scene.h"
#include "GameEngine.h"

// all Level based stuff
Level::Level(const std::string name, GameEngine* gameEngine, const std::string fileName)
	: Scene(name, gameEngine), m_fileName(fileName) {
	init();
}

void Level::regInputs()
{
	//movement
	registerAction(Action{ sf::Keyboard::W });
	registerAction(Action{ sf::Keyboard::S });
	registerAction(Action{ sf::Keyboard::A });
	registerAction(Action{ sf::Keyboard::D });

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

	regInputs();

	initGrid();
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

}

void Level::renderGrid(sf::RenderTarget& target)
{
	for (auto& ent : m_entManager.getAllByTag(TAG::GRID)) {
		target.draw(ent->getComponent<CBoundingBox>().b_shape);
		target.draw(ent->getComponent<CText>().text);
	}
}

void Level::sDoAction(Action action)
{

	if (action.keyCode() == sf::Keyboard::Escape && action.status()) {

		m_gameEngine->ChangeScene("MainMenu");

	}

	if (action.keyCode() == sf::Keyboard::G && action.status()) {

		showGrid = !showGrid;
	}

}

void Level::sRender(sf::RenderTarget& target)
{
	if (showGrid) {
		renderGrid(target);
	}
}

void Level::update()
{
	for (auto& action : m_keys)
	{
		if (m_keys.size() == 0) {
			return;
		}
		sDoAction(action);
		action.setStatus(false);
	}

}
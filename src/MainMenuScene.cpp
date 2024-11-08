#include "MainMenuScene.h"
#include "GameEngine.h"

//Main menu scene

MainMenu::MainMenu(const std::string name, GameEngine* gameEngine) : Scene(name, gameEngine)
{
	registerAction(Action(sf::Keyboard::W));
	registerAction(Action(sf::Keyboard::S));
	registerAction(Action(sf::Keyboard::Enter));
	registerAction(Action(sf::Keyboard::Escape));

	init();

}

MainMenu::~MainMenu() {}

void MainMenu::sRender(sf::RenderTarget& target)
{
	for (auto& e : entManager.getAllByTag(TAG::TEXT)) {
		target.draw(e->getComponent<CText>().text);
	}
}

void MainMenu::sDoAction(Action action)
{
	auto& e = entManager.getAllByTag(TAG::TEXT);

	// if there are more than one options in menu
	if (choiceCount != 1) {
		if (action.keyCode() == sf::Keyboard::W && action.status()) {
			choice--;
			if (choice < 0) {
				choice = choiceCount;
				m_savedEnt = e[choice];

				e[choice]->getComponent<CText>().text.setFillColor(sf::Color::Yellow);
				e[choice - choiceCount]->getComponent<CText>().text.setFillColor(sf::Color::White);
				return;

			}
			m_savedEnt = e[choice];
			e[choice]->getComponent<CText>().text.setFillColor(sf::Color::Yellow);
			e[choice + 1]->getComponent<CText>().text.setFillColor(sf::Color::White);

		}
		else if (action.keyCode() == sf::Keyboard::S && action.status()) {
			choice++;
			if (choice > choiceCount) {
				choice = 0;
				m_savedEnt = e[choice];

				e[choice]->getComponent<CText>().text.setFillColor(sf::Color::Yellow);
				e[choice + choiceCount]->getComponent<CText>().text.setFillColor(sf::Color::White);
				return;
			}
			m_savedEnt = e[choice];
			e[choice]->getComponent<CText>().text.setFillColor(sf::Color::Yellow);
			e[choice - 1]->getComponent<CText>().text.setFillColor(sf::Color::White);
		}
	}

	//go back button
	if (action.keyCode() == sf::Keyboard::Escape && action.status()) {
		init();
		return;
	}

	if (action.keyCode() == sf::Keyboard::Enter && action.status()) {
		//clear all entities
		entManager.clear();
		auto& text = m_savedEnt->getComponent<CText>().text.getString();
		//exit

		if (text == "START") {
			initLevelPicker();
		}
		else if (text == "OPTIONS") {
			initOptions();
		}
		else if (text == "EXIT") {
			m_gameEngine->SetRunning(false);
		}
		else if (text == "BACK") {
			init();
		}

		if (text == "LEVEL 1") {
			m_gameEngine->ChangeScene("Level");

		}

	}


}

void MainMenu::init()
{
	entManager.clear();

	auto start_t = entManager.addEntity(TAG::TEXT);
	auto options_t = entManager.addEntity(TAG::TEXT);
	auto exit_t = entManager.addEntity(TAG::TEXT);
	auto label_t = entManager.addEntity(TAG::TEXT);

	start_t->addComponent<CText>("START", m_gameEngine->getAssets().getFont("MainMenu"),
		60);
	start_t->getComponent<CText>().text.setPosition(sf::Vector2f{ 100.f,200.f });
	start_t->getComponent<CText>().text.setFillColor(sf::Color::Yellow);

	options_t->addComponent<CText>("OPTIONS", m_gameEngine->getAssets().getFont("MainMenu"),
		60);
	options_t->getComponent<CText>().text.setPosition(sf::Vector2f{ 100.f,300.f });

	exit_t->addComponent<CText>("EXIT", m_gameEngine->getAssets().getFont("MainMenu"),
		60);
	exit_t->getComponent<CText>().text.setPosition(sf::Vector2f{ 100.f,400.f });


	label_t->addComponent<CText>("MARIO", m_gameEngine->getAssets().getFont("MainMenu"),
		60);
	label_t->getComponent<CText>().text.setPosition(sf::Vector2f{ 350, 50.f });
	label_t->getComponent<CText>().text.setFillColor(sf::Color::Green);

	choice = 0;
	choiceCount = 2;

	Action temp{ sf::Keyboard::S };
	temp.setStatus(true);
	sDoAction(temp);
}

void MainMenu::initLevelPicker()
{
	entManager.clear();

	auto level1_t = entManager.addEntity(TAG::TEXT);
	auto level2_t = entManager.addEntity(TAG::TEXT);
	auto back_t = entManager.addEntity(TAG::TEXT);
	auto label_t = entManager.addEntity(TAG::TEXT);

	level1_t->addComponent<CText>("LEVEL 1", m_gameEngine->getAssets().getFont("MainMenu"),
		60);
	level1_t->getComponent<CText>().text.setPosition(sf::Vector2f{ 100.f,200.f });
	level1_t->getComponent<CText>().text.setFillColor(sf::Color::Yellow);

	level2_t->addComponent<CText>("LEVEL 2", m_gameEngine->getAssets().getFont("MainMenu"),
		60);
	level2_t->getComponent<CText>().text.setPosition(sf::Vector2f{ 100.f,300.f });

	back_t->addComponent<CText>("BACK", m_gameEngine->getAssets().getFont("MainMenu"),
		60);
	back_t->getComponent<CText>().text.setPosition(sf::Vector2f{ 100.f,400.f });

	label_t->addComponent<CText>("CHOOSE LEVEL", m_gameEngine->getAssets().getFont("MainMenu"),
		60);
	label_t->getComponent<CText>().text.setPosition(sf::Vector2f{ 300.f, 50.f });

	choice = 0;
	choiceCount = 2;

	Action temp{ sf::Keyboard::S };
	temp.setStatus(true);
	sDoAction(temp);
}

void MainMenu::initOptions()
{
	entManager.clear();

	auto exit_t = entManager.addEntity(TAG::TEXT);

	exit_t->addComponent<CText>("EXIT", m_gameEngine->getAssets().getFont("MainMenu"),
		60);
	exit_t->getComponent<CText>().text.setPosition(sf::Vector2f{ 100.f,400.f });
	exit_t->getComponent<CText>().text.setFillColor(sf::Color::Yellow);

	m_savedEnt = exit_t;

	choice = 0;
	choiceCount = 0;
}

void MainMenu::update()
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

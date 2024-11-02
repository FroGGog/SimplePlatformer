#include "Scene.h"
#include "iostream"
#include "GameEngine.h"

Scene::Scene(const std::string name, GameEngine* gameEngine) : m_scene_name(name), m_gameEngine(gameEngine) {};

Scene::~Scene()
{
	m_gameEngine = nullptr;
}

void Scene::registerAction(Action action)
{
	m_keys.push_back(action);
}

void Scene::doAction(sf::Keyboard::Key key, bool status)
{
	for (auto& action : m_keys) {
		if (action.keyCode() == key) {
			action.setStatus(status);
		}
	}
}

const std::string& Scene::name() const
{
	return m_scene_name;
}

//Main menu scene

MainMenu::MainMenu(const std::string name, GameEngine* gameEngine) : Scene(name, gameEngine)
{
	registerAction(Action(sf::Keyboard::W));
	registerAction(Action(sf::Keyboard::S));
	registerAction(Action(sf::Keyboard::Space));

	init();

}

void MainMenu::sRender(sf::RenderTarget& target)
{
	for (auto& e : entManager.getAllByTag(TAG::TEXT)) {
		target.draw(e->getComponent<CText>().text);
	}
}

void MainMenu::sDoAction(Action action)
{
	auto& e = entManager.getAllByTag(TAG::TEXT);


	if (action.keyCode() == sf::Keyboard::W && action.status()) {
		choice--;
		if (choice < 0) {
			choice = choiceCount;

			e[choice]->getComponent<CText>().text.setFillColor(sf::Color::Yellow);
			e[choice - choiceCount]->getComponent<CText>().text.setFillColor(sf::Color::White);
			return;

		}
		e[choice]->getComponent<CText>().text.setFillColor(sf::Color::Yellow);
		e[choice + 1]->getComponent<CText>().text.setFillColor(sf::Color::White);
		
	}
	else if (action.keyCode() == sf::Keyboard::S && action.status()) {
		choice++;
		if (choice > choiceCount) {
			choice = 0;

			e[choice]->getComponent<CText>().text.setFillColor(sf::Color::Yellow);
			e[choice + choiceCount]->getComponent<CText>().text.setFillColor(sf::Color::White);
			return;
		}
		e[choice]->getComponent<CText>().text.setFillColor(sf::Color::Yellow);
		e[choice - 1]->getComponent<CText>().text.setFillColor(sf::Color::White);
	}


}

void MainMenu::init()
{
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
	label_t->getComponent<CText>().text.setPosition(sf::Vector2f{350, 50.f});
	label_t->getComponent<CText>().text.setFillColor(sf::Color::Green);

	choice = 0;
	choiceCount = 2;
	
}

void MainMenu::update()
{
	for (auto& action : m_keys) 
	{
		sDoAction(action);
		action.setStatus(false);
	}


}

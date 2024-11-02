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

}

void MainMenu::sRender(sf::RenderTarget& target)
{
	for (auto& e : entManager.getAllByTag(TAG::TEXT)) {
		target.draw(e->getComponent<CText>().text);
	}
}

void MainMenu::sDoAction(Action action)
{
	if (action.keyCode() == sf::Keyboard::W && action.status()) {
		
	}
	else if (action.keyCode() == sf::Keyboard::S && action.status()) {
		
	}


}

void MainMenu::init()
{
	auto start_t = entManager.addEntity(TAG::TEXT);
	start_t->addComponent<CText>("START", )

}

void MainMenu::update()
{
	for (auto& action : m_keys) 
	{
		sDoAction(action);
	}
	
}

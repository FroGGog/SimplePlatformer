#include "Scene.h"
#include "iostream"

Scene::Scene(const std::string name) : m_scene_name(name) {}

Scene::Scene()
{
	m_scene_name = "DEFAULT";
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
		std::cout << action.status() << '\n';
	}
	

}

const std::string& Scene::name() const
{
	return m_scene_name;
}

//Main menu scene

MainMenu::MainMenu(const std::string name) : Scene(name)
{
	registerAction(Action(sf::Keyboard::Space));
	registerAction(Action(sf::Keyboard::A));

}

MainMenu::MainMenu() : Scene() {}

void MainMenu::sRender()
{

}

void MainMenu::sDoAction(Action action)
{

}

void MainMenu::update()
{

}

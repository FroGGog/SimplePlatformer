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



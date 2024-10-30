#include "Scene.h"
#include "iostream"

Scene::Scene(const std::string name) : m_scene_name(name) {}

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

MainMenu::MainMenu(const std::string name) : Scene(name)
{
	registerAction(Action(sf::Keyboard::W));
	registerAction(Action(sf::Keyboard::S));

	auto e = entManager.addEntity(TAG::TILE);
	e->addComponent<CBoundingBox>(sf::Vector2f{ 150.f, 150.f });
}

void MainMenu::sRender(sf::RenderTarget& target)
{
	for (auto& e : entManager.getAllByTag(TAG::TILE)) {
		target.draw(e->getComponent<CBoundingBox>().b_shape);
	}
}

void MainMenu::sDoAction(Action action)
{
	if (action.keyCode() == sf::Keyboard::W && action.status()) {
		auto e = entManager.addEntity(TAG::TILE);
		e->addComponent<CBoundingBox>(sf::Vector2f{ (float)(rand() % 900), (float)(rand() % 600) });
	}
	else if (action.keyCode() == sf::Keyboard::S && action.status()) {

	}


}

void MainMenu::update()
{
	for (auto& action : m_keys) 
	{
		sDoAction(action);
	}
	
}

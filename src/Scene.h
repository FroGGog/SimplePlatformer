#pragma once
#include "EntityManager.h"
#include "Action.h"

class Scene {

protected:

	EntityManager m_entManager;
	std::string m_scene_name;
	std::vector<Action> m_keys;

	void registerAction(Action action);

public:
	Scene(const std::string name);
	Scene();

	virtual void sRender() = 0;
	virtual void sDoAction(Action action) = 0;
	virtual void update() = 0;

	void doAction(sf::Keyboard::Key key, bool status);
	//void doAction(sf::Mouse::Button);


	const std::string& name() const;
};

class MainMenu : public Scene
{

public:

	MainMenu(const std::string name);
	MainMenu();

	void sRender() override;
	void sDoAction(Action action) override;
	void update() override;
	


};
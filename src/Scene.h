#pragma once
#include "EntityManager.h"
#include "Action.h"

class GameEngine;

class Scene {

protected:

	EntityManager m_entManager;
	std::string m_scene_name;
	std::vector<Action> m_keys;
	GameEngine* m_gameEngine;
	
	void registerAction(Action action);

	virtual void sDoAction(Action action) = 0;

public:
	explicit Scene(const std::string name, GameEngine* gameEngine);
	~Scene();

	virtual void sRender(sf::RenderTarget& target) = 0;
	virtual void update() = 0;

	void doAction(sf::Keyboard::Key key, bool status);
	//void doAction(sf::Mouse::Button);


	const std::string& name() const;
};

class MainMenu : public Scene
{

private:

	void sDoAction(Action action) override;

	EntityManager entManager;

	void init();

public:

	MainMenu(const std::string name, GameEngine* gameEngine);

	void sRender(sf::RenderTarget& target) override;
	void update() override;
	


};
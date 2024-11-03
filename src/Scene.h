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
	
	int choice;
	int choiceCount;

	void init();
	void initLevelPicker();
	void initOptions();

	std::shared_ptr<Entity> m_savedEnt;

public:

	MainMenu(const std::string name, GameEngine* gameEngine);
	~MainMenu();

	void sRender(sf::RenderTarget& target) override;
	void update() override;
	
};


class Level : public Scene {

private:

	void sDoAction(Action action) override;

	EntityManager entManager;
	std::string m_fileName;

	void regInputs();
	void init();

	void initGrid();

public:

	Level(const std::string name, GameEngine* gameEngine, const std::string fileName);

	void sRender(sf::RenderTarget& target) override;
	void update() override;

};
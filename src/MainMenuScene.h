#pragma once
#include "Scene.h"

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

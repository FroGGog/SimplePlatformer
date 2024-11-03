#pragma once
#include "Scene.h"

class GameEngine;

class Level : public Scene {

private:

	void sDoAction(Action action) override;

	EntityManager entManager;
	std::string m_fileName;

	bool showGrid;

	void regInputs();
	void init();

	void initGrid();
	void initLevel();

	void renderGrid(sf::RenderTarget& target);

public:

	Level(const std::string name, GameEngine* gameEngine, const std::string fileName);

	void sRender(sf::RenderTarget& target) override;
	void update() override;

};
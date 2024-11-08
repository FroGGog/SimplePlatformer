#pragma once
#include "Scene.h"

class GameEngine;

class Level : public Scene {

private:

	void sDoAction(Action action) override;

	EntityManager entManager;
	std::string m_fileName;

	std::shared_ptr<Entity> m_player;

	bool showGrid;
	bool showCBoxes;
	float deltaTime;

	void regInputs();
	void init();

	void initGrid();
	void initLevel();
	void initPlayer();

	void initLevel1();
	void initLevel2();
	void addBackTile(std::string texName, sf::Vector2f pos);
	void addTile(std::string texName, sf::Vector2f pos);
	void addPipe(int lenght, sf::Vector2f l_pos);

	void renderGrid(sf::RenderTarget& target);
	void renderLevel(sf::RenderTarget& target);
	void renderPlayer(sf::RenderTarget& target);

	void updatePlayerSpeed();
	void updatePlayerInput(Action action);
	void updateCollision();

public:

	Level(const std::string name, GameEngine* gameEngine, const std::string fileName);

	void sRender(sf::RenderTarget& target) override;
	void update() override;

};
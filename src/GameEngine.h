#include "LevelScene.h"
#include "MainMenuScene.h"
#include "Assets.h"

class GameEngine {

private:

	std::shared_ptr<sf::RenderWindow> m_win;
	sf::VideoMode vidMode;
	sf::Event evt;

	sf::Clock time;
	sf::Time deltaTime;

	std::shared_ptr<Scene> CurrentScene;

	Assets assets;

	bool m_running;

	void init();
	void initAssets();
	void UserInput();

public:

	GameEngine();
	
	void Render();
	void Update();

	void SetRunning(bool rn);
	void ChangeScene(std::string sceneName);

	const bool isOpen() const;
	const std::shared_ptr<sf::RenderWindow> window() const;
	Assets& getAssets();
};
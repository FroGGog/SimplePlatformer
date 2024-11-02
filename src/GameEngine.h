#include "Scene.h"
#include "Assets.h"

class GameEngine {

private:

	std::shared_ptr<sf::RenderWindow> m_win;
	sf::VideoMode vidMode;
	sf::Event evt;

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

	const bool isOpen() const;
	const std::shared_ptr<sf::RenderWindow> window() const;
	Assets& getAssets();
};
#include "GameEngine.h"

void GameEngine::init()
{
	vidMode.width = 960;
	vidMode.height = 640;

	m_win = std::make_shared<sf::RenderWindow>(vidMode, "Mario", sf::Style::Titlebar | sf::Style::Close);

	CurrentScene = std::make_shared<Level>("LEVEL 1", this, "src/");
	//CurrentScene = std::make_shared<MainMenu>("MainMenu", this);
	m_win->setFramerateLimit(60);
	
}

void GameEngine::initAssets()
{
	assets.addFont("MainMenu", "fonts/menu.ttf");
	assets.addFont("Grid", "fonts/grid.ttf");

	assets.addTexture("MarioIDLE", "textures/MarioIDLE.png");
	assets.addTexture("Brick", "textures/Brick.png");
}

GameEngine::GameEngine()
{
	initAssets();

	init();
	
	m_running = true;
}

void GameEngine::Render()
{
	m_win->clear();

	CurrentScene->sRender(*m_win);

	m_win->display();

	deltaTime = time.getElapsedTime();

}

void GameEngine::Update()
{
	time.restart();

	UserInput();
	//Call currentScence->update()
	CurrentScene->update();

}

void GameEngine::SetRunning(bool rn)
{
	m_running = rn;
}

void GameEngine::ChangeScene(std::string sceneName)
{
	if (sceneName == "MainMenu") {
		CurrentScene = std::make_shared<MainMenu>("MainMenu", this);
		m_win->setFramerateLimit(10);
	}
	else if (sceneName == "Level") {
		std::cout << "Changed scene\n";
		CurrentScene = std::make_shared<Level>("Level1", this, "/src");
		m_win->setFramerateLimit(60);
	}
}

void GameEngine::UserInput()
{
	//recreate this with action class
	while (m_win->pollEvent(evt)) {

		switch (evt.type)
		{
		case sf::Event::Closed:
			m_running = false;
			break;
		case sf::Event::KeyPressed:
			CurrentScene->doAction(evt.key.code, true);
			break;
		case sf::Event::KeyReleased:
			CurrentScene->doAction(evt.key.code, false);
			break;
		default:
			break;
		}
	}
}

const bool GameEngine::isOpen() const
{
	return m_running;
}

const std::shared_ptr<sf::RenderWindow> GameEngine::window() const
{
	return m_win;
}

Assets& GameEngine::getAssets()
{
	return assets;
}

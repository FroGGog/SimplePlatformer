#pragma once
#include "EntityManager.h"
#include "Action.h"

class Scene {

protected:

	EntityManager m_entManager;
	std::string m_scene_name;
	std::vector<Action> m_keys;

	void registerAction(Action action);

	virtual void sDoAction(Action action) = 0;

public:
	Scene(const std::string name);

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

public:

	MainMenu(const std::string name);

	void sRender(sf::RenderTarget& target) override;
	void update() override;
	


};
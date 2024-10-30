#pragma once
#include <string>
#include "SFML/Graphics.hpp"

class Action {

private:
	
	sf::Keyboard::Key m_key;
	bool m_status;

public:

	Action(const sf::Keyboard::Key key);

	const sf::Keyboard::Key keyCode();
	const bool status();

	void setStatus(bool status);

};
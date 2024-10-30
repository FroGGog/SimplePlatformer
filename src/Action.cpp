#include "Action.h"

Action::Action(const sf::Keyboard::Key key): m_key(key), m_status(false) {}

const sf::Keyboard::Key Action::keyCode()
{
	return m_key;
}

const bool Action::status()
{
	return m_status;
}

void Action::setStatus(bool status)
{
	m_status = status;
}

#pragma once
#include "SFML/Graphics.hpp"

class Animation {

private:

	int m_currentFrame;
	float m_speed;
	int m_framesCount;
		
	sf::Clock m_clock;
	sf::Time m_time;

	sf::IntRect m_rect;

public:

	Animation(sf::Texture& texture, float speed, int framesCount);

	void update();

	sf::IntRect& getAnimRect();

};
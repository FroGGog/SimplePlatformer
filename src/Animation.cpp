#include "Animation.h"

Animation::Animation(sf::Texture& texture, float speed, int framesCount)
{
	m_speed = speed;
	m_framesCount = framesCount;
	m_currentFrame = 0;

	m_time = m_clock.restart();

	m_rect = sf::IntRect{ 16 * m_currentFrame, 0, 16, 16 };


}

void Animation::update()
{
	if (m_time.asSeconds() > m_speed) {
		m_currentFrame++;
		m_clock.restart();
		if (m_currentFrame > (m_framesCount - 1)) {
			m_currentFrame = 0;
		}
	}
	m_rect = sf::IntRect{ 16 * m_currentFrame, 0, 16, 16 };
	m_time = m_clock.getElapsedTime();
}

sf::IntRect& Animation::getAnimRect()
{
	return m_rect;
}


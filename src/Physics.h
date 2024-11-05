#include "SFML/Graphics.hpp"

namespace Physics {

	bool isColliding(sf::RectangleShape& shape1, sf::RectangleShape& shape2);

	float getVertSquare(sf::RectangleShape& shape1, sf::RectangleShape& shape2);
	float getHorizSquare(sf::RectangleShape& shape1, sf::RectangleShape& shape2);
}



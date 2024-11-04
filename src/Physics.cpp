#include "Physics.h"
#include "iostream"

namespace Physics {

	// This function is used for checking if two rectangle shapes is colliding with each other
	bool isColliding(sf::RectangleShape& shape1, sf::RectangleShape& shape2)
	{
		sf::Vector2f pos_1 = shape1.getPosition();
		float shape1_w = shape1.getGlobalBounds().width;
		float shape1_h = shape1.getGlobalBounds().height;

		sf::Vector2f pos_2 = shape2.getPosition();
		float shape2_w = shape2.getGlobalBounds().width;
		float shape2_h = shape2.getGlobalBounds().height;

		if (pos_1.x + shape1_w > pos_2.x && pos_1.y + shape1_h > pos_2.y) {

			if (pos_1.x < pos_2.x + shape2_w && pos_1.y < pos_2.y + shape2_h) {

				return true;

			}
		}
		return false;
	}

	// TODO : need to create antorher version of this func to get square if collision in horizontal
	float getCollSquare(sf::RectangleShape& shape1, sf::RectangleShape& shape2)
	{
		
		float pos_1y = shape1.getPosition().y;
		float shape1_h = shape1.getGlobalBounds().height;

		float pos_2y = shape2.getPosition().y;
		float shape2_h = shape2.getGlobalBounds().height;

		return (shape1_h - (pos_1y + shape1_h - pos_2y + shape2_h));



	}


}



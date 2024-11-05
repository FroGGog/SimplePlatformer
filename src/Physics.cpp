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

	//return x > 0 if colliding by down side of shape
	//return x < 0 if colliding by upper side of shape
	float getVertSquare(sf::RectangleShape& shape1, sf::RectangleShape& shape2)
	{
		float pos_1y = shape1.getPosition().y;
		float shape1_h = shape1.getGlobalBounds().height;

		float pos_2y = shape2.getPosition().y;
		float shape2_h = shape2.getGlobalBounds().height;

		if (pos_1y < pos_2y) {
			return (sqrtf(powf((pos_1y + shape1_h), 2) - powf(pos_2y, 2)));
		}
		else if (pos_1y > pos_2y) {
			return -(sqrtf(abs(powf(pos_1y, 2) - powf((pos_2y + shape2_h), 2))));
		}
		else{
		
			return 0;

		}

	}

	float getHorizSquare(sf::RectangleShape& shape1, sf::RectangleShape& shape2)
	{
	
		float pos_1x = shape1.getPosition().x;
		float shape1_w = shape1.getGlobalBounds().width;

		float pos_2x = shape2.getPosition().x;
		float shape2_w = shape2.getGlobalBounds().width;

		if (pos_1x < pos_2x) {
			return (sqrtf(powf((pos_1x + shape1_w), 2) - powf(pos_2x, 2)));
		}
		else if (pos_1x > pos_2x) {
			return -(sqrtf(abs(powf(pos_1x, 2) - powf((pos_2x + shape2_w), 2))));
		}
		else {

			return 0;

		}

	}


}



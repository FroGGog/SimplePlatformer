#pragma once
#include <SFML/Graphics.hpp>


struct CBoundingBox {

	sf::RectangleShape b_shape;
	bool has = false;

	CBoundingBox(sf::Vector2f size_) {

		b_shape.setSize(size_);
		b_shape.setFillColor(sf::Color{ 255,255,255,0 });
		b_shape.setOutlineThickness(2.f);

		has = true;

	}
	CBoundingBox() {};
};
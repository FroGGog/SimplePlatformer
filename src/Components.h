#pragma once
#include <SFML/Graphics.hpp>
#include <string>

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

struct CText {

	sf::Text text;
	std::string placeHolder;
	bool has = false;

	CText(std::string text_, sf::Font& font, int ch_size) {

		text.setFont(font);
		text.setString(text_);
		text.setCharacterSize(ch_size);

		has = true;

	}
	CText() {};

};

struct CInput {

	bool UP = false;
	bool DOWN = false;
	bool LEFT = false;
	bool RIGHT = false;

	bool has = false;

	CInput() { has = true; };

};

struct CTransformable {

	sf::Vector2f speed{ 0.f,0.f };

	sf::Vector2f decel{ 0.f, 0.f };

	float speedLimit;

	bool has = false;

	CTransformable() 
	{ 
		has = true; 
		speedLimit = 0.f;
	};

};
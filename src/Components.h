#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

struct CBoundingBox {

	sf::RectangleShape b_shape;
	sf::Vector2f center;
	bool has = false;

	CBoundingBox(sf::Vector2f size_) {

		b_shape.setSize(size_);
		b_shape.setFillColor(sf::Color{ 255,255,255,0 });
		b_shape.setOutlineThickness(1.f);

		center = sf::Vector2f{ b_shape.getPosition().x + b_shape.getGlobalBounds().width / 2,
			b_shape.getPosition().y + b_shape.getGlobalBounds().height / 2 };

		has = true;

	}

	void updateCenter() {

		center = sf::Vector2f{ b_shape.getPosition().x + b_shape.getGlobalBounds().width / 2,
			b_shape.getPosition().y + b_shape.getGlobalBounds().height / 2 };

	};

	CBoundingBox() {};
};

struct CSprite {

	sf::Sprite m_sprite;

	bool has = false;

	bool right = true;

	CSprite(sf::Texture& tex, sf::Vector2f scale = { 1.f,1.f }) {

		m_sprite.setTexture(tex);

		m_sprite.setOrigin(sf::Vector2f{ float(tex.getSize().x / 2), float(tex.getSize().y / 2)});

		m_sprite.setScale(scale);

		has = true;
	}

	CSprite() {  };
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

	float speedLimit;

	bool has = false;
	bool onGround = false;

	CTransformable() 
	{ 
		has = true; 
		speedLimit = 0.f;
	};

};
#pragma once

#include <map>
#include <string>
#include <iostream>

#include "SFML/Graphics.hpp"


class Assets {

private:

	std::map<std::string, sf::Texture> m_textures;
	std::map<std::string, sf::Font> m_fonts;

public:

	Assets();

	void addTexture(std::string name, std::string path);
	void addFont(std::string name, std::string path);

	sf::Texture& getTexture(std::string name);
	sf::Font& getFont(std::string name);

};
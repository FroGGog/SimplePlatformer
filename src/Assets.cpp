#include "Assets.h"

Assets::Assets(){}

void Assets::addTexture(std::string name, std::string path)
{
	sf::Texture texture;
	if (!texture.loadFromFile(path)) {
		std::cerr << "ERROR::LOADFROMFILE::TEXTURE::" + path << '\n';
	}
	m_textures[name] = texture;
}

void Assets::addFont(std::string name, std::string path)
{
	sf::Font font;
	if (!font.loadFromFile(path)) {
		std::cerr << "ERROR::LOADFROMFILE::TEXTURE::" + path << '\n';
	}
	m_fonts[name] = font;
}

sf::Texture& Assets::getTexture(std::string name)
{
	return m_textures[name];
}

sf::Font& Assets::getFont(std::string name)
{
    return	m_fonts[name];
}

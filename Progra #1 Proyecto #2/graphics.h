#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace std;

class graphics {
private:
	sf::Texture mapTexture;
	sf::Sprite mapSprite;

public:
	graphics();
	void displayMap();

};

#endif // GRAPHICS_H

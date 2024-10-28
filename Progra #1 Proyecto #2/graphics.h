#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace std;

const int MAX_BUTTONS = 10;

struct Button {
	sf::RectangleShape shape;
	std::string name;

	Button() = default;

	Button(float x, float y, float width, float height, sf::Color color, const std::string& buttonName) {
		shape.setSize(sf::Vector2f(width, height));
		shape.setPosition(x, y);
		shape.setFillColor(color);
		name = buttonName;
	}
};

class graphics {
private:
	sf::Texture mapTexture;
	sf::Sprite mapSprite;

	Button buttons[MAX_BUTTONS];
	int buttonCount = 0;

public:
	graphics();
	void displayMap();
	void addButton(float x, float y, float width, float height, sf::Color color, const std::string& name);

};

#endif // GRAPHICS_H

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "filemanager.h"
#include "routenode.h"

using namespace std;

const int MAX_BUTTONS = 10;
const int MAX_POINTS = 120;

struct Button {
    sf::RectangleShape shape;
    std::string name;

    Button() = default;
    Button(float x, float y, float width, float height, sf::Texture& texture, const std::string& buttonName);
};

struct Point {
    sf::CircleShape shape;
    std::string name;

    Point() = default;
    Point(float x, float y, int radius, sf::Color color, const std::string& pointName);
};

class graphics {
private:
    sf::Texture mapTexture;
    sf::Texture addButtonTexture;
    sf::Texture editButtonTexture;
    sf::Texture deleteButtonTexture;
    sf::Texture colorsButtonTexture;
    sf::Sprite mapSprite;

    Button buttons[MAX_BUTTONS];
    int buttonCount = 0;

    Point points[MAX_POINTS];
    int pointCount = 0;

    sf::Vector2f pointPositions[MAX_POINTS];
    sf::Vector2f splinePoints[MAX_POINTS * 20];
    int splinePointCount = 0;

    FileManager fileManager;
    RouteList routeList;

public:
    graphics();
    void displayMap();
    void addButton(float x, float y, float width, float height, sf::Texture& texture, const std::string& name);
    void addPoint(float x, float y, int radius, sf::Color color, const std::string& pointName);
    void calculateSplinePoints();
};

<<<<<<< HEAD
#endif
=======
#endif
>>>>>>> 2dddc26832c4271e736b58f46c17c3856733c5b4

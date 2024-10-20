#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace sf;
using namespace std;

class graphics {
private:
	Texture mapTexture;

public:
	bool loadMap(const std::string& filePath);

	const Texture& getMapTexture() const;
};

#endif // GRAPHICS_H

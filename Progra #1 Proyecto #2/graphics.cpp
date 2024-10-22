#include "graphics.h"

graphics::graphics() {
	if (!mapTexture.loadFromFile("MapCR.png")) {
		cout << "Error al cargar la imagen MapCR.png" << endl;
	}
	else {
		mapSprite.setTexture(mapTexture);
	}
}

void graphics::displayMap() {
	sf::RenderWindow window(sf::VideoMode(mapTexture.getSize().x, mapTexture.getSize().y), "Rutas Turisticas");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(mapSprite);  // Dibujar el sprite que contiene la textura
        window.display();
    }
}
#include "graphics.h"
#include <iostream>

graphics::graphics() {
    if (!mapTexture.loadFromFile("MapCR.png")) {
        std::cout << "Error al cargar la imagen MapCR.png" << std::endl;
    }
    else {
        mapSprite.setTexture(mapTexture);
        mapSprite.setPosition(0, 0);
    }

    addButton(1196, 5, 50, 40, sf::Color::Red, "Boton1");
    addButton(1196, 50, 50, 40, sf::Color::Green, "Boton2");
    addButton(1196, 95, 50, 40, sf::Color::Blue, "Boton3");
}

void graphics::addButton(float x, float y, float width, float height, sf::Color color, const std::string& name) {
    if (buttonCount < MAX_BUTTONS) {
        buttons[buttonCount] = Button(x, y, width, height, color, name);
        buttonCount++;
    }
    else {
        std::cout << "No se pueden agregar más botones. Máximo alcanzado: " << MAX_BUTTONS << std::endl;
    }
}

void graphics::displayMap() {
    sf::RenderWindow window(sf::VideoMode(mapTexture.getSize().x, mapTexture.getSize().y), "Rutas Turisticas");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    int mouseX = event.mouseButton.x;
                    int mouseY = event.mouseButton.y;

                    for (int i = 0; i < buttonCount; i++) {
                        sf::FloatRect bounds = buttons[i].shape.getGlobalBounds();
                        if (bounds.contains(mouseX, mouseY)) {
                            std::cout << buttons[i].name << " presionado!" << std::endl;
                        }
                    }
                }
            }
        }

        window.clear();

        window.draw(mapSprite);

        for (int i = 0; i < buttonCount; i++) {
            window.draw(buttons[i].shape);
        }

        window.display();
    }
}

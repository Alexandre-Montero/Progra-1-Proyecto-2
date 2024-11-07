#include "graphics.h"

Button::Button(float x, float y, float width, float height, sf::Texture& texture, const std::string& buttonName) {
    shape.setSize(sf::Vector2f(width, height));
    shape.setPosition(x, y);
    shape.setTexture(&texture);
    name = buttonName;
}

Point::Point(float x, float y, int radius, sf::Color color, const std::string& pointName) {
    shape.setRadius(radius);
    shape.setPosition(x, y);
    shape.setFillColor(color);
    name = pointName;
}

graphics::graphics() {
    if (!mapTexture.loadFromFile("MapCR.png")) {
        cout << "Error al cargar la imagen MapCR.png\n";
    }
    else {
        mapSprite.setTexture(mapTexture);
        mapSprite.setPosition(0, 0);
    }

    if (!addButtonTexture.loadFromFile("AddButton.png")) {
        cout << "Error al cargar la imagen addButton.png\n";
    }
    if (!editButtonTexture.loadFromFile("editButton.png")) {
        cout << "Error al cargar la imagen editButton.png\n";
    }
    if (!deleteButtonTexture.loadFromFile("deleteButton.png")) {
        cout << "Error al cargar la imagen deleteButton\n";
    }
    if (!colorsButtonTexture.loadFromFile("colorButton.png")) {
        cout << "Error al cargar la imagen colorButton.png\n";
    }

    addButton(1196, 135, 50, 40, addButtonTexture, "Agregar Ruta");
    addButton(1196, 180, 50, 40, editButtonTexture, "Editar Ruta");
    addButton(1196, 225, 50, 40, deleteButtonTexture, "Borrar Ruta");
    addButton(15, 400, 50, 40, colorsButtonTexture, "Paleta de Colores");

    addPoint(1150, 135, 6, sf::Color::Red, "Prueba");
}

void graphics::addButton(float x, float y, float width, float height, sf::Texture& texture, const std::string& name) {
    if (buttonCount < MAX_BUTTONS) {
        buttons[buttonCount] = Button(x, y, width, height, texture, name);
        buttonCount++;
    } else {
        cout << "No se pueden agregar mas botones. Maximo alcanzado: " << MAX_BUTTONS << std::endl;
    }
}

void graphics::addPoint(float x, float y, int radius, sf::Color color, const std::string& name) {
    if (pointCount < MAX_POINTS) {
        points[pointCount] = Point(x, y, radius, color, name);
        pointCount++;
    }
    else {
        std::cout << "No se pueden agregar mas puntos. Maximo alcanzado: " << MAX_POINTS << std::endl;
    }
}


void graphics::displayMap() {
    sf::RenderWindow window(sf::VideoMode(mapTexture.getSize().x, mapTexture.getSize().y), "Rutas Turisticas");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
                int mouseX = event.mouseButton.x;
                int mouseY = event.mouseButton.y;

                std::cout << "Clic en las coordenadas: (" << mouseX << ", " << mouseY << ")" << std::endl;

            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                int mouseX = event.mouseButton.x;
                int mouseY = event.mouseButton.y;

                for (int i = 0; i < buttonCount; i++) {
                    sf::FloatRect bounds = buttons[i].shape.getGlobalBounds();
                    if (bounds.contains(static_cast<float>(mouseX), static_cast<float>(mouseY))) {
                        std::cout << buttons[i].name << " presionado!" << std::endl;
                    }
                }
            }
        }

        window.clear();

        window.draw(mapSprite);

        for (int i = 0; i < buttonCount; i++) {
            window.draw(buttons[i].shape);
        }

        for (int i = 0; i < pointCount; i++) {
            window.draw(points[i].shape);
        }

        window.display();
    }
}

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

graphics::graphics() : fileManager("Archivo de rutas.txt") {
    if (!mapTexture.loadFromFile("MapCR.png")) {
        std::cout << "Error al cargar la imagen MapCR.png\n";
    }
    else {
        mapSprite.setTexture(mapTexture);
        mapSprite.setPosition(0, 0);
    }

    if (!addButtonTexture.loadFromFile("AddButton.png")) {
        std::cout << "Error al cargar la imagen addButton.png\n";
    }
    if (!editButtonTexture.loadFromFile("editButton.png")) {
        std::cout << "Error al cargar la imagen editButton.png\n";
    }
    if (!deleteButtonTexture.loadFromFile("deleteButton.png")) {
        std::cout << "Error al cargar la imagen deleteButton.png\n";
    }
    if (!colorsButtonTexture.loadFromFile("colorButton.png")) {
        std::cout << "Error al cargar la imagen colorButton.png\n";
    }

    addButton(1196, 135, 50, 40, addButtonTexture, "Agregar Ruta");
    addButton(1196, 180, 50, 40, editButtonTexture, "Editar Ruta");
    addButton(1196, 225, 50, 40, deleteButtonTexture, "Borrar Ruta");
    addButton(1196, 270, 50, 40, colorsButtonTexture, "Cambiar Colores");
    fileManager.createFile();
    fileManager.loadRoutes(routeList);
}

void graphics::displayMap() {
    sf::RenderWindow window(sf::VideoMode(mapTexture.getSize().x, mapTexture.getSize().y), "Rutas Turísticas");
    sf::Color lineAndPointColor = sf::Color::Green;
    float lineThickness = 5.0f;
    bool isEditMode = false;
    bool isAddRouteMode = false;

    sf::Clock delayClock;
    sf::Clock inactivityClock;
    sf::Time delayTime = sf::milliseconds(500);
    sf::Time idleTimeout = sf::seconds(5);
    bool waitForFirstClick = false;

    std::vector<sf::Color> colorOptions = { sf::Color::Green, sf::Color::Red, sf::Color::Blue, sf::Color::Yellow, sf::Color::Black, sf::Color::Cyan };
    int currentColorIndex = 0;

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

                        if (buttons[i].name == "Agregar Ruta") {
                            isAddRouteMode = true;
                            waitForFirstClick = true;
                            delayClock.restart();
                            inactivityClock.restart();
                            fileManager.askForRouteName(routeList);
                            fileManager.saveRoutes(routeList);
                        }

                        if (buttons[i].name == "Editar Ruta") {
                            isEditMode = !isEditMode;
                            std::cout << "Modo de edicion " << (isEditMode ? "activado" : "desactivado") << std::endl;
                            if (isEditMode) {
                                fileManager.editRoute(routeList);
                                fileManager.saveRoutes(routeList);
                            }
                        }

                        if (buttons[i].name == "Borrar Ruta") {
                            fileManager.deleteRoute(routeList);
                            fileManager.saveRoutes(routeList);
                        }

                        if (buttons[i].name == "Cambiar Colores") {
                            currentColorIndex = (currentColorIndex + 1) % colorOptions.size();
                            lineAndPointColor = colorOptions[currentColorIndex];
                            std::cout << "Color cambiado a: " << currentColorIndex << std::endl;
                        }
                    }
                }

                if (isAddRouteMode && !waitForFirstClick && delayClock.getElapsedTime() >= delayTime) {
                    addPoint(static_cast<float>(mouseX), static_cast<float>(mouseY), 6, lineAndPointColor, "Nuevo Punto");
                    calculateSplinePoints();
                }

                waitForFirstClick = false;
                inactivityClock.restart();
            }
        }

        if (isAddRouteMode && inactivityClock.getElapsedTime() >= idleTimeout) {
            isAddRouteMode = false;
            std::cout << "Modo de agregar ruta desactivado por inactividad" << std::endl;
        }

        window.clear();

        window.draw(mapSprite);

        for (int i = 0; i < buttonCount; i++) {
            window.draw(buttons[i].shape);
        }

        for (int i = 0; i < pointCount; i++) {
            points[i].shape.setFillColor(lineAndPointColor);
            window.draw(points[i].shape);
        }

        if (splinePointCount >= 2) {
            for (int i = 0; i < splinePointCount - 1; i++) {
                sf::Vector2f point1 = splinePoints[i];
                sf::Vector2f point2 = splinePoints[i + 1];
                sf::Vector2f direction = point2 - point1;
                float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

                sf::RectangleShape rectangle(sf::Vector2f(length, lineThickness));

                rectangle.setPosition(point1);

                float angle = std::atan2(direction.y, direction.x) * 180.0f / 3.14159265358979323846;
                rectangle.setRotation(angle);

                rectangle.setFillColor(lineAndPointColor);

                window.draw(rectangle);
            }
        }

        window.display();
    }
}
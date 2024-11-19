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

    fileManager.createFile();
    fileManager.loadRoutes(routeList);
}

void graphics::addButton(float x, float y, float width, float height, sf::Texture& texture, const std::string& name) {
    if (buttonCount < MAX_BUTTONS) {
        buttons[buttonCount] = Button(x, y, width, height, texture, name);
        buttonCount++;
    }
    else {
        std::cout << "No se pueden agregar mas botones. Maximo alcanzado: " << MAX_BUTTONS << std::endl;
    }
}

void graphics::addPoint(float x, float y, int radius, sf::Color color, const std::string& name) {
    if (pointCount < MAX_POINTS) {
        points[pointCount] = Point(x, y, radius, color, name);
        pointPositions[pointCount] = sf::Vector2f(x, y);
        pointCount++;
    }
    else {
        std::cout << "No se pueden agregar mas puntos. Maximo alcanzado: " << MAX_POINTS << std::endl;
    }
}

void graphics::calculateSplinePoints() {
    splinePointCount = 0;

    if (pointCount < 2) return;

    for (int i = 0; i < pointCount - 1 && splinePointCount < MAX_POINTS * 20; i++) {
        sf::Vector2f p0 = (i == 0) ? pointPositions[i] : pointPositions[i - 1];
        sf::Vector2f p1 = pointPositions[i];
        sf::Vector2f p2 = pointPositions[i + 1];
        sf::Vector2f p3 = (i + 2 < pointCount) ? pointPositions[i + 2] : pointPositions[i + 1];

        for (int j = 0; j < 20 && splinePointCount < MAX_POINTS * 20; j++) {
            float t = j / 20.0f;
            float tt = t * t;
            float ttt = tt * t;

            float q1 = -ttt + 2 * tt - t;
            float q2 = 3 * ttt - 5 * tt + 2;
            float q3 = -3 * ttt + 4 * tt + t;
            float q4 = ttt - tt;

            float x = 0.5f * (p0.x * q1 + p1.x * q2 + p2.x * q3 + p3.x * q4);
            float y = 0.5f * (p0.y * q1 + p1.y * q2 + p2.y * q3 + p3.y * q4);

            splinePoints[splinePointCount++] = sf::Vector2f(x, y);
        }
    }
}

void graphics::displayMap() {
    sf::RenderWindow window(sf::VideoMode(mapTexture.getSize().x, mapTexture.getSize().y), "Rutas Turísticas");
    sf::Color lineAndPointColor = sf::Color::Green;
    float lineThickness = 5.0f;
    bool isEditMode = false;
    bool isAddRouteMode = false;
    bool colorPaletteActive = false;

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

                        if (buttons[i].name == "Paleta de Colores" && isEditMode) {
                            colorPaletteActive = true;
                            currentColorIndex = (currentColorIndex + 1) % colorOptions.size();
                            lineAndPointColor = colorOptions[currentColorIndex];
                            std::cout << "Color cambiado a " << currentColorIndex << std::endl;
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
            if (buttons[i].name == "Paleta de Colores" && !isEditMode) {
                continue;
            }
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
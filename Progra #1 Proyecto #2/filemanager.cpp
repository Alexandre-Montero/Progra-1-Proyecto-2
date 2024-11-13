#include "filemanager.h"

FileManager::FileManager(const std::string& filename) : filename(filename) {}

void FileManager::saveRoutes(const RouteList& routeList) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo para guardar las rutas.\n";
        return;
    }

    RouteNode* currentRoute = routeList.getHead();
    while (currentRoute) {
        file << "Route: " << currentRoute->getName() << "\n";

        PointNode* currentPoint = currentRoute->getPointList().getHead();
        while (currentPoint) {
            file << "Point: " << currentPoint->getName() << " "
                << currentPoint->getX() << " "
                << currentPoint->getY() << "\n";
            currentPoint = currentPoint->getNext();
        }

        currentRoute = currentRoute->getNext();
    }
    file.close();
}

void FileManager::loadRoutes(RouteList& routeList) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo para cargar las rutas.\n";
        return;
    }

    std::string line;
    RouteNode* currentRoute = nullptr;

    while (std::getline(file, line)) {
        if (line.rfind("Route: ", 0) == 0) {
            std::string routeName = line.substr(7);
            routeList.insertRoute(routeName);
            currentRoute = routeList.getHead();

            while (currentRoute && currentRoute->getNext()) {
                currentRoute = currentRoute->getNext();
            }
        }
        else if (line.rfind("Point: ", 0) == 0 && currentRoute) {
            std::istringstream iss(line.substr(7));
            std::string pointName;
            int x, y;
            iss >> pointName >> x >> y;
            currentRoute->getPointList().insertPoint(pointName, x, y);
        }
    }

    file.close();
}

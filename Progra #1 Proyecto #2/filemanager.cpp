#include "filemanager.h"

FileManager::FileManager(const std::string& filename) : filename(filename) {}


void FileManager::createFile() {

    std::ifstream existingFile(filename);
    if (existingFile.is_open()) {
        std::cout << "El archivo ya existe: " << filename << "\n";
        existingFile.close();
        return; 
    }

    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error al crear el archivo.\n";
        return;
    }
    std::cout << "Archivo creado correctamente: " << filename << "\n";
    file.close();
}


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

void FileManager::askForRouteName(RouteList& routeList) {
    std::string routeName;
    std::cout << "Introduce el nombre de la ruta (por ejemplo, 'Ruta #1'): ";
    std::getline(std::cin, routeName);  

    routeList.insertRoute(routeName);  
    std::cout << "Ruta '" << routeName << "' agregada correctamente.\n";
}

void FileManager::editRoute(RouteList& routeList) {
    std::string oldRoute;
    std::string NewRoute;

    cout << "Introduce el nombre de la ruta que desea editar:\n";
    std::getline(std::cin, oldRoute);

    RouteNode* routeToEdit = routeList.searchRoute(oldRoute);
    if (!routeToEdit) {
        std::cout << "Ruta no encontrada\n";
        return;
    }

    std::cout << "Introduce el nuevo nombre de la ruta:\n";
    std::getline(std::cin, NewRoute);

    routeToEdit->setName(NewRoute);

    saveRoutes(routeList);

    std::cout << "Ruta actualizada correcta a " << NewRoute << std::endl;
}

void FileManager::deleteRoute(RouteList& routeList) {
    std::string routeName;
    std::cout << "Introduce el nombre de la ruta que deseas eliminar: ";
    std::getline(std::cin, routeName);

    RouteNode* routeToDelete = routeList.searchRoute(routeName);
    if (!routeToDelete) {
        std::cout << "Ruta no encontrada.\n";
        return;
    }

    routeList.removeRoute(routeName);

    saveRoutes(routeList);
    std::cout << "Ruta eliminada correctamente: " << routeName << "\n";
}

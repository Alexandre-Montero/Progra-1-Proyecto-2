#include <iostream>
#include "filemanager.h"
#include "graphics.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace std;

int main() {
	graphics Map;
	Map.displayMap();
	FileManager fileOfRutes("Archivo de rutas.txt");
	fileOfRutes.createFile();
	RouteList routeList;
	fileOfRutes.askForRouteName(routeList);
	fileOfRutes.saveRoutes(routeList);
	return 0;
}
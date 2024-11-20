#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "routenode.h" 

class RouteList;

class FileManager {
private:
    std::string filename;

public:
    FileManager(const std::string& filename);

    void saveRoutes(const RouteList& routeList);
    void loadRoutes(RouteList& routeList);

    void createFile();
    void askForRouteName(RouteList& routeList);
    void editRoute(RouteList& routeList);
    void deleteRoute(RouteList& routeList);
};

#endif // FILEMANAGER_H



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
<<<<<<< HEAD
    void createFile();
    void askForRouteName(RouteList& routeList);
};

#endif // FILEMANAGER_H
=======
};

#endif // FILEMANAGER_H
>>>>>>> 10fb90c17ac632f56158ead0ec89a270a1bd5b53

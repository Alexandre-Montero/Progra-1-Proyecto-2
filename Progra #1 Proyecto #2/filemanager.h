// FileManager.h
#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class FileManager {
private:
    string fileName;

public:
    
    FileManager(const string& nameOfFile);

   
    void createFile();
};

#endif 

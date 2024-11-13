#include "filemanager.h"


FileManager::FileManager(const string& nameOfFile) : fileName(nameOfFile) {}


void FileManager::createFile() {
    ofstream file(fileName); 
    if (file.is_open()) {
        file << "Archivo de rutas!\n";
        file.close();
       
    }
    else {
        cout << "Error al crear el archivo\n";
    }
}


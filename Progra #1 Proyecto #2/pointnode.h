#ifndef POINTNODE_H
#define POINTNODE_H

#include <iostream>

using namespace std;

class PointNode {
private:
    std::string name;
    int x;
    int y;
    PointNode* next;
    PointNode* prev;

public:
    PointNode();
    PointNode(std::string name, int x, int y);

    std::string getName() const;
    int getX() const;
    int getY() const;
    PointNode* getNext() const;
    PointNode* getPrev() const;

    void setName(std::string name);
    void setX(int x);
    void setY(int y);
    void setNext(PointNode* next);
    void setPrev(PointNode* prev);

};

class PointList {
private:
    PointNode* head;

public:
    PointList();
    ~PointList();  

    PointNode* getHead() const;
    void insertPoint(std::string name, int x, int y);
    bool isUniqueName(std::string name) const;
    void displayPoints() const;

};

#endif
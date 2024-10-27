#ifndef RUTENODE_H
#define RUTENODE_h

#include <iostream>
#include "pointnode.h"

using namespace std;

class RouteNode {
private:
    string name;
    PointList pointList;
    RouteNode* next;
    RouteNode* prev;

public:
    RouteNode();
    RouteNode(string name);

    string getName();
    PointList& getPointList();
    RouteNode* getNext();
    RouteNode* getPrev();

    void setName(string name);
    void setPointList(PointList pointList);
    void setNext(RouteNode* next);
    void setPrev(RouteNode* prev);
};

class RouteList {
private:
    RouteNode* head;

public:
    RouteList();

    void insertRoute(string name);
    RouteNode* searchRoute(string name);
    bool isUniqueName(string name);
    void insertPointToRoute(string name);
    void removeRoute(string name);
    void displayRoutes();
};

#endif
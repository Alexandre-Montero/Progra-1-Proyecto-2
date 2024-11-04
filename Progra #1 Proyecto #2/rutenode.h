#ifndef ROUTENODE_H
#define ROUTENODE_H

#include <iostream>
#include "pointnode.h"

using namespace std;

class RouteNode {
private:
    std::string name;
    PointList pointList;
    RouteNode* next;
    RouteNode* prev;

public:
    RouteNode();
    RouteNode(std::string name);

    std::string getName() const;
    PointList& getPointList();
    RouteNode* getNext() const;
    RouteNode* getPrev() const;

    void setName(std::string name);
    void setPointList(const PointList& pointList);
    void setNext(RouteNode* next);
    void setPrev(RouteNode* prev);

};

class RouteList {
private:
    RouteNode* head;

public:
    RouteList();
    ~RouteList();

    RouteNode* getHead() const;
    void insertRoute(std::string name);
    RouteNode* searchRoute(const std::string& name) const;
    bool isUniqueName(const std::string& name) const;
    void insertPointToRoute(std::string routeName);
    void removeRoute(const std::string& name);
    void displayRoutes() const;

};

#endif
#include "rutenode.h"

// RuteNode //

RouteNode::RouteNode() {
    this->next = nullptr;
    this->prev = nullptr;
}

RouteNode::RouteNode(string name) {
    this->name = name;
    this->next = nullptr;
    this->prev = nullptr;
}

RouteList::~RouteList() {
    RouteNode* current = head;
    while (current != nullptr) {
        RouteNode* next = current->getNext();
        delete current;
        current = next;
    }
}

string RouteNode::getName() const{
    return this->name;
}

PointList& RouteNode::getPointList() {
    return this->pointList;
}

RouteNode* RouteNode::getNext() const{
    return this->next;
}

RouteNode* RouteNode::getPrev() const{
    return this->prev;
}

void RouteNode::setName(string name) {
    this->name = name;
}

void RouteNode::setPointList(const PointList& pointList) {
    this->pointList = pointList;
}

void RouteNode::setNext(RouteNode* next) {
    this->next = next;
}

void RouteNode::setPrev(RouteNode* prev) {
    this->prev = prev;
}

// RouteList //

RouteNode* RouteList::getHead() const {
    return head;
}

RouteList::RouteList() {
    this->head = nullptr;
}

void RouteList::insertRoute(string name) {
    RouteNode* newNode = new RouteNode(name);
    if (head == nullptr) {
        head = newNode;
    }
    else {
        RouteNode* current = head;
        while (current->getNext() != nullptr) {
            current = current->getNext();
        }
        current->setNext(newNode);
        newNode->setPrev(current);
    }
}

RouteNode* RouteList::searchRoute(const string& name) const{
    RouteNode* current = head;
    while (current != nullptr) {
        if (current->getName() == name) {
            return current;
        }
        current = current->getNext();
    }
    return nullptr;
}

bool RouteList::isUniqueName(const string& name) const{
    RouteNode* current = head;
    while (current != nullptr) {
        if (!current->getPointList().isUniqueName(name)) {
            return false;
        }
        current = current->getNext();
    }
    return true;
}

void RouteList::insertPointToRoute(string routeName) {
    RouteNode* current = head;
    while (current != nullptr && current->getName() != routeName) {
        current = current->getNext();
    }
    if (current != nullptr) {
        string pointName;
        cout << "Nombre del punto: ";
        cin >> pointName;
        if (isUniqueName(pointName)) {
            current->getPointList().insertPoint(pointName, 50, 100);
        }
    }
}

void RouteList::removeRoute(const string& name) {
    if (head == nullptr) return;

    if (head->getName() == name) {
        RouteNode* temp = head;
        head = head->getNext();
        delete temp;
        return;
    }

    RouteNode* current = head->getNext();
    while (current != nullptr) {
        if (current->getName() == name) {
            current->getPrev()->setNext(current->getNext());
            if (current->getNext() != nullptr) {
                current->getNext()->setPrev(current->getPrev());
            }
            delete current;
            return;
        }
        current = current->getNext();
    }
}

void RouteList::displayRoutes() const{
    RouteNode* current = head;
    while (current != nullptr) {
        std::cout << current->getName() << ", ";
        current = current->getNext();
    }
}
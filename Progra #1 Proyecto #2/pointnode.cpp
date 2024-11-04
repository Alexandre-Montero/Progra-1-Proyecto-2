#include "pointnode.h"

// PointNode //

PointNode::PointNode() {
    this->next = nullptr;
    this->prev = nullptr;
}

PointNode::PointNode(string name, int x, int y) {
    this->name = name;
    this->x = x;
    this->y = y;
    this->next = nullptr;
    this->prev = nullptr;
}

string PointNode::getName() const{
    return this->name;
}

int PointNode::getX() const{
    return this->x;
}

int PointNode::getY() const{
    return this->y;
}

PointNode* PointNode::getNext() const{
    return this->next;
}

PointNode* PointNode::getPrev() const{
    return this->prev;
}

void PointNode::setName(string name) {
    this->name = name;
}

void PointNode::setX(int x) {
    this->x = x;
}

void PointNode::setY(int y) {
    this->y = y;
}

void PointNode::setNext(PointNode* next) {
    this->next = next;
}

void PointNode::setPrev(PointNode* prev) {
    this->prev = prev;
}

// PointList //

PointNode* PointList::getHead() const {
    return head;
}

PointList::PointList() {
    this->head = nullptr;
}

PointList::~PointList() {
    PointNode* current = head;
    while (current != nullptr) {
        PointNode* next = current->getNext();
        delete current;
        current = next;
    }
}

void PointList::insertPoint(string name, int x, int y) {
    PointNode* newNode = new PointNode(name, x, y);
    if (head == nullptr) {
        head = newNode;
    }
    else {
        PointNode* current = head;
        while (current->getNext() != nullptr) {
            current = current->getNext();
        }
        current->setNext(newNode);
        newNode->setPrev(current);
    }
}

bool PointList::isUniqueName(std::string name) const {
    PointNode* current = head;
    while (current != nullptr) {
        if (current->getName() == name) {
            return false;
        }
        current = current->getNext();
    }
    return true;
}

void PointList::displayPoints() const{
    PointNode* current = head;
    while (current != nullptr) {
        std::cout << current->getName() << ", ";
        current = current->getNext();
    }
}
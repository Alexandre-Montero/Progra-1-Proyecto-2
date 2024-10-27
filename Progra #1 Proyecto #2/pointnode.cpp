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

string PointNode::getName() {
    return this->name;
}

int PointNode::getX() {
    return this->x;
}

int PointNode::getY() {
    return this->y;
}

PointNode* PointNode::getNext() {
    return this->next;
}

PointNode* PointNode::getPrev() {
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

PointList::PointList() {
    this->head = nullptr;
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

bool PointList::isUniqueName(string name) {
    PointNode* current = head;
    while (current != nullptr) {
        if (current->getName() == name) {
            return false;
        }
        current = current->getNext();
    }
    return true;
}

void PointList::displayPoints() {
    PointNode* current = head;
    while (current != nullptr) {
        std::cout << current->getName() << ", ";
        current = current->getNext();
    }
}
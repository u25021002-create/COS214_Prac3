#include "EventGroup.h"
#include <algorithm>
#include <iostream>

EventGroup::EventGroup(const std::string& name) : EventComponent(name) {}

EventGroup::~EventGroup() {
    for (EventComponent* child : children) {
        delete child;
    }
    children.clear();
}

void EventGroup::add(EventComponent* component) {
    children.push_back(component);
}

void EventGroup::remove(EventComponent* component) {
    children.erase(std::remove(children.begin(), children.end(), component),
                    children.end());
}

void EventGroup::open() {
    open_ = true;
    for (EventComponent* child : children) child->open();
}

void EventGroup::close() {
    open_ = false;
    for (EventComponent* child : children) child->close();
}

void EventGroup::reportStatus() const {
    std::cout << "[Group] " << name << " (" << (open_ ? "OPEN" : "CLOSED")
              << ", capacity=" << getCapacity() << ")\n";
    for (const EventComponent* child : children) {
        child->reportStatus();
    }
}

int EventGroup::getCapacity() const {
    int total = 0;
    for (const EventComponent* child : children) total += child->getCapacity();
    return total;
}

size_t EventGroup::childCount() const { return children.size(); }

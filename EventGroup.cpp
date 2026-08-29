#include "EventGroup.h"
#include "EventNotice.h"
#include <algorithm>
#include <iostream>

EventGroup::EventGroup(const std::string& name) : EventComponent(name) {}

EventGroup::~EventGroup() {
    for (EventComponent* child : children) {
        // Drop the registration first so no notice can reach a dying child.
        Observer* asObserver = dynamic_cast<Observer*>(child);
        if (asObserver != NULL) detach(asObserver);
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
    Observer* asObserver = dynamic_cast<Observer*>(component);
    if (asObserver != NULL) detach(asObserver);
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

void EventGroup::update(const EventNotice& notice) {
    applyLocalPolicy(notice);
    notify(notice);
}

void EventGroup::applyLocalPolicy(const EventNotice& notice) {
    // The area's own bookkeeping, so that a status report taken afterwards
    // agrees with the notices the area has received.
    if (notice.getType() == OPEN)  open_ = true;
    if (notice.getType() == CLOSE || notice.getType() == EVACUATE) open_ = false;

    std::cout << "[Group] " << name << " received "
              << noticeTypeName(notice.getType()) << " from "
              << notice.getSource();
    if (getObserverCount() == 0) {
        std::cout << " -> nothing is registered here\n";
    } else {
        std::cout << " -> passing it to " << getObserverCount()
                  << " observer(s)\n";
    }
}

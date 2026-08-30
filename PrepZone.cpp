#include "PrepZone.h"
#include "EventNotice.h"
#include "Observer.h"
#include <iostream>

PrepZone::PrepZone(const std::string& name)
    : EventGroup(name), vehiclesReady(0) {}

PrepZone::~PrepZone() {}

bool PrepZone::releaseToDisplay(EventComponent* unit, EventGroup* target) {
    if (unit == NULL || target == NULL) return false;

    Observer* asObserver = dynamic_cast<Observer*>(unit);
    if (asObserver != NULL) detach(asObserver);   // stop notifying it from here
    remove(unit);                                 // give up ownership
    target->add(unit);                            // the target now owns it
    if (asObserver != NULL) target->attach(asObserver);   // and now notifies it

    if (vehiclesReady > 0) --vehiclesReady;
    std::cout << "[Group] " << name << " released " << unit->getName()
              << " to " << target->getName()
              << " (ownership and registration both moved).\n";
    return true;
}

void PrepZone::applyLocalPolicy(const EventNotice& notice) {
    if (notice.getType() == OPEN) {
        vehiclesReady = getObserverCount();
        std::cout << "[Group] " << name << " reports " << vehiclesReady
                  << " exhibit(s) prepared and ready to release.\n";
    } else if (notice.getType() == LOW_STOCK) {
        std::cout << "[Group] " << name << " logistics: preparing a restock "
                  << "run for " << notice.getSource() << " (" << notice.getMessage()
                  << ").\n";
    } else {
        EventGroup::applyLocalPolicy(notice);
    }
}

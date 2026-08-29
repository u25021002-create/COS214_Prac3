#include "DisplayZone.h"
#include "EventNotice.h"
#include <iostream>

DisplayZone::DisplayZone(const std::string& name, bool outdoor)
    : EventGroup(name), outdoor(outdoor) {}

DisplayZone::~DisplayZone() {}

void DisplayZone::shelterAll() {
    std::cout << "[Group] " << name << " is bringing its exhibits under cover.\n";
    notify(EventNotice(WEATHER_ALERT, "cover the exhibits", name, 2));
}

void DisplayZone::applyLocalPolicy(const EventNotice& notice) {
    if (notice.getType() == WEATHER_ALERT && outdoor) {
        std::cout << "[Group] " << name
                  << " is outdoor: sheltering before passing the alert on -> "
                  << getObserverCount() << " observer(s)\n";
    } else {
        EventGroup::applyLocalPolicy(notice);
    }
}

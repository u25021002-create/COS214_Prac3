#include "MedicalTent.h"
#include "EventNotice.h"
#include <iostream>

MedicalTent::MedicalTent(const std::string& name, int capacity)
    : EventUnit(name, capacity), alertLevel(0) {}

void MedicalTent::open() {
    open_ = true;
    std::cout << name << ": medical tent staffed and operational.\n";
}

void MedicalTent::close() {
    // Medical stays open even when "close" is called on the tree, unless
    // this is a full evacuation; that decision is made in Task 3/4 via
    // notice-specific update() logic, not here.
    std::cout << name << ": medical remains operational.\n";
}

void MedicalTent::reportStatus() const {
    std::cout << "[MedicalTent] " << name << " - ALWAYS STAFFED"
              << ", alert level=" << alertLevel
              << ", capacity=" << capacity << "\n";
}

void MedicalTent::update(const EventNotice& notice) {
    switch (notice.getType()) {
        case OPEN:
            open();
            break;
        case WEATHER_ALERT:
        case EVACUATE:
            raiseAlertLevel();
            break;
        case PAUSE:
        case CAPACITY_ALERT:
            std::cout << name << ": stays operational; a first-aid post is "
                      << "never paused.\n";
            break;
        case RESUME:
            alertLevel = 0;
            std::cout << name << ": stood down to normal cover.\n";
            break;
        default:
            break;
    }
}

void MedicalTent::raiseAlertLevel() {
    ++alertLevel;
    std::cout << name << ": stays open, alert level raised to "
              << alertLevel << ".\n";
}

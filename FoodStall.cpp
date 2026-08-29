#include "FoodStall.h"
#include "EventNotice.h"
#include <iostream>

FoodStall::FoodStall(const std::string& name, int capacity)
    : EventUnit(name, capacity), cookingActive(false) {}

void FoodStall::open() {
    open_ = true;
    cookingActive = true;
    std::cout << name << ": serving food, cooking equipment active.\n";
}

void FoodStall::close() {
    open_ = false;
    cookingActive = false;
    std::cout << name << ": stall closed, cooking equipment shut down.\n";
}

void FoodStall::reportStatus() const {
    std::cout << "[FoodStall] " << name << " - "
              << (open_ ? "SERVING" : "CLOSED")
              << ", cooking=" << (cookingActive ? "ON" : "OFF")
              << ", capacity=" << capacity << "\n";
}

void FoodStall::update(const EventNotice& notice) {
    switch (notice.getType()) {
        case OPEN:
        case RESUME:
            open();
            break;
        case WEATHER_ALERT:
            // Open flame under canvas in high wind: unlike MerchStall, this
            // stall must shut down on the same notice.
            std::cout << name << ": open flame is unsafe in this weather.\n";
            close();
            break;
        case PAUSE:
        case EVACUATE:
            close();
            break;
        default:
            break;
    }
}

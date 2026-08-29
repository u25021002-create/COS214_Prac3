#include "FoodStall.h"
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

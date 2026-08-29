#include "VehicleDisplay.h"
#include <iostream>

VehicleDisplay::VehicleDisplay(const std::string& name, int capacity)
    : EventUnit(name, capacity), covered(false) {}

void VehicleDisplay::open() {
    open_ = true;
    covered = false;
    std::cout << name << ": display uncovered, vehicles on show.\n";
}

void VehicleDisplay::close() {
    open_ = false;
    covered = true;
    std::cout << name << ": vehicles covered and secured.\n";
}

void VehicleDisplay::reportStatus() const {
    std::cout << "[VehicleDisplay] " << name << " - "
              << (covered ? "COVERED" : "ON DISPLAY")
              << ", capacity=" << capacity << "\n";
}

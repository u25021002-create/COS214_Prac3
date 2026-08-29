#include "DroidShow.h"
#include <iostream>

DroidShow::DroidShow(const std::string& name, int capacity)
    : EventUnit(name, capacity), running(false) {}

void DroidShow::open() {
    open_ = true;
    running = true;
    std::cout << name << ": droid show running.\n";
}

void DroidShow::close() {
    open_ = false;
    running = false;
    std::cout << name << ": droid show paused.\n";
}

void DroidShow::reportStatus() const {
    std::cout << "[DroidShow] " << name << " - "
              << (running ? "RUNNING" : "PAUSED")
              << ", capacity=" << capacity << "\n";
}

#include "MainGate.h"
#include <iostream>

MainGate::MainGate(const std::string& name, int capacity)
    : EventUnit(name, capacity), admitted(0) {}

void MainGate::open() {
    open_ = true;
    std::cout << name << ": now admitting attendees.\n";
}

void MainGate::close() {
    open_ = false;
    std::cout << name << ": gate closed, no new admissions.\n";
}

void MainGate::reportStatus() const {
    std::cout << "[MainGate] " << name << " - "
              << (open_ ? "ADMITTING" : "CLOSED")
              << ", admitted=" << admitted << "/" << capacity << "\n";
}

bool MainGate::admit(int count) {
    if (!open_ || admitted + count > capacity) return false;
    admitted += count;
    return true;
}

#include "AutographBooth.h"
#include <iostream>
#include <algorithm>

AutographBooth::AutographBooth(const std::string& name, int capacity)
    : EventUnit(name, capacity), queueLength(0) {}

void AutographBooth::open() {
    open_ = true;
    std::cout << name << ": now taking guests (queue=" << queueLength << ").\n";
}

void AutographBooth::close() {
    open_ = false;
    std::cout << name << ": queue paused, no new guests admitted.\n";
}

void AutographBooth::reportStatus() const {
    std::cout << "[AutographBooth] " << name << " - "
              << (open_ ? "OPEN" : "PAUSED")
              << ", queue=" << queueLength << ", capacity=" << capacity << "\n";
}

void AutographBooth::joinQueue(int count) {
    queueLength = std::min(capacity, queueLength + count);
}

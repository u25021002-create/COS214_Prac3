#include "AutographBooth.h"
#include "EventNotice.h"
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

void AutographBooth::update(const EventNotice& notice) {
    switch (notice.getType()) {
        case OPEN:
        case RESUME:
            open();
            break;
        case CAPACITY_ALERT:
        case PAUSE:
            // Those already queuing are still served; only new guests stop.
            close();
            break;
        case EVACUATE:
            queueLength = 0;
            close();
            break;
        case WEATHER_ALERT:
            std::cout << name << ": indoors, the queue is unaffected.\n";
            break;
        default:
            break;
    }
}

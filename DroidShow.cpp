#include "DroidShow.h"
#include "EventNotice.h"
#include <iostream>

DroidShow::DroidShow(const std::string& name, int capacity)
    : EventUnit(name, capacity), running(false), nextShowTime("12:00") {}

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
              << ", next show=" << nextShowTime
              << ", capacity=" << capacity << "\n";
}

void DroidShow::update(const EventNotice& notice) {
    switch (notice.getType()) {
        case OPEN:
        case RESUME:
            open();
            break;
        case SCHEDULE_CHANGE:
            // The only unit that treats the notice's message as data.
            nextShowTime = notice.getMessage();
            std::cout << name << ": next performance moved to "
                      << nextShowTime << ".\n";
            break;
        case PAUSE:
        case WEATHER_ALERT:
        case EVACUATE:
            close();
            break;
        default:
            break;
    }
}

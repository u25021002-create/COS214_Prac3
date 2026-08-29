#include "AnnouncementBooth.h"
#include <iostream>

AnnouncementBooth::AnnouncementBooth(const std::string& name, int capacity)
    : EventUnit(name, capacity) {}

void AnnouncementBooth::open() {
    open_ = true;
    announce("Welcome to Star Wars Fan Day!");
}

void AnnouncementBooth::close() {
    open_ = false;
    announce("Announcements ending for the day. Thank you for attending.");
}

void AnnouncementBooth::reportStatus() const {
    std::cout << "[AnnouncementBooth] " << name << " - "
              << (open_ ? "BROADCASTING" : "SILENT") << "\n";
}

void AnnouncementBooth::announce(const std::string& message) const {
    std::cout << name << " [PA]: " << message << "\n";
}

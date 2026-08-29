#include "EventControl.h"
#include <iostream>

EventControl::EventControl(const std::string& eventName)
    : eventName(eventName), noticesIssued(0) {}

EventControl::~EventControl() {}

void EventControl::issueNotice(NoticeType type, const std::string& message) {
    ++noticesIssued;
    std::cout << "\n[Control] " << eventName << " issues "
              << noticeTypeName(type) << ": " << message << "\n";
    notify(EventNotice(type, message, eventName + " Control", 0));
}

void EventControl::issueSafetyNotice(NoticeType type, const std::string& message,
                                     int severity) {
    ++noticesIssued;
    std::cout << "\n[Control] " << eventName << " issues " << noticeTypeName(type)
              << " (severity " << severity << "): " << message << "\n";
    notify(EventNotice(type, message, eventName + " Control", severity));
}

int EventControl::getNoticesIssued() const { return noticesIssued; }

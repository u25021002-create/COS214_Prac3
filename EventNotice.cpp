#include "EventNotice.h"

const char* noticeTypeName(NoticeType type) {
    switch (type) {
        case OPEN:            return "OPEN";
        case CLOSE:           return "CLOSE";
        case SCHEDULE_CHANGE: return "SCHEDULE_CHANGE";
        case CAPACITY_ALERT:  return "CAPACITY_ALERT";
        case WEATHER_ALERT:   return "WEATHER_ALERT";
        case PAUSE:           return "PAUSE";
        case RESUME:          return "RESUME";
        case EVACUATE:        return "EVACUATE";
        case REASSIGN:        return "REASSIGN";
        case LOW_STOCK:       return "LOW_STOCK";
    }
    return "UNKNOWN";
}

EventNotice::EventNotice(NoticeType type, const std::string& message,
                         const std::string& source, int severity)
    : type(type), message(message), source(source), severity(severity) {}

NoticeType EventNotice::getType() const { return type; }
const std::string& EventNotice::getMessage() const { return message; }
const std::string& EventNotice::getSource() const { return source; }
int EventNotice::getSeverity() const { return severity; }

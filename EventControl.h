#ifndef EVENTCONTROL_H
#define EVENTCONTROL_H

#include "Subject.h"
#include "EventNotice.h"
#include <string>

/**
 * @brief Concrete Subject: the event control centre that raises notices.
 *
 * EventControl is deliberately not an EventComponent. It is not part of the
 * containment tree; it is the coordinator that broadcasts into it. It knows
 * only Observer and EventNotice, so a new kind of unit can be added to the
 * event without changing this class.
 */
class EventControl : public Subject {
public:
    /**
     * @brief Constructs a control centre.
     * @param eventName Name of the event being coordinated.
     */
    explicit EventControl(const std::string& eventName);

    ~EventControl() override;

    /**
     * @brief Raises a routine notice and pushes it to every registered observer.
     * @param type The kind of change.
     * @param message The detail carried with the notice.
     */
    void issueNotice(NoticeType type, const std::string& message);

    /**
     * @brief Raises an urgent notice and pushes it to every registered observer.
     * @param type The kind of change.
     * @param message The detail carried with the notice.
     * @param severity How urgent the notice is.
     */
    void issueSafetyNotice(NoticeType type, const std::string& message, int severity);

    /** @brief Returns how many notices this control centre has issued. */
    int getNoticesIssued() const;

private:
    std::string eventName;
    int noticesIssued;
};

#endif

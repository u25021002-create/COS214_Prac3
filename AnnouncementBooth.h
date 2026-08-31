#ifndef ANNOUNCEMENTBOOTH_H
#define ANNOUNCEMENTBOOTH_H

#include "EventUnit.h"
#include <string>

class EventNotice;

/**
 * @brief Concrete Leaf: PA/announcement booth.
 *
 * Distinct from every other leaf: instead of changing its own physical
 * state on open/close, it broadcasts a message. In Task 3 this becomes the
 * unit that turns received notices into attendee-facing announcements.
 */
class AnnouncementBooth : public EventUnit {
public:
    /**
    * @brief constrcts an announcement booth
    * @param name displays name of booth
    * @param capacity Nominal capc
    */
    AnnouncementBooth(const std::string& name, int capacity);

    void open() override;
    void close() override;
    void reportStatus() const override;

    /** 
     * @brief Broadcasts a message to attendees over the PA system.
     * @param message text to announce
     */
    void announce(const std::string& message) const;

    /**
     * @brief Reacts to a notice pushed by a subject this unit is attached to.
     * @param notice The notice being delivered.
     */
    void update(const EventNotice& notice) override;

};

#endif

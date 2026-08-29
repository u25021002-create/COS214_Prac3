#ifndef ANNOUNCEMENTBOOTH_H
#define ANNOUNCEMENTBOOTH_H

#include "EventUnit.h"
#include <string>

/**
 * @brief Concrete Leaf: PA/announcement booth.
 *
 * Distinct from every other leaf: instead of changing its own physical
 * state on open/close, it broadcasts a message.
 */
class AnnouncementBooth : public EventUnit {
public:
    AnnouncementBooth(const std::string& name, int capacity);

    void open() override;
    void close() override;
    void reportStatus() const override;

    /** @brief Broadcasts a message to attendees over the PA system. */
    void announce(const std::string& message) const;
};

#endif

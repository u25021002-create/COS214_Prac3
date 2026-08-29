#ifndef DROIDSHOW_H
#define DROIDSHOW_H

#include "EventUnit.h"
#include <string>

class EventNotice;

/**
 * @brief Concrete Leaf: live droid demonstration show.
 *
 * Represents an active, running demo. close() pauses the live show rather
 * than shutting the venue down, capturing a distinct "paused" state.
 */
class DroidShow : public EventUnit {
public:
    DroidShow(const std::string& name, int capacity);

    void open() override;
    void close() override;
    void reportStatus() const override;

    /**
     * @brief Reacts to a notice pushed by a subject this unit is attached to.
     * @param notice The notice being delivered.
     */
    void update(const EventNotice& notice) override;

private:
    bool running;
    std::string nextShowTime; ///< Moved by a SCHEDULE_CHANGE notice.
};

#endif

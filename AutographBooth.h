#ifndef AUTOGRAPHBOOTH_H
#define AUTOGRAPHBOOTH_H

#include "EventUnit.h"

class EventNotice;

/**
 * @brief Concrete Leaf: actor/cosplayer meet-and-greet booth.
 *
 * Maintains a simple queue count. Closing the booth pauses queue admission
 * without discarding attendees already queued.
 */
class AutographBooth : public EventUnit {
public:
    AutographBooth(const std::string& name, int capacity);

    void open() override;
    void close() override;
    void reportStatus() const override;

    /** @brief Adds attendees to the booth's queue, capped at capacity. */
    void joinQueue(int count);

    /**
     * @brief Reacts to a notice pushed by a subject this unit is attached to.
     * @param notice The notice being delivered.
     */
    void update(const EventNotice& notice) override;


private:
    int queueLength;
};

#endif

#ifndef AUTOGRAPHBOOTH_H
#define AUTOGRAPHBOOTH_H

#include "EventUnit.h"

class EventNotice;
class AnnouncementBooth;

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

    /**
     * @brief Task 4.4 original feature: queue overflow redirect.
     *
     * Registers an AnnouncementBooth this booth can ask to announce an
     * alternate time slot when joinQueue() would exceed capacity. This is a
     * plain, non-owning collaborator pointer -- not an Observer registration
     * -- kept deliberately separate from the Subject/Observer machinery so
     * it is easy to see this feature does not touch any other class.
     * @param booth The announcement booth to notify on overflow; may be null.
     */
    void setOverflowAnnouncer(AnnouncementBooth* booth);

private:
    int queueLength;
    AnnouncementBooth* overflowAnnouncer; ///< Non-owning; may be null.
};

#endif

#ifndef AUTOGRAPHBOOTH_H
#define AUTOGRAPHBOOTH_H

#include "EventUnit.h"

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

private:
    int queueLength;
};

#endif

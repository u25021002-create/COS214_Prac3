#ifndef DROIDSHOW_H
#define DROIDSHOW_H

#include "EventUnit.h"

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

private:
    bool running;
};

#endif

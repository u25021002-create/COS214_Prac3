#ifndef EVENTUNIT_H
#define EVENTUNIT_H

#include "EventComponent.h"

/**
 * @brief Abstract Leaf base class in the Composite pattern.
 *
 * EventUnit represents a single operational unit at Star Wars Fan Day
 * (e.g. a gate, a stall, a display). It has no children: getCapacity()
 * operates only on this unit's own state. Concrete leaves override
 * open()/close()/reportStatus() to give each unit meaningfully different
 * behaviour.
 */
class EventUnit : public EventComponent {
public:
    /**
     * @brief Constructs a leaf unit.
     * @param name Display name of the unit.
     * @param capacity The maximum capacity/throughput of this unit.
     */
    EventUnit(const std::string& name, int capacity);

    virtual ~EventUnit();

    int getCapacity() const override;

protected:
    int capacity;
};

#endif

#ifndef EVENTUNIT_H
#define EVENTUNIT_H

#include "EventComponent.h"
#include "Observer.h"

/**
 * @brief Abstract Leaf base class in the Composite pattern.
 *
 * EventUnit represents a single operational unit at Star Wars Fan Day
 * (e.g. a gate, a stall, a display). It has no children: getCapacity()
 * operates only on this unit's own state. Concrete leaves override
 * open()/close()/reportStatus() to give each unit meaningfully different
 * behaviour.
 *
 * Task 3: EventUnit is also an Observer. A unit is registered with the area
 * whose notices it must hear, which is a separate decision from which area
 * contains it: EventGroup::add() establishes containment, Subject::attach()
 * establishes notification.
 */
class EventUnit : public EventComponent, public Observer {
public:
    /**
     * @brief Constructs a leaf unit.
     * @param name Display name of the unit.
     * @param capacity The maximum capacity/throughput of this unit.
     */
    EventUnit(const std::string& name, int capacity);

    /** @brief Virtual destructor ensures correct polymorphism destruction */
    virtual ~EventUnit();

    int getCapacity() const override;

    /**
     * @brief Reacts to a notice pushed by a subject this unit is attached to.
     *
     * Left pure virtual so that every concrete leaf must state its own
     * reaction. Two units receiving the same notice therefore behave
     * differently through polymorphism, not through type inspection.
     * @param notice The notice being delivered.
     */
    void update(const EventNotice& notice) override = 0;

protected:
    int capacity;
};

#endif

#ifndef PREPZONE_H
#define PREPZONE_H

#include "EventGroup.h"

/**
 * @brief Composite with its own policy: the back-of-house preparation area.
 *
 * PrepZone reports how many exhibits it has ready when the event opens, and it
 * is the area that hands a prepared unit over to another one, transferring
 * ownership and the observer registration together.
 */
class PrepZone : public EventGroup {
public:
    /**
     * @brief Constructs a preparation area.
     * @param name Display name of the area.
     */
    explicit PrepZone(const std::string& name);

    ~PrepZone() override;

    /**
     * @brief Moves a prepared unit out of this area and into another one.
     *
     * The transfer is detach, remove, add, attach: this area gives up both the
     * ownership and the registration and the target takes both on, so the unit
     * is owned exactly once before and after and is never left as a dangling
     * registration.
     *
     * @param unit The unit to hand over; must currently be a child of this area.
     * @param target The area that will own and notify the unit.
     * @return true if the transfer took place.
     */
    bool releaseToDisplay(EventComponent* unit, EventGroup* target);

protected:
    /** @brief Reports how many exhibits are ready when the event opens. 
     *  @param notice notice being handled 
    */
    void applyLocalPolicy(const EventNotice& notice) override;

private:
    int vehiclesReady; ///< Count of prepared exhibits, rfresh @ open
};

#endif

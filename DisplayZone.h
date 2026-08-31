#ifndef DISPLAYZONE_H
#define DISPLAYZONE_H

#include "EventGroup.h"

/**
 * @brief Composite with its own policy: an area whose exhibits stand outdoors.
 *
 * DisplayZone is an EventGroup that reacts to a weather alert from its own
 * state rather than from the types of its children: an outdoor display area
 * decides that everything it is responsible for must be brought under cover,
 * and says so by broadcasting to its own observers.
 */
class DisplayZone : public EventGroup {
public:
    /**
     * @brief Constructs a display area.
     * @param name Display name of the area.
     * @param outdoor True if the exhibits stand in the open air.
     */
    DisplayZone(const std::string& name, bool outdoor);

    /** @brief Desroy this zone and all exhibit it owns  */
    ~DisplayZone() override;

    /**
     * @brief Tells every registered display to cover up.
     *
     * This is a broadcast, not a loop over children: each display decides for
     * itself what covering up means.
     */
    void shelterAll();

protected:
    /** @brief Outdoor areas shelter on a weather alert; indoor ones do not. 
      * @param notice the notice being handled
    */
    void applyLocalPolicy(const EventNotice& notice) override;

private:
    bool outdoor; ///< True if this area exhibit stand in open air
};

#endif

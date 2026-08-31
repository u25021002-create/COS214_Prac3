#ifndef VEHICLEDISPLAY_H
#define VEHICLEDISPLAY_H

#include "EventUnit.h"

class EventNotice;

/**
 * @brief Concrete Leaf: a static replica vehicle exhibit.
 *
 * Passive by default. Closing a VehicleDisplay represents covering the
 * vehicle(s) up (e.g. for weather protection) rather than an evacuation.
 */
class VehicleDisplay : public EventUnit {
public:
    /**
     * @brief constructs a static replica vehical exhibit
     * @param name display name of exhibit 
     * @param capacity man num of vistors can host at time 
     */
    VehicleDisplay(const std::string& name, int capacity);

    void open() override;
    void close() override;
    void reportStatus() const override;

    /**
     * @brief Reacts to a notice pushed by a subject this unit is attached to.
     * @param notice The notice being delivered.
     */
    void update(const EventNotice& notice) override;

private:
    bool covered; ///< True while the vehicls are covered
};

#endif

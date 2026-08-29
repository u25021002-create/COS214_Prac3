#ifndef VEHICLEDISPLAY_H
#define VEHICLEDISPLAY_H

#include "EventUnit.h"

/**
 * @brief Concrete Leaf: a static replica vehicle exhibit.
 *
 * Passive by default. Closing a VehicleDisplay represents covering the
 * vehicle(s) up (e.g. for weather protection) rather than an evacuation.
 */
class VehicleDisplay : public EventUnit {
public:
    VehicleDisplay(const std::string& name, int capacity);

    void open() override;
    void close() override;
    void reportStatus() const override;

private:
    bool covered;
};

#endif

#ifndef MEDICALTENT_H
#define MEDICALTENT_H

#include "EventUnit.h"

class EventNotice;

/**
 * @brief Concrete Leaf: on-site medical support.
 *
 * Deliberately stays operational through almost every notice, contrasting
 * with units like MainGate or FoodStall that shut down readily. Proves
 * that reaction to a notice is per-unit policy, not a blanket rule.
 */
class MedicalTent : public EventUnit {
public:
    /**
     * @brief constrcuct an on-site mediacl support tent
     * @param name display name on tent
     * @param capacity Max num it can assist/treat at a time
     */
    MedicalTent(const std::string& name, int capacity);

    void open() override;
    void close() override;
    void reportStatus() const override;

    /**
     * @brief Reacts to a notice pushed by a subject this unit is attached to.
     * @param notice The notice being delivered.
     */
    void update(const EventNotice& notice) override;

    /** @brief Steps the alert level up by one; the tent never closes. */
    void raiseAlertLevel();

private:
    int alertLevel; ///< Steps up on WEATHER_ALERT/EVACUATE; resets on RESUME
};

#endif

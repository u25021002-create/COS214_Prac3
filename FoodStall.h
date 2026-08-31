#ifndef FOODSTALL_H
#define FOODSTALL_H

#include "EventUnit.h"

class EventNotice;

/**
 * @brief Concrete Leaf: food and drinks vendor.
 *
 * Uses open flame/cooking equipment, so it behaves differently from
 * MerchStall on fire/weather-related safety notices even though both are
 * "vendor" style units.
 */
class FoodStall : public EventUnit {
public:
    /**
     * @brief constrcts food& drink vendor stall
     * @param name display name of stall
     * @param capacity Max serving 
     */
    FoodStall(const std::string& name, int capacity);

    void open() override;
    void close() override;
    void reportStatus() const override;

    /**
     * @brief Reacts to a notice pushed by a subject this unit is attached to.
     * @param notice The notice being delivered.
     */
    void update(const EventNotice& notice) override;

private:
    bool cookingActive; ///< True while cooking eqip is run
};

#endif

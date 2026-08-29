#ifndef MEDICALTENT_H
#define MEDICALTENT_H

#include "EventUnit.h"

/**
 * @brief Concrete Leaf: on-site medical support.
 *
 * Deliberately stays operational through almost every notice, contrasting
 * with units like MainGate or FoodStall that shut down readily. Proves
 * that reaction to a notice is per-unit policy, not a blanket rule.
 */
class MedicalTent : public EventUnit {
public:
    MedicalTent(const std::string& name, int capacity);

    void open() override;
    void close() override;
    void reportStatus() const override;
};

#endif

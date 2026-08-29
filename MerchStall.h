#ifndef MERCHSTALL_H
#define MERCHSTALL_H

#include "EventUnit.h"

/**
 * @brief Concrete Leaf: merchandise vendor stall.
 *
 * Sells collectibles/merch. Trading is largely unaffected by most notices
 * (unlike safety-critical units), representing a low-priority commercial unit.
 */
class MerchStall : public EventUnit {
public:
    MerchStall(const std::string& name, int capacity);

    void open() override;
    void close() override;
    void reportStatus() const override;

    /** @brief Sells items, decreasing stock (never below zero). */
    void sell(int units);

private:
    int stock;
};

#endif

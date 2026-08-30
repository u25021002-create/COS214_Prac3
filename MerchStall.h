#ifndef MERCHSTALL_H
#define MERCHSTALL_H

#include "EventUnit.h"
#include "Subject.h"

class EventNotice;

/**
 * @brief Concrete Leaf: merchandise vendor stall.
 *
 * Sells collectibles/merch. Trading is largely unaffected by most notices
 * (unlike safety-critical units), representing a low-priority commercial unit.
 *
 * Task 4.4 original feature: MerchStall is also a Subject. When sell()
 * drops stock below a restock threshold it raises its own LOW_STOCK notice
 * to whichever observers (typically a logistics/PrepZone) are attached to
 * it directly. This shows a Leaf acting as a ConcreteSubject in its own
 * right, not only as a ConcreteObserver receiving notices from above --
 * proof that the Subject/Observer collaboration is not tied to position in
 * the Composite tree.
 */
class MerchStall : public EventUnit, public Subject {
public:
    MerchStall(const std::string& name, int capacity);

    void open() override;
    void close() override;
    void reportStatus() const override;

    /** @brief Sells items, decreasing stock (never below zero). Raises
     *         LOW_STOCK if stock falls below the restock threshold. */
    void sell(int units);

    /**
     * @brief Reacts to a notice pushed by a subject this unit is attached to.
     * @param notice The notice being delivered.
     */
    void update(const EventNotice& notice) override;

private:
    int stock;
    static const int RESTOCK_THRESHOLD = 20;
    bool lowStockRaised; ///< Prevents repeated LOW_STOCK notices while low.
};

#endif

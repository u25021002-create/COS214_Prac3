#ifndef MAINGATE_H
#define MAINGATE_H

#include "EventUnit.h"

/**
 * @brief Concrete Leaf: main entry gate.
 *
 * Tracks a running admission count and enforces capacity by refusing
 * entry once admitted reaches capacity, independent of open()/close().
 */
class MainGate : public EventUnit {
public:
    MainGate(const std::string& name, int capacity);

    void open() override;
    void close() override;
    void reportStatus() const override;

    /** @brief Admits attendees if the gate is open and under capacity. */
    bool admit(int count);

private:
    int admitted;
};

#endif

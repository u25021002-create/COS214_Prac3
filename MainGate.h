#ifndef MAINGATE_H
#define MAINGATE_H

#include "EventUnit.h"

class EventNotice;

/**
 * @brief Concrete Leaf: main entry gate.
 *
 * Tracks a running admission count and enforces capacity by refusing
 * entry once admitted reaches capacity, independent of open()/close().
 */
class MainGate : public EventUnit {
public:
    /**
     * @brief constrct main entry gate
     * @param name display name of gate
     * @param capacity Max num of people this gate can allow  
     */
    MainGate(const std::string& name, int capacity);

    void open() override;
    void close() override;
    void reportStatus() const override;

    /** @brief Admits attendees if the gate is open and under capacity. 
     *  @param count num of people requesting entry
     *  @return true all admited, false if gate closed or admiting exceed capcity 
    */
    bool admit(int count);

    /** @brief Returns true once the admitted count has reached capacity. 
     *  @return true if no more people can be admitted
    */
    bool atCapacity() const;

    /**
     * @brief Reacts to a notice pushed by a subject this unit is attached to.
     * @param notice The notice being delivered.
     */
    void update(const EventNotice& notice) override;


private:
    int admitted; ///< Rn count of people admited so far
};

#endif

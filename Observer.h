#ifndef OBSERVER_H
#define OBSERVER_H

class EventNotice;

/**
 * @brief Abstract Observer in the Observer pattern.
 *
 * An Observer is told that something has changed and is handed the notice that
 * describes it, because EventFlow pushes rather than pulls. Each concrete
 * observer decides for itself how to react, so no subject ever needs to know
 * which concrete classes are listening to it.
 *
 * An Observer is never owned by the Subject it registers with; see Subject.
 */
class Observer {
public:
    /**
     * @brief Reacts to a notice pushed by a subject this observer is attached to.
     * @param notice The complete notice; the observer must not keep a pointer to it.
     */
    virtual void update(const EventNotice& notice) = 0;

    /** @brief Virtual destructor ensures correct polymorphic destruction. */
    virtual ~Observer();
};

#endif

#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>

class Observer;
class EventNotice;

/**
 * @brief Abstract Subject in the Observer pattern.
 *
 * A Subject keeps a registration list of Observers and broadcasts notices to
 * every observer currently on it.
 *
 * Registration policy:
 *  - attach() ignores a null pointer and ignores an observer that is already
 *    registered; both return false. The same observer can therefore never
 *    appear twice, so no subject ever delivers the same notice twice.
 *  - detach() returns false when the observer is not registered. That is not
 *    an error, so a caller may safely detach the same observer twice.
 *
 * Ownership policy:
 *  A Subject does NOT own its observers. The vector holds raw pointers to
 *  objects the subject did not create, and ~Subject() deletes none of them.
 *  Deleting here would destroy a unit twice, because every unit is already
 *  owned by the EventGroup that contains it.
 */
class Subject {
public:
    Subject();

    /** @brief Virtual destructor. Clears the registration list; deletes nothing. */
    virtual ~Subject();

    /**
     * @brief Registers an observer to receive this subject's notices.
     * @param observer The observer to add; must not be null.
     * @return true if it was added, false if it was null or already registered.
     */
    bool attach(Observer* observer);

    /**
     * @brief Stops sending this subject's notices to an observer.
     * @param observer The observer to remove.
     * @return true if it was registered and has been removed, false otherwise.
     */
    bool detach(Observer* observer);

    /**
     * @brief Pushes a notice to every currently registered observer.
     *
     * The list is copied before iterating, so an observer that attaches or
     * detaches inside its own update() cannot invalidate the traversal. Such a
     * change takes effect on the next notice.
     *
     * @param notice The notice to deliver.
     */
    void notify(const EventNotice& notice);

    /** @brief Returns how many observers are currently registered. 
     *  @return num of curr registered observers 
    */
    int getObserverCount() const;

protected:
    std::vector<Observer*> observers; ///< Non-owning registration list.
};

#endif

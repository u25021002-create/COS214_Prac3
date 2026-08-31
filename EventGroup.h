#ifndef EVENTGROUP_H
#define EVENTGROUP_H

#include "EventComponent.h"
#include "Subject.h"
#include "Observer.h"
#include <vector>

class EventNotice;

/**
 * @brief Concrete Composite in the Composite pattern.
 *
 * EventGroup represents a grouping/area of the event (e.g. a zone) that can
 * contain both EventUnit leaves and other EventGroup composites, forming a
 * genuine part-whole tree. EventGroup owns every child it holds: when an
 * EventGroup is destroyed, it deletes all of its owned children, and that
 * deletion recurses down the tree exactly once per object.
 *
 * Ownership (this Composite tree) is deliberately kept separate from
 * Observer registration (see Subject/Observer).
 *
 * Task 3: EventGroup is also a Subject and an Observer, for two different
 * collaborations. As an Observer it is registered with the control centre or
 * with a larger area above it; as a Subject it keeps its own registration list
 * of things below it. update() applies the area's own reaction and then
 * re-broadcasts, which is how a notice cascades down several runtime levels
 * without any object knowing the whole chain.
 */
class EventGroup : public EventComponent, public Subject, public Observer {
public:
    /**
     * @brief Constructs an empty group with the given name.
     * @param name Display name of this zone/group.
     */
    explicit EventGroup(const std::string& name);

    /**
     * @brief Destroys this group and every child it owns.
     *
     * Each child's destructor is invoked exactly once, via delete on the
     * base EventComponent* pointer. Because ~EventComponent() is virtual,
     * this correctly invokes the most-derived destructor for each child,
     * which in turn destroys that child's own owned subtree.
     */
    ~EventGroup() override;

    /**
     * @brief Adds a child component to this group. This group takes
     *        ownership of the pointer.
     * @param component Non-null pointer to the child to add.
     */
    void add(EventComponent* component);

    /**
     * @brief Removes a child component from this group without deleting it.
     *
     * Used when transferring a unit between groups (see Task 4.2): the
     * caller (or the destination group) becomes responsible for its
     * lifetime after removal. If the pointer is not found, this is a no-op.
     *
     * The child is also detached from this group's registration list, so a
     * component that leaves an area can never be left registered with it.
     * @param component Pointer to the child to remove.
     */
    void remove(EventComponent* component);

    void open() override;
    void close() override;
    void reportStatus() const override;
    int getCapacity() const override;

    /** @brief Returns the number of direct children (for tests/inspection). 
     *  @return num of direct children curr owned by this group
    */
    size_t childCount() const;

    /**
     * @brief Receives a notice from above, reacts to it, then passes it on.
     *
     * This is applyLocalPolicy() followed by notify(). The group re-broadcasts
     * to its observers list, not to its children list: a unit hears a notice
     * because it was attached, not because it is contained.
     * @param notice The notice pushed by the subject above.
     */
    void update(const EventNotice& notice) override;

protected:
    /**
     * @brief The area's own reaction to a notice, before it is passed on.
     *
     * The base version records whether the area is open and reports how many
     * observers the notice is about to be passed to. Overridden by DisplayZone
     * and PrepZone to give an area behaviour of its own.
     * @param notice The notice being handled.
     */
    virtual void applyLocalPolicy(const EventNotice& notice);

    std::vector<EventComponent*> children; ///< Owned children (structural ownership).
};

#endif

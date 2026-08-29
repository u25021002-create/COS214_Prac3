#ifndef EVENTGROUP_H
#define EVENTGROUP_H

#include "EventComponent.h"
#include <vector>

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
 * Observer registration (see Subject/Observer), which is added in Task 3.
 */
class EventGroup : public EventComponent {
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
     * @param component Pointer to the child to remove.
     */
    void remove(EventComponent* component);

    void open() override;
    void close() override;
    void reportStatus() const override;
    int getCapacity() const override;

    /** @brief Returns the number of direct children (for tests/inspection). */
    size_t childCount() const;

protected:
    std::vector<EventComponent*> children; ///< Owned children (structural ownership).
};

#endif

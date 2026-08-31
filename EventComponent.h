#ifndef EVENTCOMPONENT_H
#define EVENTCOMPONENT_H

#include <string>

/**
 * @brief Abstract Component in the Composite pattern.
 *
 * EventComponent is the common interface shared by individual event units
 * (Leaves) and groupings of units (Composites). Client code can invoke
 * these operations without knowing whether it holds a single unit or an
 * entire subtree of the event.
 */
class EventComponent {
public:
    /**
     * @brief Constructs a component with a display name.
     * @param name Human-readable name of this component.
     */
    explicit EventComponent(const std::string& name);

    /** @brief Virtual destructor ensures correct polymorphic destruction. */
    virtual ~EventComponent();

    /** @brief Opens this component (and, for composites, its children). */
    virtual void open() = 0;

    /** @brief Closes this component (and, for composites, its children). */
    virtual void close() = 0;

    /** @brief Prints/returns a status report for this component. */
    virtual void reportStatus() const = 0;

    /**
     * @brief Returns the capacity of this component.
     * @return For a Leaf, its own capacity. For a Composite, the sum of
     *         its children's capacities.
     */
    virtual int getCapacity() const = 0;

    /** @brief Returns the display name of this component.
     *  @return the comps display name
     */
    const std::string& getName() const;

protected:
    std::string name;
    bool open_;
};

#endif

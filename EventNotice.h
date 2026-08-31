#ifndef EVENTNOTICE_H
#define EVENTNOTICE_H

#include <string>

/**
 * @brief The kinds of notice that can be broadcast across the event.
 *
 * Nine types are provided, covering the three categories required by the
 * specification: ordinary operational changes (OPEN, CLOSE, SCHEDULE_CHANGE,
 * PAUSE, RESUME, REASSIGN), a capacity-related change (CAPACITY_ALERT) and
 * safety-related changes (WEATHER_ALERT, EVACUATE).
 */
enum NoticeType {
    OPEN,             ///< An area or unit is being opened.
    CLOSE,            ///< An area or unit is being closed.
    SCHEDULE_CHANGE,  ///< A programme time has moved.
    CAPACITY_ALERT,   ///< Admission has reached the allowed limit.
    WEATHER_ALERT,    ///< Weather is threatening outdoor activity.
    PAUSE,            ///< Activity must stop temporarily.
    RESUME,           ///< Normal activity may restart.
    EVACUATE,         ///< The area must be cleared.
    REASSIGN          ///< A unit has been moved to another area.
};

/**
 * @brief Human-readable name of a NoticeType, used in status output.
 * @param type The notice type to name.
 * @return The enumerator name as a C string.
 */
const char* noticeTypeName(NoticeType type);

/**
 * @brief The information a Subject pushes to its Observers.
 *
 * EventFlow uses a push Observer, so the complete notice travels with the
 * update(...) call. EventNotice is an immutable value object: it is created by
 * the subject, passed by const reference, and copied by value if a receiver
 * needs to keep it. No observer ever holds a pointer into a notice.
 */
class EventNotice {
public:
    /**
     * @brief Constructs a notice.
     * @param type The kind of change being reported.
     * @param message Human-readable detail carried with the notice.
     * @param source Name of the subject that raised the notice.
     * @param severity 0 for routine, higher for more urgent notices.
     */
    EventNotice(NoticeType type, const std::string& message,
                const std::string& source, int severity = 0);

    /** @brief Returns the kind of change this notice reports. 
     *  @return notices NoticeType
    */
    NoticeType getType() const;

    /** @brief Returns the human-readable detail carried with the notice. 
     *  @return notices message text
    */
    const std::string& getMessage() const;

    /** @brief Returns the name of the subject that raised the notice. 
     *  @return og subjects name
    */
    const std::string& getSource() const;

    /** @brief Returns how urgent the notice is; 0 is routine. 
     *  @return severtity lvl
    */
    int getSeverity() const;

private:
    NoticeType type; ///< Kind of change being reproted 
    std::string message; ///< Human-read deatil carried with notice
    std::string source; ///< Name of the subject that raised the notice
    int severity; ///< 0 for routine, high for more urgent notics
};

#endif

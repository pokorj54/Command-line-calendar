#ifndef EventContainer_2bbf503dbcf742179fe0e7d8f50c23cb
#define EventContainer_2bbf503dbcf742179fe0e7d8f50c23cb

#include "Event.hpp"
#include "VirtualEvent.hpp"

#include <memory>
#include <vector>

class Event;
class VirtualEvent;

/**
 * @brief Represents container for Event objects
 * 
 */
class EventContainer
{
    private:
        std::vector<std::shared_ptr<Event>> events;
    public:
        EventContainer() = default;

        /**
         * @brief Add Event object to this container
         * 
         * @param event shared pointer of Event object
         * @return true if Event was succesfully added 
         * @return false if Event already exists in this EventContainer
         */
        bool Add(const std::shared_ptr<Event> & event);
        /**
         * @brief Removes event from EventContainer
         * 
         * @param event shared pointer of Event that is in the EventContainer
         */
        void Remove(const std::shared_ptr<Event> & event);

        /**
         * @brief Exports Event objects of this EventConatiner to file
         * 
         * @param fileName it will be exported to file named like this
         * @return true if all Event objects were succesfully exported
         * @return false if export failed to complete
         */
        bool Export(const std::string & fileName) const;
        
        /**
         * @brief Gets all events that have an instance between given DateTimes from and to
         * 
         * @param[out] putHere Here will be inserted VirtualEvents that represents instance of Event
         * @param from 
         * @param to 
         */
        void FillWithVirtualEvents(std::vector<VirtualEvent> & putHere, const DateTime & from,
            const DateTime & to) const;
            /**
             * @brief Gets all events that contains given string
             * 
             * @param[out] putHere Here will be inserted VirtualEvents that represents instance of Event
             * @param search string that is searched for
             */
        void FillWithVirtualEvents(std::vector<VirtualEvent> & putHere,
            const std::string & search = "") const;

        /**
         * @brief Finds closest available time for new Event onbject with given duration
         * 
         * @param dt First possible date for new Event object
         * @param ts Duration of the new Event object
         * @return DateTime DateTime that represents first available time
         */
        DateTime FindClosestAvailableTime(const DateTime & dt, const TimeSpan & ts) const;
};

#endif //EventContainer_2bbf503dbcf742179fe0e7d8f50c23cb
#ifndef Person_9345f7b9835a45ffb8336cc073e7af1d
#define Person_9345f7b9835a45ffb8336cc073e7af1d

#include "../Event/Event.hpp"
#include "../Event/EventContainer.hpp"

#include <iostream>
#include <vector>
#include <memory>

class Event;
class EventContainer;

/**
 * @brief Represent user of this program
 * 
 */
class Person
{
    private:
        /**
         * @brief Unique identificator of Person 
         *  (there cannot be more than one Person object with given name)
         */
        std::string name;
        std::shared_ptr<EventContainer> events;
    public:
        Person(const std::string & name);

        /**
         * @brief Compares Person objects by name
         * 
         * @param p another Person object to compare this with
         */
        bool operator < (const Person & p) const;
        bool operator > (const Person & p) const;
        /**
         * @brief Compares Person objects by name
         * 
         * @param p another Person object to compare this with
         */
        bool operator == (const Person & p) const;
        bool operator != (const Person & p) const;

        const std::string & GetName() const;
        std::shared_ptr<EventContainer> GetEvents() const;

        /**
         * @brief Adds event to Persons Eventcontainer
         * 
         * @param event event that will be added
         * @return true if events was added to the EventContainer
         * @return false if same event already existed in the EventContainer
         */
        bool AddEvent(const std::shared_ptr<Event> & event);
        /**
         * @brief Removes event from Persons EventContainer
         * 
         * @param event shared pointer of Event that is in the EventContainer
         */
        void RemoveEvent(const std::shared_ptr<Event> & event);
        /**
         * @brief Exports Event objects to a file
         * 
         * @param fileName to file with this name will it be exported
         * @return true if Event objects were successfully exported
         * @return false if export failed to complete
         */
        bool ExportEvents(const std::string & fileName);

        void Print(std::ostream & os) const;
        DateTime FindClosestAvailableTime(const DateTime & dt, const TimeSpan & ts) const;
};

#endif //Person_9345f7b9835a45ffb8336cc073e7af1d
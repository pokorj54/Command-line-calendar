#ifndef Calendar_148f31b6d3ed48fcba0942c7d6652e6e
#define Calendar_148f31b6d3ed48fcba0942c7d6652e6e

#include "../Event/Event.hpp"
#include "../Event/OneTimeEvent.hpp"
#include "../Event/EventContainer.hpp"
#include "../Helpers/DateTime.hpp"

#include <iostream>
#include <memory>
#include <set>
#include <algorithm>

/**
 * @brief Abstract class providing general interface to calendars
 * 
 */
class Calendar
{
    protected:
        std::shared_ptr<EventContainer> allEvents;
        std::vector<VirtualEvent> instances;
        DateTime start;

        /**
         * @brief Common part for FillWithVirtualEvents method
         * 
         * @param periode number of specified time intervals that symbolises lenght of calendar
         * @param t time adding method that symbolizes in which time units is Calendar lenght defined
         */
        void _FillWithVirtualEvents(int periode, DateTime::TimeAddMethod t);
    public:
        /**
         * @brief Construct a new Calendar object 
         * 
         * @param ec From this container it will gather Event objects
         * @param dt Represents start date for the Calendar
         */
        Calendar(const std::shared_ptr<EventContainer> & ec, const DateTime & dt);
        virtual ~Calendar() = default;

        /**
         * @brief Fills instances with VirtualEvent objects for given calendar type
         * 
         */
        virtual void FillWithVirtualEvents() = 0;

        /**
         * @brief Prints all VirtualEvents objects in instances
         * 
         * @param[out] os here it will be printed
         */
        virtual void Print(std::ostream & os) const = 0;
        /**
         * @brief Prints prefix accorfing to calendar type
         * 
         * @param[out] os here it will be printed
         */
        virtual void PrintPrefix(std::ostream & os) const = 0;
        /**
         * @brief Changes calendar view to next time interval
         * 
         */
        virtual void Next() = 0;
        /**
         * @brief Changes calendar view to previous time interval
         * 
         */
        virtual void Prev() = 0;

        /**
         * @brief Get the Event object on given position from previously printed calendar view
         * 
         * @param pos specifies which Event object will be selected
         * @param[out] serialNum here will be stored serial number of the specific instance of 
         *  Event object
         * @return std::shared_ptr<Event> 
         */
        std::shared_ptr<Event> GetEvent(int pos, int * serialNum);
};

#endif //Calendar_148f31b6d3ed48fcba0942c7d6652e6e
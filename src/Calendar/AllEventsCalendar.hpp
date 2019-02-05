#ifndef AllEventsCalendar_5ae1b9c48d7c4b2d95a7c1faeaba5292
#define AllEventsCalendar_5ae1b9c48d7c4b2d95a7c1faeaba5292

#include "Calendar.hpp"
#include "../Event/Event.hpp"
#include "../Event/EventContainer.hpp"

#include <iostream>

/**
 * @brief Represents Calendar that can show all or searched events 
 * 
 */
class AllEventsCalendar : public Calendar
{
    private:
        std::string searchStr;
    public:
        /**
         * @brief Construct a new All Events Calendar object
         * 
         * @param ec From this container it will gather Event objects
         * @param searchStr if it is empty string it will be calendar that shows all events, 
         *  otherwise it will show events that contains this string
         */
        AllEventsCalendar(const std::shared_ptr<EventContainer> & ec, 
            const std::string & searchStr = "");
        
        /**
         * @brief Fills instances with all or searched for VirtualEvent objects
         * 
         */
        void FillWithVirtualEvents() override;

        /**
         * @brief Prints all VirtualEvents objects in instances
         * 
         * @param[out] os here it will be printed
         */
        void Print(std::ostream & os) const override;
        /**
         * @brief Prints if it is showing all events or only searched for Event objects
         * 
         * @param[out] os here it will be printed
         */
        void PrintPrefix(std::ostream & os) const override;
        /**
         * @brief Does not have an interpretation 
         * 
         * @throws InvalidUseException
         */
        void Next() override;
        /**
         * @brief Does not have an interpretation 
         * 
         * @throws InvalidUseException
         */
        void Prev() override;
};

#endif //AllEventsCalendar_5ae1b9c48d7c4b2d95a7c1faeaba5292
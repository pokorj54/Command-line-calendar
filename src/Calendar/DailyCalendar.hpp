#ifndef DailyCalendar_fbf4a433ac904a02ae77b4d0abe64f0e
#define DailyCalendar_fbf4a433ac904a02ae77b4d0abe64f0e

#include "Calendar.hpp"
#include "../Event/Event.hpp"
#include "../Event/EventContainer.hpp"
#include "../Helpers/DateTime.hpp"

#include <iostream>

/**
 * @brief Represents Calendar that can show events in selected day
 * 
 */
class DailyCalendar : public Calendar
{
    public:
        DailyCalendar(const std::shared_ptr<EventContainer> & ec, DateTime dt);
        
        /**
         * @brief Fills instances with all Event objects that are happening selected day
         * 
         */
        void FillWithVirtualEvents() override;

        /**
         * @brief Prints all VirtualEvents objects in instances, spilts them by which starts 
         *  on the selected day
         * 
         * @param[out] os here it will be printed
         */
        void Print(std::ostream & os) const override;
        /**
         * @brief Prints that it is DailyCalendar and selected date
         * 
         * @param[out] os here it will be printed
         */
        void PrintPrefix(std::ostream & os) const override;
        /**
         * @brief Changes Calendar view to next day
         * 
         */
        void Next() override;
        /**
         * @brief Changes Calendar view to previous day
         * 
         */
        void Prev() override;
};

#endif //DailyCalendar_fbf4a433ac904a02ae77b4d0abe64f0e
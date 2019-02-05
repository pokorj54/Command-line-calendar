#ifndef WeeklyCalendar_f95ed375a699490b9e84a9a3d5a81a53
#define WeeklyCalendar_f95ed375a699490b9e84a9a3d5a81a53

#include "Calendar.hpp"
#include "../Event/Event.hpp"
#include "../Event/EventContainer.hpp"

#include <iostream>
/**
 * @brief Represents Calendar that can show events in selected week
 * 
 */
class WeeklyCalendar : public Calendar
{
    public:
        /**
         * @brief Construct a new WeeklyCalendar object, changes start to the last weekStart Day
         *  that is not before param dt
         * 
         * @param ec From this container it will gather Event objects
         * @param dt Selects week
         * @param weekStart 
         */
        WeeklyCalendar(const std::shared_ptr<EventContainer> & ec, DateTime dt,
            int weekStart = DEFAULT_WEEK_START);
        
        /**
         * @brief Fills instances with all Event objects that are happening selected week
         * 
         */
        void FillWithVirtualEvents() override;

        /**
         * @brief Prints all VirtualEvents objects in instances, spilts them by start day
         * 
         * @param[out] os here it will be printed
         */
        void Print(std::ostream & os) const override;
        /**
         * @brief Prints that it is WeeklyCalendar and first day of the week
         * 
         * @param[out] os here it will be printed
         */
        void PrintPrefix(std::ostream & os) const override;
        /**
         * @brief Changes Calendar view to next week
         * 
         */
        void Next() override;
        /**
         * @brief Changes Calendar view to previous week
         * 
         */
        void Prev() override;
};

#endif //WeeklyCalendar_f95ed375a699490b9e84a9a3d5a81a53
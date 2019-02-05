#ifndef MonthlyCalendar_3837d1b6871845d09187dff8161117e6
#define MonthlyCalendar_3837d1b6871845d09187dff8161117e6

#include "Calendar.hpp"
#include "../Event/Event.hpp"
#include "../Event/EventContainer.hpp"

#include <iostream>

/**
 * @brief Represents Calendar that can show events in selected month
 * 
 */
class MonthlyCalendar : public Calendar
{
    private:
        /**
         * @brief Prints Block view of a calnendar for selected month with marking of given days
         * 
         * @param[out] os Here it will be printed
         * @param days Days which will be marked with color
         */
        void PrintBlockCalendar(std::ostream & os, const std::vector<int> & days) const;
    public:
        /**
         * @brief Construct a new MonthlyCalendar object, selects first day of month as start
         * 
         * @param ec From this container it will gather Event objects
         * @param dt Selects month
         */
        MonthlyCalendar(const std::shared_ptr<EventContainer> & ec, DateTime dt);
        
        /**
         * @brief Fills instances with all Event objects that are happening selected month
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
         * @brief Prints that it is MonthlyCalendar and first day of selected month
         * 
         * @param[out] os here it will be printed
         */
        void PrintPrefix(std::ostream & os) const override;
        /**
         * @brief Changes Calendar view to next month
         * 
         */
        void Next() override;
        /**
         * @brief Changes Calendar view to previous month
         * 
         */
        void Prev() override;
};

#endif //MonthlyCalendar_3837d1b6871845d09187dff8161117e6
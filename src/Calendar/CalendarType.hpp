#ifndef CalendarType_287be02a60454cfaa92037f40742446a
#define CalendarType_287be02a60454cfaa92037f40742446a

#include <ostream>
#include <vector>

/**
 * @brief Enum that corresponds to Calendar types
 * 
 */
enum CalendarType
{
    CT_DailyCalendar,
    CT_WeeklyCalendar,
    CT_MonthlyCalendar,
    CT_AllEventsCalendar 
};

std::vector<CalendarType> GetCalendarTypes();
std::ostream & operator << (std::ostream & out, const CalendarType & calendarType);

#endif //CalendarType_287be02a60454cfaa92037f40742446a
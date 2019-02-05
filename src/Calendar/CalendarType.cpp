#include "CalendarType.hpp"

std::vector<CalendarType> GetCalendarTypes()
{
    return std::vector<CalendarType>{
        CT_DailyCalendar,
        CT_WeeklyCalendar,
        CT_MonthlyCalendar,
        CT_AllEventsCalendar
    };
}
std::ostream & operator << (std::ostream & out, const CalendarType & calendarType)
{
    switch(calendarType)
    {
        case CT_DailyCalendar:
            out << "Daily calendar";
            break;
        case CT_WeeklyCalendar:
            out << "Weekly calendar";
            break;
        case CT_MonthlyCalendar:
            out << "Monthly calendar";
            break;
        case CT_AllEventsCalendar:
            out << "Calendar for all events";
            break;
        default:
            out << "Unknown calendar";
    }
    return out;
}
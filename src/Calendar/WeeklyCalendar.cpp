#include "WeeklyCalendar.hpp"

using namespace std;

WeeklyCalendar::WeeklyCalendar(const shared_ptr<EventContainer> & ec, DateTime dt, int weekStart): 
Calendar(ec, dt.Week(weekStart))
{}

void WeeklyCalendar::FillWithVirtualEvents()
{
     _FillWithVirtualEvents(7, &DateTime::AddDays);
}

void WeeklyCalendar::Print(ostream & os) const
{
    DateTime tmp = start;
    tmp.AddDays(6);
    os << "Weekly calendar from ";
    start.Print(os, DEFAULT_DATE_FORMAT);
    os << " to ";
    tmp.Print(os, DEFAULT_DATE_FORMAT);
    os << endl;

    int rowNum = 0;
    tmp = start;
    bool dateStart = false;
    if(instances.empty())
    {
        os << "No events this week" << endl;
        return;
    }
    else if(tmp > instances.begin()->GetStart())
    {
        os << "Events that continues this week" << endl;
        dateStart = true;
    }
    for(const VirtualEvent & v : instances)
    {
        DateTime day = v.GetStart();
        if(day > tmp)
        {
            tmp = day.Date();
            dateStart = false;
            os << DateTime::GetWeekday(tmp.GetWeekday()) << " ";
            tmp.Print(os, DEFAULT_DATE_FORMAT);
            os << endl;
            tmp.AddDays(1);
        }
        os << "\t" << rowNum << ") ";
        v.Print(os, dateStart);
        os << endl;
        ++rowNum;
    }
}
void WeeklyCalendar::PrintPrefix(ostream & os) const
{
    os << "Week from ";
    start.Print(os, DEFAULT_DATE_FORMAT);
}
void WeeklyCalendar::Next()
{
    start.AddDays(7);
}
void WeeklyCalendar::Prev()
{
    start.AddDays(-7);
}
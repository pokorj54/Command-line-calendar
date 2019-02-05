#include "DailyCalendar.hpp"

using namespace std;

DailyCalendar::DailyCalendar(const shared_ptr<EventContainer> & ec, DateTime dt): 
Calendar(ec, dt.Date())
{}

void DailyCalendar::FillWithVirtualEvents()
{
    _FillWithVirtualEvents(1, &DateTime::AddDays);
}

void DailyCalendar::Print(ostream & os) const
{
    os << "Daily calendar for ";
    start.Print(os, DEFAULT_DATE_FORMAT);
    os << endl;

    int rowNum = 0;
    DateTime tmp = start;
    bool dateStart = false;
    if(instances.empty())
    {
        os << "No events this day" << endl;
        return;
    }
    else if(tmp > instances.begin()->GetStart())
    {
        os << "Events that continues this day" << endl;
        dateStart = true;
    }
    else
    {
        tmp.AddDays(1);
    }
    for(const VirtualEvent & v : instances)
    {
        DateTime day = v.GetStart();
        if(day > tmp)
        {
            tmp = day.AddDays(1);
            dateStart = false;
            os << "Events that start today" << endl;
        }
        os << "\t" << rowNum << ") ";
        v.Print(os, dateStart);
        os << endl;
        ++rowNum;
    }
}
void DailyCalendar::PrintPrefix(ostream & os) const
{
    os << "Day ";
    start.Print(os, DEFAULT_DATE_FORMAT);
}
void DailyCalendar::Next()
{
    start.AddDays(1);
}
void DailyCalendar::Prev()
{
    start.AddDays(-1);
}
#include "MonthlyCalendar.hpp"

using namespace std;

MonthlyCalendar::MonthlyCalendar(const shared_ptr<EventContainer> & ec, DateTime dt): 
Calendar(ec, dt.Month())
{}

void MonthlyCalendar::FillWithVirtualEvents()
{
     _FillWithVirtualEvents(1, &DateTime::AddMonths);
}
void MonthlyCalendar::PrintBlockCalendar(ostream & os, const vector<int> & days) const
{
    DateTime tmp = start;
    DateTime nextMonth = tmp;
    nextMonth.AddMonths(1);

    for(int i = 0; i < 7 ; ++i)
    {
        os << "\t" <<DateTime::GetWeekday(i + DEFAULT_WEEK_START).substr(0, 3);
    }
    os << endl;
    int weekday = DEFAULT_WEEK_START;
    while(weekday != tmp.GetWeekday())
    {
        os << "\t";
        ++weekday;
        weekday %= 7; 
    }
    vector<int>::const_iterator it = days.begin();
    while(tmp < nextMonth)
    {
        if(tmp.GetWeekday() == DEFAULT_WEEK_START)
        {
            os << endl;
        }
        if(it != days.end() && *it == tmp.GetDay())
        {
            cout << BLUE_COLOR;
            ++it;
        }
        os  << "\t" << tmp.GetDay();
        tmp.AddDays(1);
        ++weekday;
        weekday %= 7; 
        os << WHITE_COLOR;
    }
     os << endl;
}

void MonthlyCalendar::Print(ostream & os) const
{
    DateTime tmp = start;
    tmp.AddMonths(1).AddDays(-1);
    os << "Monthly calendar from ";
    start.Print(os, DEFAULT_DATE_FORMAT);
    os << " to ";
    tmp.Print(os, DEFAULT_DATE_FORMAT);
    os << endl;

    vector<VirtualEvent>::const_iterator it = instances.begin();
    tmp = start;
    DateTime delayed = tmp;
    delayed.AddDays(-1);
    vector<int> days = {};
    DateTime nextMonth = tmp;
    nextMonth.AddMonths(1);
    DateTime maximum(0);
    while(tmp <= nextMonth)
    {
        while(it != instances.end() && it->GetStart() < tmp)
        {
            if(it->GetEnd() > maximum)
            {
                maximum = it->GetEnd();
            }
            ++it;
        }
        if(maximum > delayed && delayed >= start)
        {
            days.push_back(delayed.GetDay());
        }
        delayed.AddDays(1);
        tmp.AddDays(1);
    }
    PrintBlockCalendar(os, days);

    int rowNum = 0;
    tmp = start;
    bool dateStart = false;
    if(instances.empty())
    {
        os << "No events this month" << endl;
        return;
    }
    else if(tmp > instances.begin()->GetStart())
    {
        os << "Events that continues this month" << endl;
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
void MonthlyCalendar::PrintPrefix(ostream & os) const
{
    os << "Month from ";
    start.Print(os, DEFAULT_DATE_FORMAT);
}
void MonthlyCalendar::Next()
{
    start.AddMonths(1);
}
void MonthlyCalendar::Prev()
{
    start.AddMonths(-1);
}
#include "AllEventsCalendar.hpp"
#include "../Exceptions/InvalidUseException.hpp"

using namespace std;

AllEventsCalendar::AllEventsCalendar(const shared_ptr<EventContainer> & ec,
    const string & searchStr):
    Calendar(ec, DateTime()), searchStr(searchStr)
{}

void AllEventsCalendar::FillWithVirtualEvents()
{
    string lowSearchStr = searchStr;
    transform(lowSearchStr.begin(), lowSearchStr.end(), lowSearchStr.begin(), ::tolower);
    instances.clear();
    allEvents->FillWithVirtualEvents(instances, lowSearchStr);
    sort(instances.begin(), instances.end());
}
void AllEventsCalendar::Print(ostream & os) const
{
    if(instances.empty())
    {
        os << "No events yet" << endl;
        return;
    }
    int rowNum = 0;
    for(const VirtualEvent & v : instances)
    {
        os << "\t" << rowNum << ") ";
        v.PrintSource(os);
        os << endl;
        ++rowNum;
    }
}
void AllEventsCalendar::PrintPrefix(ostream & os) const
{
    if(searchStr == "")
    {
        os << "All Events";
    }
    else
    {
        os << "Searched for " << searchStr;
    }
}
void AllEventsCalendar::Next()
{
    throw InvalidUseException();
}
void AllEventsCalendar::Prev()
{
    throw InvalidUseException();
}
#include "Calendar.hpp"

Calendar::Calendar(const std::shared_ptr<EventContainer> & ec, const DateTime & dt): allEvents(ec),
    start(dt)
{}

void Calendar::_FillWithVirtualEvents(int periode, DateTime::TimeAddMethod t)
{
    instances.clear();
    DateTime to = start;
    (to.*t)(periode);
    allEvents->FillWithVirtualEvents(instances, start, to);
    sort(instances.begin(), instances.end());
}

std::shared_ptr<Event> Calendar::GetEvent(int pos, int * serialNum) 
{
    VirtualEvent v = instances.at(pos);
    *serialNum = v.GetSerialNumber();
    return v.GetSource();
}
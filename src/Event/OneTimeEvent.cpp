#include "OneTimeEvent.hpp"

using namespace std;

OneTimeEvent::OneTimeEvent(const string & name, const string & place, const DateTime & start,
    const TimeSpan & duration, const shared_ptr<Person> & owner):
    Event(name, place, start, duration, owner)
{}

void OneTimeEvent::Print(ostream & os) const
{
    os << place << ": " << name << ": ";
    start.Print(os, DEFAULT_DATETIME_FORMAT);
    os << " - ";
    DateTime end = start + duration;
    end.Print(os, end.isSameDate(start) ? DEFAULT_TIME_FORMAT : DEFAULT_DATETIME_FORMAT);
}

void OneTimeEvent::FillWithVirtualEvents(vector<VirtualEvent> & putHere, const DateTime & from,
    const DateTime & to, shared_ptr<Event> & ptr) const
{
    DateTime end = start + duration;
    if((start < to && start >= from) || (start < from && end > to) || (end < to && end > from))
    {
        putHere.push_back(VirtualEvent(start, end, ptr, NOT_SERIABLE));
    }
}

shared_ptr<Event> OneTimeEvent::SplitShift(const TimeSpan & ts, int from,
    const std::shared_ptr<Person> & owner)
{
    throw InvalidUseException();
}

void OneTimeEvent::ExportEventTypeSpecificInfo(ofstream & file) const
{
    file << CHAR_NO << endl;
}
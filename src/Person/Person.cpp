#include "Person.hpp"
#include "../constants.hpp"
#include "../Exceptions/InvalidDateTimeFormatException.hpp"
#include "../Exceptions/InvalidTimeSpanFormatException.hpp"
#include "../Helpers/TimeSpan.hpp"

using namespace std;

Person::Person(const string & name): name(name), events(new EventContainer)
{}

bool Person::operator < (const Person & p) const
{
    return name < p.name;
}
bool Person::operator > (const Person & p) const
{
    return p < *this;
}
bool Person::operator == (const Person & p) const
{
    return name == p.name;
}
bool Person::operator != (const Person & p) const
{
    return !(*this == p);
}

std::shared_ptr<EventContainer> Person::GetEvents() const
{
    return events;
}
const string & Person::GetName() const
{
    return name;
}
bool Person::AddEvent(const shared_ptr<Event> & event)
{
    return events->Add(event);
}
void Person::RemoveEvent(const shared_ptr<Event> & event)
{
    events->Remove(event);
}
bool Person::ExportEvents(const std::string & fileName)
{
    return events->Export(fileName);
}

void Person::Print(std::ostream & os) const
{
    os << name;
}

DateTime Person::FindClosestAvailableTime(const DateTime & dt, const TimeSpan & ts) const
{
    return events->FindClosestAvailableTime(dt, ts);
}
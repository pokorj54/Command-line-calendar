#include "NDaysRepeatingEvent.hpp"
#include "OneTimeEvent.hpp"
using namespace std;

NDaysRepeatingEvent::NDaysRepeatingEvent(const string & name, const string & place,
    const DateTime & start, const TimeSpan & duration, const shared_ptr<Person> & owner,
    int periode, size_t repeats):
    RepeatingEvent(name, place, start, duration, owner, repeats), periode(periode)
{}
std::shared_ptr<Event> NDaysRepeatingEvent::MakeSimilar(const std::string & name,
    const std::string & place, const DateTime & start, const TimeSpan & duration,
    const std::shared_ptr<Person> & owner, std::size_t repeats) const
{
    return make_shared<NDaysRepeatingEvent>(name, place, start, duration, owner, periode, repeats);
}

void NDaysRepeatingEvent::Print(ostream & os) const
{
    os << place << ": " << name << ": ";
    start.Print(os, DEFAULT_DATETIME_FORMAT);
    os << ", duration: ";
    duration.Print(os, DEFAULT_TIMESPAN_FORMAT);
    os << ", repeats every " << periode <<" days";
    if(repeats > 0)
    {
        os << ", " << repeats << " times in total";
    }
}

void NDaysRepeatingEvent::FillWithVirtualEvents(vector<VirtualEvent> & putHere, const DateTime & from,
    const DateTime & to, shared_ptr<Event> & ptr) const
{
   _FillWithVirtualEvents(putHere, from, to, ptr, periode, &DateTime::AddDays);
}

shared_ptr<Event> NDaysRepeatingEvent::SplitShift(const TimeSpan & ts, int from,
    const std::shared_ptr<Person> & owner)
{
    return _SplitShift(ts, from, owner, periode, &DateTime::AddDays);
}

void NDaysRepeatingEvent::ExportEventTypeSpecificInfo(ofstream & file) const
{
    file << CHAR_YES << endl << (int)ET_NDaysRepeatingEvent<< endl << repeats << endl
        << periode << endl;
}
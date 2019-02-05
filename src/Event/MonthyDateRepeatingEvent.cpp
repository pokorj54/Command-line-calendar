#include "MonthyDateRepeatingEvent.hpp"
#include "OneTimeEvent.hpp"

using namespace std;

MonthyDateRepeatingEvent::MonthyDateRepeatingEvent(const string & name, const string & place,
    const DateTime & start, const TimeSpan & duration, const shared_ptr<Person> & owner,
    size_t repeats): RepeatingEvent(name, place, start, duration, owner, repeats)
{
    if(start.GetDay() >= 29)
    {
        int cycles = repeats == 0 ? 23 : repeats; //testing 23 months is enough
        DateTime startCopy = start;
        for (int i = 0; i < cycles; ++i)
        {
            startCopy.AddMonths(1); //it will throw exception if there is no representation for the date
        }
    }
}
std::shared_ptr<Event> MonthyDateRepeatingEvent::MakeSimilar(const std::string & name,
    const std::string & place, const DateTime & start, const TimeSpan & duration,
    const std::shared_ptr<Person> & owner, std::size_t repeats) const
{
    return make_shared<MonthyDateRepeatingEvent>(name, place, start, duration, owner, repeats);
}

void MonthyDateRepeatingEvent::Print(ostream & os) const
{
    os << place << ": " << name << ": ";
    start.Print(os, DEFAULT_DATETIME_FORMAT);
    os << ", duration: ";
    duration.Print(os, DEFAULT_TIMESPAN_FORMAT);
    os << ", repeats every month";
    if(repeats > 0)
    {
        os << ", " << repeats << " times in total";
    }
}

void MonthyDateRepeatingEvent::FillWithVirtualEvents(std::vector<VirtualEvent> & putHere, const DateTime & from,
    const DateTime & to, std::shared_ptr<Event> & ptr) const
{
   _FillWithVirtualEvents(putHere, from, to, ptr, 1, &DateTime::AddMonths);
}

shared_ptr<Event> MonthyDateRepeatingEvent::SplitShift(const TimeSpan & ts, int from,
    const std::shared_ptr<Person> & owner)
{
    return _SplitShift(ts, from, owner, 1, &DateTime::AddMonths);
}

void MonthyDateRepeatingEvent::ExportEventTypeSpecificInfo(ofstream & file) const
{
    file << CHAR_YES << endl << (int)ET_MonthyDateRepeatingEvent << endl << repeats << endl;
}
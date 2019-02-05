#include "YearlyRepeatingEvent.hpp"
#include "OneTimeEvent.hpp"

using namespace std;

YearlyRepeatingEvent::YearlyRepeatingEvent(const string & name, const string & place, 
    const DateTime & start, const TimeSpan & duration, const shared_ptr<Person> & owner,
     size_t repeats): RepeatingEvent(name, place, start, duration, owner, repeats)
{
    if(start.GetDay() == 29 && start.GetMonth() == 2)
    {
        throw InvalidDateTimeShiftException(start.GetYear(), 2, 29, 12); //there are never two 29.2. in two years
    }
}
std::shared_ptr<Event> YearlyRepeatingEvent::MakeSimilar(const std::string & name,
    const std::string & place, const DateTime & start, const TimeSpan & duration,
    const std::shared_ptr<Person> & owner, std::size_t repeats) const
{
    return make_shared<YearlyRepeatingEvent>(name, place, start, duration, owner, repeats);
}

void YearlyRepeatingEvent::Print(ostream & os) const
{
    os << place << ": " << name << ": ";
    start.Print(os, DEFAULT_DATETIME_FORMAT);
    os << ", duration: ";
    duration.Print(os, DEFAULT_TIMESPAN_FORMAT);
    os << ", repeats every year";
    if(repeats > 0)
    {
        os << ", " << repeats << " times in total";
    }
}

void YearlyRepeatingEvent::FillWithVirtualEvents(std::vector<VirtualEvent> & putHere, const DateTime & from,
    const DateTime & to, std::shared_ptr<Event> & ptr) const
{
   _FillWithVirtualEvents(putHere, from, to, ptr, 1, &DateTime::AddYears);
}

shared_ptr<Event> YearlyRepeatingEvent::SplitShift(const TimeSpan & ts, int from,
    const std::shared_ptr<Person> & owner)
{
    return _SplitShift(ts, from, owner, 1, &DateTime::AddYears);
}

void YearlyRepeatingEvent::ExportEventTypeSpecificInfo(ofstream & file) const
{
    file << CHAR_YES << endl << (int)ET_YearlyRepeatingEvent << endl << repeats << endl;
}
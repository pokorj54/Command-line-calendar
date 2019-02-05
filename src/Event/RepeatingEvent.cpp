#include "RepeatingEvent.hpp"
#include "OneTimeEvent.hpp"

using namespace std;

RepeatingEvent::RepeatingEvent(const string & name, const string & place, const DateTime & start,
    const TimeSpan & duration, const shared_ptr<Person> & owner, size_t repeats):
    Event(name, place, start, duration, owner), repeats(repeats)
{}

void RepeatingEvent::_FillWithVirtualEvents(vector<VirtualEvent> & putHere, const DateTime & from,
    const DateTime & to, shared_ptr<Event> & ptr, int periode, DateTime::TimeAddMethod t) const
{
    DateTime startCopy = start;
    DateTime end = startCopy + duration;
    size_t repeatNum = 0;
    while(startCopy < to && (repeats == 0 || repeats >= repeatNum))
    {
        if(end > from)
        {
            putHere.push_back(VirtualEvent(startCopy, end, ptr, repeatNum));
        }
        (startCopy.*t)(periode);
        end = startCopy + duration;
        ++repeatNum;
    }
}

std::shared_ptr<Event> RepeatingEvent::_SplitShift(const TimeSpan & ts, int from,
    const std::shared_ptr<Person> & owner, int periode, DateTime::TimeAddMethod t)
{
    if((from > (int)repeats && repeats != 0) || from <= 0)
    {
        throw InvalidUseException();
    }
    bool withoutBound = repeats == 0;
    DateTime startCopy = start;
    startCopy = (startCopy.*t)(periode * from) + ts;
    int newRepeats = repeats - from;
    repeats = from - 1;
    if(from == 0)
    {
        DateTime tmp = start;
        start = startCopy;
        startCopy = tmp;
        return make_shared<OneTimeEvent>(name, place, startCopy, duration, owner);
    }
    else if(newRepeats == 0)
    {
        return make_shared<OneTimeEvent>(name, place, startCopy, duration, owner);
    }
    if(withoutBound)
    {
        newRepeats = 0;
    }
    return MakeSimilar(name, place, startCopy, duration, owner, newRepeats);
}
#include "EventType.hpp"

#include <algorithm>

std::vector<EventType> GetRepeatingEventTypes()
{
    std::vector<EventType> eTypes {
        ET_MonthyDateRepeatingEvent,
        ET_NDaysRepeatingEvent,
        ET_YearlyRepeatingEvent
    };
    sort(eTypes.begin(), eTypes.end());
    return eTypes;
}

std::ostream & operator << ( std::ostream & out, const EventType & eventType )
{
    switch (eventType)
    {
        case ET_MonthyDateRepeatingEvent:
            out << "Monthly repeat date";
            break;
        case ET_NDaysRepeatingEvent:
            out << "Repeat every N days";
            break;
        case ET_OneTimeEvent:
            out << "Without repeat";
            break;
        case ET_YearlyRepeatingEvent:
            out << "Repeat yearly";
            break;
        default:
            out << "Unknown event type";
    }
    return out;
}
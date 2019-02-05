#ifndef EventType_6ffa81be6628419ebe00ad423f74fcea
#define EventType_6ffa81be6628419ebe00ad423f74fcea

#include <ostream>
#include <vector>

/**
 * @brief Enum that corresponds to Event types
 * 
 */
enum EventType
{
    ET_OneTimeEvent = -1,
    ET_NDaysRepeatingEvent = 0,
    ET_MonthyDateRepeatingEvent = 1,
    ET_YearlyRepeatingEvent = 2
};

std::vector<EventType> GetRepeatingEventTypes();
std::ostream & operator << (std::ostream & out, const EventType & eventType);

#endif //EventType_6ffa81be6628419ebe00ad423f74fcea
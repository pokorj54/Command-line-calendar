#include "InvalidDateTimeException.hpp"

InvalidDateTimeException::InvalidDateTimeException(int year, int month, int day, int hour, int minute, int second): 
    year(year), month(month), day(day), hour(hour), minute(minute), second(second)
{}

void InvalidDateTimeException::Message(std::ostream & o) const
{
    o << "Invalid DateTime entered" << std::endl;
}
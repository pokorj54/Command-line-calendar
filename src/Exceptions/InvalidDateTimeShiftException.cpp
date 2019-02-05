#include "InvalidDateTimeShiftException.hpp"

InvalidDateTimeShiftException::InvalidDateTimeShiftException(int years, int months, int days, int addMonths): 
    years(years),months(months), days(days), addMonths(addMonths)
{}
void InvalidDateTimeShiftException::Message(std::ostream & o) const 
{
    o << "Shifted date doesn't have a representation" << std::endl;
}
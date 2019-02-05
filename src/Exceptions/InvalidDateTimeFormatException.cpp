#include "InvalidDateTimeFormatException.hpp"

InvalidDateTimeFormatException::InvalidDateTimeFormatException(const std::string & value,
    const std::string & format): value(value), format(format)
{}
InvalidDateTimeFormatException::InvalidDateTimeFormatException(const std::string & format): format(format)
{}

void InvalidDateTimeFormatException::Message(std::ostream & o) const
{
    if(value != "")
    {
        o << "Invalid DateTime format, \"" << value << "\" doesn't fit to format: " << format << std::endl;
    }
    else
    {
        o << "Invalid DateTime format: " << format << std::endl;   
    }
}
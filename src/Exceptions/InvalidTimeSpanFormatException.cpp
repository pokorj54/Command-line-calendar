#include "InvalidTimeSpanFormatException.hpp"

InvalidTimeSpanFormatException::InvalidTimeSpanFormatException(const std::string & value,
    const std::string & format): value(value), format(format)
{}
InvalidTimeSpanFormatException::InvalidTimeSpanFormatException(const std::string & format): format(format)
{}

void InvalidTimeSpanFormatException::Message(std::ostream & o) const
{
    if(value != "")
    {
        o << "Invalid TimeSpan format, \"" << value << "\" doesn't fit to format: " << format << std::endl;
    }
    else
    {
        o << "Invalid TimeSpan format: " << format << std::endl;   
    }
}
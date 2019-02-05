#ifndef InvalidTimeSpanFormatException_70902db7ce8c451999646c17ba0aac4e
#define InvalidTimeSpanFormatException_70902db7ce8c451999646c17ba0aac4e

#include "Exception.hpp"

#include <iostream>

/**
 * @brief Exception signaling that TimeSpan format is not valid 
 *  [for string containing TimeSpan representation]
 * 
 */
class InvalidTimeSpanFormatException: public Exception
{
    private:
        std::string value;
        std::string format;
    public:
        InvalidTimeSpanFormatException(const std::string & value, const std::string & format);
        InvalidTimeSpanFormatException(const std::string & format);
        void Message(std::ostream & o) const override;
};

#endif //InvalidTimeSpanFormatException_70902db7ce8c451999646c17ba0aac4e
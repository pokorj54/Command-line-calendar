#ifndef InvalidDateTimeException_0d0be36c73674d198971a32c54547f09
#define InvalidDateTimeException_0d0be36c73674d198971a32c54547f09

#include "Exception.hpp"

#include <iostream>

/**
 * @brief Exception signaling that given time measures does not form a valid DateTIme
 * 
 */
class InvalidDateTimeException: public Exception
{
    private:
        int year;
        int month;
        int day;
        int hour;
        int minute;
        int second;
    public:
        InvalidDateTimeException(int year, int month, int day, int hour, int minute, int second);
        void Message(std::ostream & o) const override;
};

#endif //InvalidDateTimeException_0d0be36c73674d198971a32c54547f09
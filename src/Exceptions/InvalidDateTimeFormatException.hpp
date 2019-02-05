#ifndef InvalidDateTimeFormatException_c3533262afb543b590fc5592879d076f
#define InvalidDateTimeFormatException_c3533262afb543b590fc5592879d076f

#include "Exception.hpp"

#include <iostream>

/**
 * @brief Exception signaling that DateTime format is not valid 
 *  [for string containing DateTime representation]
 * 
 */
class InvalidDateTimeFormatException: public Exception
{
    private:
        std::string value;
        std::string format;
    public:
        InvalidDateTimeFormatException(const std::string & value, const std::string & format);
        InvalidDateTimeFormatException(const std::string & format);
        void Message(std::ostream & o) const override;
};

#endif //InvalidDateTimeFormatException_c3533262afb543b590fc5592879d076f
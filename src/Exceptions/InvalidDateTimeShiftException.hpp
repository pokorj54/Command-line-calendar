#ifndef InvalidDateTimeShiftException_eaf875b43ef142658871a87b37699309
#define InvalidDateTimeShiftException_eaf875b43ef142658871a87b37699309

#include "Exception.hpp"

/**
 * @brief Exception signaling that given time shift applied to given DateTime object 
 *  does not have a representation
 * 
 */
class InvalidDateTimeShiftException: public Exception
{
    private:
        int years;
        int months;
        int days;
        int addMonths;
    public:
        InvalidDateTimeShiftException( int years, int months, int days, int addMonths);
        void Message(std::ostream & o) const override;
};

#endif //InvalidDateTimeShiftException_eaf875b43ef142658871a87b37699309
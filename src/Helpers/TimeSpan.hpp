#ifndef TimeSpan_9c3dee11625a4758973c8b03c642cf76
#define TimeSpan_9c3dee11625a4758973c8b03c642cf76

#include "../Exceptions/InvalidTimeSpanFormatException.hpp"
#include "../constants.hpp"

#include <ctime>
#include <iostream>

/**
 * @brief Represent a duration between two points in time that can be expressed in seconds
 * 
 */
class TimeSpan
{
    private:
        std::time_t duration;
    public:
        /**
         * @brief Construct a new Time Span object from number of seconds
         * 
         * @param seconds 
         */
        TimeSpan(std::time_t seconds);
        /**
         * @brief Construct a new Time Span object
         * 
         * @param ts string representation of TimeSpan
         * @param format contains literals(%) dHMS separated by delimiters
         * @throws InvalidTimeSpanFormatException if string representation does not correspond
         *  to given format
         */
        TimeSpan(const std::string & ts, const std::string & format = DEFAULT_TIMESPAN_FORMAT);

        bool operator < (const TimeSpan & ts) const;
        bool operator <= (const TimeSpan & ts) const;
        bool operator > (const TimeSpan & ts) const;
        bool operator >= (const TimeSpan & ts) const;
        bool operator == (const TimeSpan & ts) const;
        bool operator != (const TimeSpan & ts) const;

        TimeSpan operator - (const TimeSpan & ts) const;
        TimeSpan operator + (const TimeSpan & ts) const;

        std::time_t GetDuration() const;

        /**
         * @brief Prints representation of TimeSpan object to given ostream
         * 
         * @param[out] os here it will be printed
         * @param format contains literals(%) dHMS separated by delimiters
         * @throws InvalidTimeSpanFormatException if the format is not valid
         */
        void Print(std::ostream & os, const std::string & format = DEFAULT_TIMESPAN_FORMAT) const;

        /**
         * @brief Returns TimeSpan that represents duration of one day
         * 
         * @return TimeSpan 
         */
        static TimeSpan Day();
        /**
         * @brief Checks if given TimeSpan format is valid
         * 
         * @param format is valid if it contains literals(%) dHMS separated by delimiters
         * @return true if format is valid
         * @return false if format is not valid
         */
        static bool IsFormatValid(const std::string & format);

        /**
         * @brief Number of seconds in a minute
         * 
         */
        static const int MINUTESECONDS = 60;
        /**
         * @brief Number of seconds in an hour
         * 
         */
        static const int HOURSECONDS = 60*60;
        /**
         * @brief Number of seconds in a day
         * 
         */
        static const int DAYSECONDS = 60*60*24;
};

#endif //TimeSpan_9c3dee11625a4758973c8b03c642cf76
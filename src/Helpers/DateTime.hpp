#ifndef DateTime_5f0c7bc6d3334db3a6340e3c8a391406
#define DateTime_5f0c7bc6d3334db3a6340e3c8a391406

#include "TimeSpan.hpp"
#include "../Exceptions/InvalidDateTimeException.hpp"
#include "../Exceptions/InvalidDateTimeShiftException.hpp"
#include "../Exceptions/InvalidDateTimeFormatException.hpp"
#include "../constants.hpp"

#include <iostream>
#include <ctime>
#include <unordered_map>

/**
 * @brief Represents a moment in time expressed as a number of seconds from start epoch
 * 
 */
class DateTime
{
    private:
        std::time_t value;
        static std::unordered_map<std::string, int> weekdays;
    public:
        /**
         * @brief Construct a new DateTime object from number of second since the star of epoch
         * 
         */
        DateTime(std::time_t time = 0);
         /**
         * @brief Construct a new DateTime object that represents given moment
         * 
         * @throws InvalidDateTimeException if given parametrs doesn't form valid DateTime
         */
        DateTime(int year, int month, int day, int hour = 0, int minute = 0, int second = 0);
        /**
         * @brief Construct a new DateTime object from string in given format
         * 
         * @param dt string representation of DateTime onject
         * @param format strftime format
         * @throws InvalidDateTimeFormatException if string representation does not correspond
         *  to given format
         * @throws InvalidDateTimeException if format is valid but it doesn't make a valid date
         */
        DateTime(const std::string & dt, const std::string & format = DEFAULT_DATETIME_FORMAT);

        bool operator < (const DateTime & dt) const;
        bool operator <= (const DateTime & dt) const;
        bool operator > (const DateTime & dt) const;
        bool operator >= (const DateTime & dt) const;
        bool operator == (const DateTime & dt) const;
        bool operator != (const DateTime & dt) const;

        TimeSpan operator - (const DateTime & dt) const;
        DateTime operator + (const TimeSpan & t) const;
        DateTime operator - (const TimeSpan & t) const;

        int GetDay() const;
        int GetWeekday() const;
        int GetMonth() const;
        int GetYear() const;

        typedef DateTime & (DateTime::*TimeAddMethod)(int periode);
        DateTime & AddSeconds(int second);
        DateTime & AddMinutes(int minutes);
        DateTime & AddHours(int hours);
        DateTime & AddDays(int days);
        /**
         * @brief adds months to the DateTime object
         * 
         * @param months 
         * @throws InvalidDateTimeShiftException if new date doesn't exist
         * @return DateTime& 
         */
        DateTime & AddMonths(int months);
        /**
         * @brief adds 12 * months to the DateTime object
         * 
         * @param years 
         * @throws InvalidDateTimeShiftException if new date doesn't exist
         * @return DateTime& 
         */
        DateTime & AddYears(int years);

        /**
         * @brief Changes DateTime object to start of the day it represents
         * 
         * @return DateTime& reference to changed object
         */
        DateTime & Date();
        /**
         * @brief Changes DateTime object to start of the week it falls to
         * 
         * @param weekstart Says which day starts the week (Sunday = 0)
         * @return DateTime& reference to changed object
         */
        DateTime & Week(int weekstart = DEFAULT_WEEK_START);
        /**
         * @brief Changes DateTime object to start of the month it falls to
         * 
         * @return DateTime& reference to changed object
         */
        DateTime & Month();

        /**
         * @brief Compares if date of both DatTime objects are same;
         * 
         * @param dt 
         * @return true if both DateTime objects represent moment in same day
         * @return false if DateTime objects does not represent moment in same day
         */
        bool isSameDate(const DateTime & dt) const;
        
        /**
         * @brief Prints representation of DateTime object to given ostream
         * 
         * @param[out] os here it will be printed
         * @param format strftime format
         * @throws InvalidDateTimeFormatException if the format is not valid
         */
        void Print(std::ostream & os, const std::string & format = DEFAULT_DATETIME_FORMAT) const;
        
        /**
         * @brief Returns representation of current moment
         * 
         * @return DateTime 
         */
        static DateTime Now();
        /**
         * @brief Returns representation of start of this day
         * 
         * @return DateTime 
         */
        static DateTime Today();
        /**
         * @brief Returns number identification of week day
         * 
         * @param day name of a weekday
         * @return int number representation of week day (0 = Sunday)
         * @throws out_of_range if string is not valid week day name 
         */
        static int GetWeekday(const std::string & day);
        /**
         * @brief Get the Weekday object
         * 
         * @param day week day representation (0 = Sunday)
         * @return std::string week name
         */
        static std::string GetWeekday(int day);

        /**
         * @brief Checks if given DateTime format is valid
         * 
         * @return true if format is valid
         * @return false if format is not valid
         */
        static bool IsFormatValid(const std::string & format);
};

#endif //DateTime_5f0c7bc6d3334db3a6340e3c8a391406
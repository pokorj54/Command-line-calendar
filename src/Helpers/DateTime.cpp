#include "DateTime.hpp"

#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <algorithm>

using namespace std;


unordered_map<std::string, int> DateTime::weekdays = 
{
    {"sunday", 0},
    {"monday", 1},
    {"tuesday", 2},
    {"wednesday", 3},
    {"thursday", 4},
    {"friday", 5},
    {"saturday", 6}
};

inline struct tm * _Gettm()
{
    time_t now = time(NULL);
    return localtime(&now);
}

bool _GetNumber(int & num, istream & is, int digits)
{
    if(digits <= 0)
    {
        return false;
    }
    num = 0;
    for(int i = 0; i < digits; ++i)
    {
        if(is.eof())
        {
            return false;
        }
        char tmp;
        is >> tmp;
        if(tmp < '0' || tmp > '9')
        {
            return false;
        }
        tmp -= '0';
        num = num*10 + tmp;
    }
    return true;
}

DateTime::DateTime(time_t time): value(time)
{}
DateTime::DateTime(int year, int month, int day, int hour, int minute, int second)
{
    struct tm * ptm = _Gettm();
    bool isDST = ptm->tm_isdst;
    ptm->tm_sec = second;
    ptm->tm_min = minute;
    ptm->tm_hour = hour;
    ptm->tm_mday= day;
    ptm->tm_mon = month - 1;
    ptm->tm_year = year-1900;
    value = mktime(ptm);
    
    struct tm * control = localtime(&value);
    if(isDST && !control->tm_isdst)
    {
        value += TimeSpan::HOURSECONDS;
        control = localtime(&value);
    }
    else if(!isDST && control->tm_isdst)
    {
        value += TimeSpan::HOURSECONDS;
        control = localtime(&value);
    }

    if(second != control->tm_sec || minute != control->tm_min ||
        hour != control->tm_hour || day != control->tm_mday ||
        month - 1 != control->tm_mon || year - 1900 != control->tm_year)
    {
        throw InvalidDateTimeException(year, month, day, hour, minute, second);
    }
}
DateTime::DateTime(const string & dt, const string & format)
{
    int sec = 0;
    int min = 0;
    int hour = 0;
    int day = 0;
    int mon = 0;
    int year = 0;
    
    bool isLiteral = false;
    istringstream iss(dt);
    for(char c : format)
    {
        if(iss.eof() || iss.fail())
        {
            throw InvalidDateTimeFormatException(dt,format);
        }
        if(isLiteral)
        {
            if(c == 'Y')
            {
                if(!_GetNumber(year, iss, 4))
                {
                    throw InvalidDateTimeFormatException(dt,format);
                }
            }
            else
            {
                int tmp;
                if(!_GetNumber(tmp, iss, 2))
                {
                    throw InvalidDateTimeFormatException(dt,format);
                }
                switch(c)
                {
                    case 'S':
                        sec = tmp;
                        break;
                    case 'M':
                        min = tmp;
                        break;
                    case 'H':
                        hour = tmp;
                        break;
                    case 'd':
                        day = tmp;
                        break;
                    case 'm':
                        mon = tmp;
                        break;
                    default:
                        throw InvalidDateTimeFormatException(dt,format);
                }
            }
            isLiteral = false;
        }
        else if(c == '%')
        {
            isLiteral = true;
        }
        else
        {
            char tmp = 0;
            iss >> tmp;
            if(tmp != c)
            {
                throw InvalidDateTimeFormatException(dt,format);
            }
        }
    }
    char tmp;
    iss >> tmp;
    if(!iss.eof())
    {
        throw InvalidDateTimeFormatException(dt, format);
    }

    *this = DateTime(year, mon, day, hour, min, sec);
}

bool DateTime::operator < (const DateTime & dt) const
{
    return value < dt.value;
}
bool DateTime::operator > (const DateTime & dt) const
{
    return dt < *this;
}
bool DateTime::operator <= (const DateTime & dt) const
{
    return !(dt < *this);
}
bool DateTime::operator >= (const DateTime & dt) const
{
    return !(*this < dt);
}
bool DateTime::operator == (const DateTime & dt) const
{
    return value == dt.value;
}
bool DateTime::operator != (const DateTime & dt) const
{
    return value != dt.value;
}

TimeSpan DateTime::operator - (const DateTime & dt) const
{
    return TimeSpan(value - dt.value);
}
DateTime DateTime::operator + (const TimeSpan & t) const
{
    return DateTime(value + t.GetDuration());
}
DateTime DateTime::operator - (const TimeSpan & t) const
{
    return DateTime(value - t.GetDuration());
}

int DateTime::GetDay() const
{
    struct tm * ptm = localtime(&value);
    return ptm->tm_mday;
}
int DateTime::GetWeekday() const
{
    struct tm * ptm = localtime(&value);
    return ptm->tm_wday;
}
int DateTime::GetMonth() const
{
    struct tm * ptm = localtime(&value);
    return ptm->tm_mon + 1;
}
int DateTime::GetYear() const
{
    struct tm * ptm = localtime(&value);
    return ptm->tm_year + 1900;
}

DateTime & DateTime::AddSeconds(int seconds)
{
    value += seconds;
    return *this;
}
DateTime & DateTime::AddMinutes(int minutes)
{
    return this->AddSeconds(minutes * 60);
}
DateTime & DateTime::AddHours(int hours)
{
    return this->AddMinutes(hours * 60);
}
DateTime & DateTime::AddDays(int days)
{
    struct tm * ptm = localtime(&value);
    bool isDST = ptm->tm_isdst;
    this->AddHours(days * 24);
    struct tm * copy = localtime(&value);
    if(isDST && !copy->tm_isdst)
    {
        this->AddHours(1);
    }
    else if(!isDST && copy->tm_isdst)
    {
        this->AddHours(-1);
    }
    return *this;
}
DateTime & DateTime::AddMonths(int months)
{
    struct tm * ptm = localtime(&value);
    struct tm * copy = localtime(&value);
    int monthsCopy = months;
    bool isDST = ptm->tm_isdst;

    months += ptm->tm_mon + 1;
    int years = months / 12;
    months -= years * 12;
    --months;
    if(months < 0)
    {
        --years;
        months += 12;
    }

    ptm->tm_mon = months;
    ptm->tm_year += years;
    value = mktime(ptm);

    struct tm * control = localtime(&value);
    if(isDST && !control->tm_isdst)
    {
        this->AddHours(1);
    }
    else if(!isDST && control->tm_isdst)
    {
        this->AddHours(-1);
    }
    control = localtime(&value); 
    if(months != control->tm_mon || copy->tm_mday != control->tm_mday)
    {
        throw InvalidDateTimeShiftException(copy->tm_year, copy->tm_mon, copy->tm_mday, monthsCopy);
    }

    return *this;
}
DateTime & DateTime::AddYears(int years)
{
    return this->AddMonths(years * 12);
}

DateTime & DateTime::Date()
{
    struct tm * ptm = localtime(&value);

    ptm->tm_sec = 0;
    ptm->tm_min = 0;
    ptm->tm_hour = 0;

    value = mktime(ptm);
    return *this;
}
DateTime & DateTime::Week(int weekstart)
{
    struct tm * ptm = localtime(&value);

    ptm->tm_sec = 0;
    ptm->tm_min = 0;
    ptm->tm_hour = 0;

    int days = ptm->tm_wday - weekstart;
    value = mktime(ptm);
    if(days < 0)
    {
        days += 7;
    }
    this->AddDays(-days);
    //TODO
    return *this;
}
DateTime & DateTime::Month()
{
    struct tm * ptm = localtime(&value);

    ptm->tm_sec = 0;
    ptm->tm_min = 0;
    ptm->tm_hour = 0;
    ptm->tm_mday = 1;

    value = mktime(ptm);
    return *this;
}

bool DateTime::isSameDate(const DateTime & dt) const
{
    DateTime tmp1 = *this;
    DateTime tmp2 = dt;

    tmp1.Date();
    tmp2.Date();

    return tmp1 == tmp2;
}

void DateTime::Print(ostream & os, const string & format) const
{
    struct tm * ptm = localtime(&value);
    char buffer[32];
    strftime(buffer, 32, format.c_str(), ptm);
     os << buffer;
}
DateTime DateTime::Now()
{
    struct tm * ptm = _Gettm();

    DateTime dt;
    dt.value = mktime(ptm);
    return dt; 
}
DateTime DateTime::Today()
{
    struct tm * ptm = _Gettm();

    ptm->tm_sec = 0;
    ptm->tm_min = 0;
    ptm->tm_hour = 0;

    DateTime dt;
    dt.value = mktime(ptm);
    return dt; 
}
int DateTime::GetWeekday(const string & day)
{
    string lcday = day;
    transform(lcday.begin(), lcday.end(), lcday.begin(), ::tolower);
    int res = DateTime::weekdays.at(lcday);
    return res;
}
string DateTime::GetWeekday(int day)
{
    day %= 7;
    switch(day)
    {
        case 0: return "Sunday";
        case 1: return "Monday";
        case 2: return "Tuesday";
        case 3: return "Wednesday";
        case 4: return "Thursday";
        case 5: return "Friday";
        case 6: return "Saturday";
    }
    return "";
}

bool DateTime::IsFormatValid(const std::string & format)
{
    string literals = "SMHdmY";
    bool isLiteral = false;
    for(char c : format)
    {
        if(isLiteral)
        {
            if(literals.find_first_of(c) == string::npos)
            {
                return false;
            }
            isLiteral = false;
        }
        else if(c =='%')
        {
            isLiteral = true;
        }
    }
    return true;
}

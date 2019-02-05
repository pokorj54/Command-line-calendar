#include "TimeSpan.hpp"

#include <iomanip>
#include <sstream>

using namespace std;

TimeSpan::TimeSpan(time_t seconds): duration(seconds)
{}
TimeSpan::TimeSpan(const string & ts, const string & format)
{
    duration = 0;
    bool isLiteral = false; //%
    stringstream ss(ts);
    for(char c : format)
    {
        if(ss.fail() || ss.eof())
        {
            throw InvalidTimeSpanFormatException(ts, format);
        }
        if(isLiteral)
        {
            int tmp = 0;
            switch(c)
            {
                case 'S':
                    ss >> tmp;
                    duration += tmp;
                    break;
                case 'M':
                    ss >> tmp;
                    duration += tmp*MINUTESECONDS;
                    break;
                case 'H':
                    ss >> tmp;
                    duration += tmp*HOURSECONDS;
                    break;
                case 'd':
                    ss >> tmp;
                    duration += tmp*DAYSECONDS;
                    break;
                default:
                    throw InvalidTimeSpanFormatException(ts, format);
            }
            isLiteral = false;
        }
        else
        {
            if(c == '%')
            {
                isLiteral = true;
            }
            else
            {
                char tmp;
                ss >> tmp;
                if(tmp !=c)
                {
                    throw InvalidTimeSpanFormatException(ts, format);
                }
            }
        }
    }
    char tmp;
    ss >> tmp;
    if(!ss.eof())
    {
        throw InvalidTimeSpanFormatException(ts, format);
    }
}

bool TimeSpan::operator < (const TimeSpan & ts) const
{
    return duration < ts.duration;
}
bool TimeSpan::operator > (const TimeSpan & ts) const
{
    return ts < *this;
}
bool TimeSpan::operator <= (const TimeSpan & ts) const
{
    return !(ts < *this);
}
bool TimeSpan::operator >= (const TimeSpan & ts) const
{
    return !(*this < ts);
}
bool TimeSpan::operator == (const TimeSpan & ts) const
{
    return duration == ts.duration;
}
bool TimeSpan::operator != (const TimeSpan & ts) const
{
    return duration != ts.duration;
}

TimeSpan TimeSpan::operator - (const TimeSpan & ts) const
{
    return TimeSpan(this->duration - ts.duration);
}
TimeSpan TimeSpan::operator + (const TimeSpan & ts) const
{
    return TimeSpan(this->duration + ts.duration); 
}

time_t TimeSpan::GetDuration() const
{
    return duration;
}

void TimeSpan::Print(ostream & os, const string & format) const
{
    int seconds = duration;
    int days = seconds / DAYSECONDS;
    seconds -= days * DAYSECONDS;
    int hours = seconds / HOURSECONDS;
    seconds -= hours * HOURSECONDS;
    int minutes = seconds / MINUTESECONDS;
    seconds -= minutes * MINUTESECONDS;

    bool isLiteral = false; //%

    for(char c : format)
    {
        if(isLiteral)
        {
            switch(c)
            {
                case 'd':
                    os << days;
                    break;
                case 'H':
                    os << hours;
                    break;
                case 'M':
                    os << minutes;
                    break;
                case 'S':
                    os << seconds;
                    break;
                default:
                    throw InvalidTimeSpanFormatException(format);
            }
                isLiteral = false;
        }
        else
        {
            if(c == '%')
            {
                isLiteral = true;
            }
            else
            {
                os << c;
            }
        }
    }
}

TimeSpan TimeSpan::Day()
{
    return TimeSpan(DAYSECONDS);
}
bool TimeSpan::IsFormatValid(const string & format)
{
    bool isLiteral = false; //%
    bool isDelimiter = false;
    string literals = "SMHd";
    for(char lit: literals)
    {
        char tmp[3];
        tmp[0] = '%';
        tmp[1] = lit;
        tmp[2] = 0;
        string s = tmp;
        if(format.find(s) == string::npos)
        {
            return false;
        }
    }
    for(char c : format)
    {
        if(isLiteral)
        {
            if(literals.find_first_of(c) == string::npos)
            {
                return false;
            }
            isDelimiter = true;
            isLiteral = false;
        }
        else if(isDelimiter)
        {
            if(c == '%')
            {
                return false;
            }
            isDelimiter = false;
        }
        else if(c == '%')
        {
            isDelimiter = false;
            isLiteral = true;
        }
    }
    return true;
}
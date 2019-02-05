#include "CommandLine.hpp"
#include "Helpers/TimeSpan.hpp"
#include "constants.hpp"

#include <iostream>

using namespace std;

bool CheckConstants()
{
    if(!TimeSpan::IsFormatValid(DEFAULT_TIMESPAN_FORMAT))
    {
        cout << "Invalid DEFAULT_TIMESPAN_FORMAT" << endl;
        return false;
    }
    else if(DEFAULT_WEEK_START > 6 || DEFAULT_WEEK_START < 0)
    {
        cout << "Invalid DEFAULT_WEEK_START" << endl;
        return false;
    }
    else if(!DateTime::IsFormatValid(DEFAULT_DATETIME_FORMAT))
    {
        cout << "Invalid DEFAULT_DATETIME_FORMAT" << endl;
        return false;
    }
    else if(!DateTime::IsFormatValid(DEFAULT_DATE_FORMAT))
    {
        cout << "Invalid DEFAULT_DATE_FORMAT" << endl;
        return false;
    }
    else if(!DateTime::IsFormatValid(DEFAULT_TIME_FORMAT))
    {
        cout << "Invalid DEFAULT_TIME_FORMAT" << endl;
        return false;
    }
    return true;
}

int main(void)
{
    if(!CheckConstants())
    {
        cout << "Invalid values in constants, exiting program" << endl;
        return 1;
    }
    CommandLine c;
    c.ImportAll();
    c.HandleCommands();
    c.ExportAll();
    return 0;
}
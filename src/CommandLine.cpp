#include "CommandLine.hpp"

#include "Exceptions/InvalidNoArgumentsException.hpp"
#include "Exceptions/InvalidCommandUseException.hpp"
#include "Exceptions/InvalidUseException.hpp"
#include "Exceptions/InvalidArgumentException.hpp"

#include "Event/EventType.hpp"
#include "Calendar/CalendarType.hpp"
#include "Person/Person.hpp"

#include "Event/OneTimeEvent.hpp"
#include "Event/MonthyDateRepeatingEvent.hpp"
#include "Event/NDaysRepeatingEvent.hpp"
#include "Event/YearlyRepeatingEvent.hpp"

#include "Calendar/DailyCalendar.hpp"
#include "Calendar/MonthlyCalendar.hpp"
#include "Calendar/WeeklyCalendar.hpp"
#include "Calendar/AllEventsCalendar.hpp"

#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>

using namespace std;

/**
 * @brief Initialization of commands
 * 
 */
unordered_map<string, std::pair<CommandLine::HandleCmd,std::string>> CommandLine::cmdTranslation =
{
    {"register", make_pair(&CommandLine::HandleRegistration, "1 - name: creates user with given name")},
    {"login", make_pair(&CommandLine::HandleLogin, "1 - name: logs in user with given name")},
    {CMD_LOGOUT, make_pair(&CommandLine::HandleLogout, "0: logs out user that is currently logged in")},
    {"users", make_pair(&CommandLine::HandleUsersShow, "0: shows all existing users")},
    {"calendar", make_pair(&CommandLine::HandleCalendarDisplay, "0: creates calendar for today, 1 - date: creates calendar for given day")},
    {"next", make_pair(&CommandLine::HandleCalendarNext, "0: shows next calendar page")},
    {"prev", make_pair(&CommandLine::HandleCalendarPrev, "0: shows previous calendar page")},
    {"leave", make_pair(&CommandLine::HandleCalendarLeave, "0: closes calendar")},
    {"refresh", make_pair(& CommandLine::HandleCalendarRefresh, "0: refreshes current calendar page")},
    {"search", make_pair(&CommandLine::HandleEventSearch, "1 - string: searches for given string in the event name and place")},
    {CMD_CREATE, make_pair(&CommandLine::HandleEventCreation, "3 - date and time, duration, name, place: creates event from given parametres")},
    {"select", make_pair(&CommandLine::HandleEventSelect, "1 - index: selects event from current calendar with given index")},
    {CMD_DESELECT, make_pair(&CommandLine::HandleEventDeselect, "0: deselects selected event")},
    {"shift", make_pair(&CommandLine::HandleEventShift, "1 - duration: shifts event for given duration")},
    {CMD_ADD, make_pair(&CommandLine::HandleParticipantAdd, "1 - name: adds user to selected event")},
    {"remove", make_pair(&CommandLine::HandleParticipantRemove, "1 - name: removes user to selected event")},
    {"show", make_pair(&CommandLine::HandleEventShow, "0: shows description for selected event")},
    {"split", make_pair(&CommandLine::HandleEventSplitShift, "0: splits event from selected index, 1 - duration: splits event from selected index and shifts the new event")},
    {"dismiss", make_pair(&CommandLine::HandleEventDismiss, "0: completely removes selected event")},
    {"changename", make_pair(&CommandLine::HandleEventChangeName, "1 - name: changes name of selected event")},
    {"changeplace", make_pair(&CommandLine::HandleEventChangePlace, "1 - place: changes plase of the selected event" )},
    {"find", make_pair(&CommandLine::HandleFindingFreeTime, "2 - date, duration: finds first available time when could event start")},
    {"help", make_pair(&CommandLine::HandleHelp, "0: shows all commands and their description, 1 - command: shows description for command")},
    {"export", make_pair(&CommandLine::HandleExport, "1 - file: exports all evenst in " + FILE_PATH + "file" + FILE_SUFFIX )},
    {"import", make_pair(&CommandLine::HandleImport, "1 - file: imports events from " + FILE_PATH + "file" + FILE_SUFFIX )}
};
CommandLine::CommandLine(): users(), loggedin(nullptr), displaying(nullptr), active(nullptr),
    eventSerialNum(NO_START_SELECTED), input(&cin), output(&cout), isImporting(false),
    checkingValidity(false), DateTimeFormat(DEFAULT_DATETIME_FORMAT), 
    TimeSpanFormat(DEFAULT_TIMESPAN_FORMAT)
{}

CommandLine::Arguments::Arguments(): noArgs(0)
{}
void CommandLine::Arguments::PushBack(const string & argument)
{
    ++noArgs;
    arguments.push_back(argument);
}
string CommandLine::Arguments::PopFirst()
{
    if(arguments.empty())
    {
        throw InvalidNoArgumentsException(noArgs, false);
    }
    string res = arguments.front();
    arguments.pop_front();
    return res;
}
string CommandLine::Arguments::PopFirstIfNotEmpty()
{
    if(arguments.empty())
    {
        return "";
    }
    string res = arguments.front();
    arguments.pop_front();
    return res;
}
void CommandLine::Arguments::ThrowIfNotEmpty()
{
    if(!arguments.empty())
    {
        throw InvalidNoArgumentsException(noArgs, true);
    }
}

/**
 * @brief Ostream that does not print anywhere
 * 
 */
class SilentOut: public ostream
{
    public:
        template <typename T>
        ostream & operator << (const T & t) {return *this;}
};
void CommandLine::ImportMode(ifstream & file)
{
    input = &file;
    output = new SilentOut();
    isImporting = true;
    DateTimeFormat = IE_DATETIME_FORMAT;
    TimeSpanFormat = IE_TIMESPAN_FORMAT;
}
void CommandLine::EndImportMode()
{
    if(isImporting)
    {
        delete output;
        isImporting = false;
    }
    input = &cin;
    output = &cout;
    DateTimeFormat = DEFAULT_DATETIME_FORMAT;
    TimeSpanFormat = DEFAULT_TIMESPAN_FORMAT;
}

string _GetCommandAndArgument(string command, CommandLine::Arguments & outArguments)
{
    size_t pos = command.find(" ");
    if(pos == string::npos)
    {   
        return command;
    }
    string result = command.substr(0, pos);
    command = command.substr(pos +1, command.length());
    
    list<string> tmp;

    pos = command.find("\"");
    bool qmark = 0;
    while(pos != string::npos)
    {
        tmp.push_back(command.substr(0, pos));
        command = command.substr(pos, command.length());
        qmark = !qmark;
        pos = command.find("\"", qmark) + qmark;
    }
    tmp.push_back(command);

    for(string & s : tmp)
    {
        if(s == "")
        {
            continue;
        }
        else if(s[0] == '"')
        {
            outArguments.PushBack(s.substr(1, s.length() - 2));
        }
        else
        {
            pos = s.find(" ");
            while(pos != string::npos)
            {
                string tmpstring = s.substr(0, pos);
                if(tmpstring.find_first_not_of(' ') != string::npos)
                {
                    outArguments.PushBack(tmpstring);
                }
                s = s.substr(pos + 1, s.length());
                pos = s.find(" ");
            }
            if(s.find_first_not_of(' ') != string::npos)
            {
                outArguments.PushBack(s);
            }
        }
    }
    return result;
}

void CommandLine::PrintPrefix(ostream & os) const
{
    if(loggedin)
    {
        os << loggedin->GetName();
    }
    if(displaying)
    {
        os << "/";
        displaying->PrintPrefix(os);
    }
    if(active)
    {
        os << "/";
        os << active->GetPlace() << ": " <<active->GetName();
        if(eventSerialNum >= 0)
        {
            os << "(" << eventSerialNum << ")";
        }
    }
    os << "> ";
}
bool _AskYesOrNo(ostream & os, istream & is, const string & question, bool safe = false)
{
    bool answered = false;
    bool answer = false;
    while(!answered && !is.eof() && !is.fail())
    {
        os << question << "["<< CHAR_YES << "/" << CHAR_NO << "]: ";
        string tmp;
        getline(is, tmp);
        if(tmp[0] == CHAR_YES)
        {
            answered = true;
            answer = true;
        }
        else if(tmp[0] == CHAR_NO)
        {
            answered = true;
        }
    }
    if((is.eof() || is.fail()) && !safe)
    {
        throw InvalidUseException();
    }
    return answer;
}
template<typename InputIt>
void _PrintMultiChoice(ostream & os, InputIt begin, InputIt end)
{
    int qnum = 0;
    for(InputIt it = begin; it != end; ++it)
    {
        os << qnum << ") "  << (*it) << endl;
        ++qnum;
    }
}
int _GetNumberWithin(ostream & os, istream & is, const string & msg, int infimum, int supremum = numeric_limits<int>::max())
{
    int res = infimum - 1;
    while((res < infimum || res > supremum) && !is.eof() && !is.fail())
    {
        os << msg;
        string tmp;
        getline(is, tmp);
        if(tmp.find_first_not_of("0123456789") == string::npos && tmp != "")
        {
            res = stoi(tmp);
        }
    }
    if(is.eof() || is.fail())
    {
        throw InvalidUseException();
    }
    return res;
}
template<typename InputIt>
int _AskMultiChoice(ostream & os, istream & is, InputIt begin, InputIt end)
{
    _PrintMultiChoice(os, begin,end);
    int size = end - begin;
    stringstream msg;
    msg << "Choose option (" << 0 << " - " << size - 1 << "): ";
    return _GetNumberWithin(os, is, msg.str(), 0, size - 1);
}

bool CommandLine::Import(const string & fileName)
{
    ifstream file;
    file.open(FILE_PATH + fileName + FILE_SUFFIX);
    CommandLine simulation;
    simulation.ImportMode(file);
    string username = "\n";
    simulation.users.AddNewPerson(username);
    simulation.loggedin = simulation.users.GetPerson(username);
    simulation.checkingValidity = true;
    if(!simulation.HandleCommands())
    {
        simulation.EndImportMode();
        return false;
    }
    simulation.checkingValidity = false;
    simulation.EndImportMode();
    file.close();
    file.open(FILE_PATH + fileName + FILE_SUFFIX);
    ImportMode(file);
    HandleCommands();
    EndImportMode();
    file.close();
    return true;
}

bool CommandLine::HandleCommands()
{
    while(!input->eof() && !input->fail())
    {
        PrintPrefix(*output);
        string fullCommand;
        getline(*input, fullCommand);
        if(fullCommand.find_first_not_of(" \t") == string::npos)
        {
            continue; //no command given
        }
        else if(count(fullCommand.begin(), fullCommand.end(), '"') % 2 == 1)
        {
            *output << "Invalid command - odd number of \"" << endl;
            continue;
        }

        Arguments arguments;
        string cmdName = _GetCommandAndArgument(fullCommand, arguments);

        if(cmdName == CMD_EXIT) //it's the only command that can affect the command cycle 
        {
            break;
        }

        HandleCmd method;
        try
        {
            method = cmdTranslation.at(cmdName).first;
        }
        catch(const out_of_range & e)
        {
            *output << "Unknown command" << endl;
            continue;
        }

        try
        {
            ((*this).*method)(arguments);
        }
        catch(const Exception & e)
        {
            e.Message(*output);
            if(checkingValidity)
            {
                return false;
            }
        }
    }
    return !input->fail();
}

void CommandLine::HandleRegistration(Arguments & args)
{
    if(loggedin)
    {
       throw InvalidCommandUseException();
    }

    string name = args.PopFirst();
    args.ThrowIfNotEmpty();
    bool res = users.AddNewPerson(name);

    if(!res)
    {
        *output << "Account with name " << name << " already exists" << endl;
    }
}
void CommandLine::HandleLogin(Arguments & args)
{
    if(loggedin)
    {
       throw InvalidCommandUseException();
    }

    string name = args.PopFirst();
    args.ThrowIfNotEmpty();
    try
    {
        loggedin = users.GetPerson(name);
    }
    catch(const out_of_range & e)
    {
        *output << "User of this name does not exist" << endl;
    }
}
void CommandLine::HandleLogout(Arguments & args)
{
    if(!loggedin)
    {
       throw InvalidCommandUseException();
    }

    args.ThrowIfNotEmpty();
    loggedin = nullptr;
    displaying = nullptr;
    active = nullptr;
}
void CommandLine::HandleUsersShow(Arguments & args)
{
    args.ThrowIfNotEmpty();
    for(const pair<string, shared_ptr<Person>> & p : users.GetUsers())
    {
        p.second->Print(*output);
        *output << endl;
    }
}
void  CommandLine::HandleEventCreation(Arguments & args)
{
    if(!loggedin)
    {
       throw InvalidCommandUseException();
    }

    string start = args.PopFirst();
    string duration = args.PopFirst();
    string eventName = args.PopFirst();
    string eventPlace = args.PopFirst();
    shared_ptr<Event> event = nullptr;
    args.ThrowIfNotEmpty();

    DateTime eventStart = DateTime(start, DateTimeFormat);
    TimeSpan eventDuration = TimeSpan(duration, TimeSpanFormat);
    if(eventDuration.GetDuration() <= 0)
    {
        throw InvalidArgumentException(duration, 2);
    }

    bool repeat = _AskYesOrNo(*output, *input, "Repeat this event?");
    if(repeat)
    {
        vector<EventType> eventTypes = GetRepeatingEventTypes();
        int answer = _AskMultiChoice(*output, *input, eventTypes.begin(), eventTypes.end());
        EventType eType = eventTypes.at(answer);
        
        int repeats = _GetNumberWithin(*output, *input, "Choose number of repeats (0 = repeat forever): ", 0);
        int periode;

        switch (eType)
        {
            case ET_MonthyDateRepeatingEvent: 
                event = make_shared<MonthyDateRepeatingEvent>(eventName, eventPlace, eventStart,
                    eventDuration, loggedin, repeats);
                break;
            case ET_NDaysRepeatingEvent:
                periode = _GetNumberWithin(*output, *input, "Choose periode in days (minimum 1 day): ", 1);
                event = make_shared<NDaysRepeatingEvent>(eventName, eventPlace, eventStart,
                    eventDuration, loggedin, periode, repeats);
                break;
            case ET_YearlyRepeatingEvent: 
                event = make_shared<YearlyRepeatingEvent>(eventName, eventPlace, eventStart,
                    eventDuration, loggedin, repeats);
                break;
            default: throw "Invalid event type";
        }
    }
    else
    {
        event = make_shared<OneTimeEvent>(eventName, eventPlace, eventStart, eventDuration, loggedin);
    }
    eventSerialNum = NO_START_SELECTED;
    if(!loggedin->AddEvent(event))
    {
        *output << "That event already exists" << endl;
        active = nullptr;
        return;
    }
    active = event;
}
void CommandLine::HandleCalendarDisplay(Arguments & args)
{
    if(!loggedin)
    {
       throw InvalidCommandUseException();
    }

    string datestr = args.PopFirstIfNotEmpty();
    args.ThrowIfNotEmpty();
    DateTime dt;

    if(datestr == "")
    {
        dt = DateTime::Today();
    }
    else 
    {
        dt = DateTime(datestr, DEFAULT_DATE_FORMAT);
    }

    vector<CalendarType> calendarTypes = GetCalendarTypes();
    int answer = _AskMultiChoice(*output, *input, calendarTypes.begin(), calendarTypes.end());
    CalendarType cType = calendarTypes.at(answer);
    
    switch(cType)
    {
        case CT_DailyCalendar:
            displaying = make_shared<DailyCalendar>(loggedin->GetEvents(), dt);
            break;
        case CT_WeeklyCalendar:
            displaying = make_shared<WeeklyCalendar>(loggedin->GetEvents(), dt);
            break;
        case CT_MonthlyCalendar:
            displaying = make_shared<MonthlyCalendar>(loggedin->GetEvents(), dt);
            break; 
        case CT_AllEventsCalendar:
            if(datestr != "")
            {
                throw InvalidUseException();
            }
            displaying = make_shared<AllEventsCalendar>(loggedin->GetEvents());
            break; 
        default:
            throw "Invalid calendar type";
    }
    displaying->FillWithVirtualEvents();
    displaying->Print(*output);
}
void  CommandLine::HandleCalendarNext(Arguments & args)
{
    if(!displaying)
    {
       throw InvalidCommandUseException();
    }
    args.ThrowIfNotEmpty();
    displaying->Next();
    displaying->FillWithVirtualEvents();
    displaying->Print(*output);
}
void  CommandLine::HandleCalendarPrev(Arguments & args)
{
    if(!displaying)
    {
       throw InvalidCommandUseException();
    }
    args.ThrowIfNotEmpty();
    displaying->Prev();
    displaying->FillWithVirtualEvents();
    displaying->Print(*output);
}
void CommandLine::HandleCalendarLeave(Arguments & args)
{
    if(!displaying && !active)
    {
       throw InvalidCommandUseException();
    }
    args.ThrowIfNotEmpty();
    displaying = nullptr;
}
void CommandLine::HandleCalendarRefresh(Arguments & args)
{
    if(!displaying)
    {
        throw InvalidCommandUseException();
    }
    args.ThrowIfNotEmpty();
    displaying->FillWithVirtualEvents();
    displaying->Print(*output);
}
void CommandLine::HandleEventSearch(Arguments & args)
{
    if(!loggedin)
    {
       throw InvalidCommandUseException();
    }
    string searchStr = args.PopFirst();
    args.ThrowIfNotEmpty();
    displaying = make_shared<AllEventsCalendar>(loggedin->GetEvents(), searchStr);
    displaying->FillWithVirtualEvents();
    displaying->Print(*output);
}
void CommandLine::HandleEventSelect(Arguments & args)
{
    if(!loggedin || !displaying)
    {
       throw InvalidCommandUseException();
    }
    string selectNum = args.PopFirst();
    args.ThrowIfNotEmpty();
    stringstream ss(selectNum);
    int selected;
    ss >> selected;
    if(!ss.eof() || ss.fail())
    {
        throw InvalidArgumentException(selectNum, 1);
    }

    try
    {
        active = displaying->GetEvent(selected, &eventSerialNum);
    }
    catch(const out_of_range & exception)
    {
        throw InvalidArgumentException(selectNum, 1);
    }
}
void CommandLine::HandleEventDeselect(Arguments & args)
{
    if(!active)
    {
       throw InvalidCommandUseException();
    }
    args.ThrowIfNotEmpty();
    active = nullptr;
    eventSerialNum = NO_START_SELECTED;
}
void CommandLine::HandleEventShift(Arguments & args)
{
    if(!active)
    {
       throw InvalidCommandUseException();
    }
    string shiftStr = args.PopFirst();
    args.ThrowIfNotEmpty();
    TimeSpan shift(shiftStr);
    active->Shift(shift);
}
void CommandLine::HandleEventSplitShift(Arguments & args)
{
    if(!active || eventSerialNum <= 0)
    {
       throw InvalidCommandUseException();
    }
    string shiftStr = args.PopFirstIfNotEmpty();
    args.ThrowIfNotEmpty();
    TimeSpan shift(0);
    if(shiftStr != "")
    {
        shift = TimeSpan(shiftStr);
    }
    shared_ptr<Event> splitted = active->SplitShift(shift, eventSerialNum, loggedin);
    loggedin->AddEvent(splitted);
    shared_ptr<Event> original = active->GetStart() < splitted->GetStart() ? active : splitted;
    active = active->GetStart() > splitted->GetStart() ? active : splitted;
    eventSerialNum = 0;
    original->AddMissingParticipants(active);
}
void CommandLine::HandleEventChangeName(Arguments & args)
{
    if(!active)
    {
       throw InvalidCommandUseException();
    }
    string name = args.PopFirst();
    args.ThrowIfNotEmpty();
    active->SetName(name);
}
void CommandLine::HandleEventChangePlace(Arguments & args)
{
    if(!active)
    {
       throw InvalidCommandUseException();
    }
    string place = args.PopFirst();
    args.ThrowIfNotEmpty();
    active->SetPlace(place);
}
void CommandLine::HandleParticipantAdd(Arguments & args)
{
    if(!active)
    {
       throw InvalidCommandUseException();
    }
    string name = args.PopFirst();
    args.ThrowIfNotEmpty();
    users.AddNewPerson(name); //create one if it doesn"t exist
    shared_ptr<Person> p = users.GetPerson(name);
    bool added = active->AddPerson(p);
    if(added)
    {
        p->AddEvent(active);
    }
    else
    {
        *output << "That user has already joined this event" << endl;
    }
}
void CommandLine::HandleParticipantRemove(Arguments & args)
{
    if(!active)
    {
       throw InvalidCommandUseException();
    }
    string name = args.PopFirst();
    args.ThrowIfNotEmpty();
    bool removed = active->RemovePerson(name);
    if(removed)
    {
        shared_ptr<Person> p = users.GetPerson(name);
        p->RemoveEvent(active);
    }
    else
    {
        *output << "This user isn't participating this event" << endl;
    }
}
void CommandLine::HandleEventDismiss(Arguments & args)
{
    if(!active)
    {
       throw InvalidCommandUseException();
    }
    args.ThrowIfNotEmpty();
    active->RemoveAllParticipants(active);
    active = nullptr;
}
void CommandLine::HandleEventShow(Arguments & args)
{
    if(!active)
    {
       throw InvalidCommandUseException();
    }
    args.ThrowIfNotEmpty();
    active->Print(*output);
    *output << endl;
    active->PrintParticipants(*output);
}
void CommandLine::HandleFindingFreeTime(Arguments & args)
{
    if(!loggedin)
    {
        throw InvalidCommandUseException();
    }
    string dateStr = args.PopFirst();
    string durationStr = args.PopFirst();
    args.ThrowIfNotEmpty();
    DateTime date(dateStr);
    TimeSpan duration(durationStr);
    if(duration.GetDuration() <= 0)
    {
        throw InvalidArgumentException(durationStr, 2);
    }
    DateTime closest = loggedin->FindClosestAvailableTime(date, duration);
    *output << "The closest available time is ";
    closest.Print(*output);
    *output << endl;
}
void CommandLine::HandleHelp(Arguments & args)
{
    string cmd = args.PopFirstIfNotEmpty();
    args.ThrowIfNotEmpty();
    if(cmd == "")
    {
        vector<pair<string, string>> commands;
        for(const pair<string, pair<CommandLine::HandleCmd, string>> & c : cmdTranslation)
        {
            commands.push_back(make_pair(c.first, c.second.second));
        }
        sort(commands.begin(), commands.end());
        for(const pair<string,string> p : commands)
        {
            *output << p.first << " - " << p.second << endl;
        }
        return;
    }
    try
    {
        *output << cmdTranslation.at(cmd).second << endl;
    }
    catch(const out_of_range & e)
    {
        *output << "Unknown command" << endl;
    }
}
void CommandLine::HandleExport(Arguments & args)
{
    if(!loggedin)
    {
        throw InvalidCommandUseException();
    }
    string fileName = args.PopFirst();
    args.ThrowIfNotEmpty();
    if(fileName.find_first_of(FILE_RESERVED_PREFIX) == 0)
    {
        *output << "File start with " + FILE_RESERVED_PREFIX + " is reserved for auto export" << endl;
    }
    if(!loggedin->ExportEvents(fileName))
    {
        *output << "Event exporting was not successful." << endl;
    }
}
void CommandLine::HandleImport(Arguments & args)
{
    if(!loggedin)
    {
        throw InvalidCommandUseException();
    }
    string fileName = args.PopFirst();
    args.ThrowIfNotEmpty();

    if(!Import(fileName))
    {
        *output << "Import failed ensure yourself that file exists and it is in healthy state" << endl;
    }
    displaying = nullptr;
}

bool LoadNames(set<string> & result)
{
    ifstream names;
    names.open(FILE_PATH + NAMES_FILE);
    string name;
    getline(names, name);
    while(!names.eof() && !names.fail())
    {
        result.insert(name);
        getline(names, name);
    }
    names.close();
    return names.eof();
}

void CommandLine::ExportAll() const
{
    if(!_AskYesOrNo(*output, *input, "Do you want to export all?", true))
    {
        return;
    }
    set<string> names;
    for(const pair<string, shared_ptr<Person>> & p : users.GetUsers())
    {
        if(!p.second->ExportEvents(FILE_RESERVED_PREFIX + p.second->GetName()))
        {
            *output << "Save after closing failed" << endl;
            return;
        }
        names.insert(p.second->GetName());
    }

    ofstream file;
    file.open(FILE_PATH + NAMES_FILE);
    for(const string & name : names)
    {
        file << name << endl;
        if(file.fail())
        {
            *output << "Save after closing failed" << endl;
            return;
        }
    }
    file.close();
}

void CommandLine::ImportAll()
{
    if(_AskYesOrNo(*output, *input, "Do you want to import automatically?", true))
    {
        set<string> names;
        if(!LoadNames(names))
        {
            *output << "Failed to load names - no events imported" << endl;
            return;
        }
        for(const string & name : names)
        {
            users.AddNewPerson(name);
            loggedin = users.GetPerson(name);
            if(!Import(FILE_RESERVED_PREFIX + name))
            {
                *output << "Failed to load event file " + FILE_RESERVED_PREFIX + name << endl;
            }
            loggedin = nullptr;
        }
    }
}
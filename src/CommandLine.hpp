#ifndef CommandLine_aae7dbabe47147b2823d68a9d5db8869
#define CommandLine_aae7dbabe47147b2823d68a9d5db8869

#include "Person/PersonDatabase.hpp"
#include "Calendar/Calendar.hpp"
#include "Event/Event.hpp"

#include <unordered_map>
#include <list>
#include <memory>
#include <iostream>

/**
 * @brief Gets commands from user and then returns answer
 * 
 */
class CommandLine
{
    private:
        /**
         * @brief Container for arguments of commands
         * 
         */
        class Arguments
        {
            private:
                std::list<std::string> arguments;
                int noArgs;
            public:
                Arguments();
                /**
                 * @brief Adds argument to the last position
                 * 
                 * @param argument 
                 */
                void PushBack(const std::string & argument);
                /**
                 * @brief Pops first argument and returns it
                 * 
                 * @return std::string first argument
                 * @throws InvalidNoArgumentsException - if it is empty
                 */
                std::string PopFirst();
                /**
                 * @brief Same as PopFirst but it will return empty string instead of throwing exception
                 * 
                 * @return std::string first argument or empty string
                 */
                std::string PopFirstIfNotEmpty();
                /**
                 * @brief Throws an exception if there are more arguments that they should be
                 * 
                 * @throws InvalidNoArgumentsException
                 */
                void ThrowIfNotEmpty();
        };
        PersonDatabase users;
        typedef void (CommandLine::*HandleCmd)(Arguments & args);
        /**
         * @brief Static map with command names as keys and pointer to method that will 
         *  handle that command and description of the command
         * 
         */
        static std::unordered_map<std::string, std::pair<HandleCmd,std::string>> cmdTranslation;

        /**
         * @brief Current user that is logged in (or that nobody is logged in = nullptr)
         * 
         */
        std::shared_ptr<Person> loggedin;
        /**
         * @brief Current calendar that is being displayed (or = nullptr when calendar is not selected)
         * 
         */
        std::shared_ptr<Calendar> displaying;
        /**
         * @brief Event that is being worked on (or = nullptr if there is none)
         * 
         */
        std::shared_ptr<Event> active;
        int eventSerialNum;

        std::istream * input;
        std::ostream * output;
        bool isImporting;
        bool checkingValidity;
        std::string DateTimeFormat;
        std::string TimeSpanFormat;

        /**
         * @brief Prints prefix info about the current state of CommandLine object
         * 
         * @param[out] os Here it will be printed 
         */
        void PrintPrefix(std::ostream & os) const;

        /**
         * @brief Changes input to file stream, silences the output, sets import formats
         * 
         * @param file from this will it now receiving commands
         */
        void ImportMode(std::ifstream & file);
        /**
         * @brief Changes input back to cin and output to cout and sets default formats
         * 
         */
        void EndImportMode();
        /**
         * @brief Tests whether is import file ok, then imports its events
         * 
         * @param fileName name of file from which it will import
         * @return true if import was successful
         * @return false if import failed
         */
        bool Import(const std::string & fileName);

        //methods that handles commands
        void HandleRegistration(Arguments & args);
        void HandleLogin(Arguments & args);
        void HandleLogout(Arguments & args);
        void HandleUsersShow(Arguments & args);
        void HandleEventCreation(Arguments & args);
        void HandleCalendarDisplay(Arguments & args);
        void HandleCalendarNext(Arguments & args);
        void HandleCalendarPrev(Arguments & args);
        void HandleCalendarLeave(Arguments & args);
        void HandleCalendarRefresh(Arguments & args);
        void HandleEventSearch(Arguments & args);
        void HandleEventSelect(Arguments & args);
        void HandleEventDeselect(Arguments & args);
        void HandleEventShift(Arguments & args);
        void HandleEventSplitShift(Arguments & args);
        void HandleEventChangeName(Arguments & args);
        void HandleEventChangePlace(Arguments & args);
        void HandleParticipantAdd(Arguments & args);
        void HandleParticipantRemove(Arguments & args);
        void HandleEventDismiss(Arguments & args);
        void HandleEventShow(Arguments & args);
        void HandleFindingFreeTime(Arguments & args);
        void HandleHelp(Arguments & args);
        void HandleExport(Arguments & args);
        void HandleImport(Arguments & args);
    public:
        CommandLine();

        /**
         * @brief 
         * 
         * @return true on normal use
         * @return false if checking validity and error occurs
         */
        bool HandleCommands();
        /**
         * @brief For every Person object creates file with information about his Event objects, 
         *  and creates file with names of all Person objets
         * 
         */
        void ExportAll() const;
        /**
         * @brief Imports all Event objects from Person files that has record in file with names
         * 
         */
        void ImportAll();

    friend std::string _GetCommandAndArgument(std::string command, Arguments & outArguments);
};

#endif //CommandLine_aae7dbabe47147b2823d68a9d5db8869
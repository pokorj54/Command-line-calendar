#ifndef Event_b2be9c82b0b54601b3cd1dc5e7a8c09e
#define Event_b2be9c82b0b54601b3cd1dc5e7a8c09e

#include "../Helpers/DateTime.hpp"
#include "../Person/Person.hpp"
#include "VirtualEvent.hpp"
#include "../Exceptions/InvalidUseException.hpp"
#include "EventType.hpp"

#include <iostream>
#include <map>
#include <memory>
#include <vector>
#include <fstream>

class Person;

/**
 * @brief Abstract class providing general interface for events
 * 
 */
class Event
{
    protected:
        std::string name;
        std::string place;
        DateTime start;
        TimeSpan duration;
        std::map<std::string, std::weak_ptr<Person>> participants;
    public:
        Event(const std::string & name, const std::string & place, const DateTime & start,
            const TimeSpan & duration, const std::shared_ptr<Person> & owner);
        virtual ~Event() = default;

        /**
         * @brief Prints Event object according its type
         * 
         * @param[out] os here it will be printed
         */
        virtual void Print(std::ostream & os) const = 0;
        /**
         * @brief Prints all participant of an Event object
         * 
         * @param[out] os here it will be printed
         */
        void PrintParticipants(std::ostream & os) const;

        /**
         * @brief Compares two Event objects by start, then by name and finaly by place
         * 
         * @param e Second Event object
         */
        bool operator < (const Event & e) const;
        /**
         * @brief Compares two Event objects by start, then by name and finaly by place
         * 
         * @param e Second Event object
         */
        bool operator == (const Event & e) const;

        const std::string & GetName() const;
        const std::string & GetPlace() const;
        const DateTime & GetStart() const;

        void SetName(const std::string & newName);
        void SetPlace(const std::string & newPlace);

        /**
         * @brief Adds Person object as a participant to this Event
         * 
         * @param p shared pointer of Person object
         * @return true if Person object was succesfully added 
         * @return false if Person is already participating
         */
        bool AddPerson(const std::shared_ptr<Person> & p);
        /**
         * @brief Removes Person object from participants
         * 
         * @param p name of the Person object that will be removed
         * @return true if Person object were removed
         * @return false if Person object was not participating
         */
        bool RemovePerson(const std::string & p);
        /**
         * @brief Adds all participants that are not in this Event object as participants
         * 
         * @param e Event object from which missing participants will be copied
         */
        void AddMissingParticipants(const std::shared_ptr<Event> & e);
        /**
         * @brief Removes all participant
         * 
         * @param e shared pointer to this event, so it could be send to the participants
         *  to remove it as well
         */
        void RemoveAllParticipants(const std::shared_ptr<Event> & e);

        /**
         * @brief Shifts start of this Event object by ts
         * 
         * @param ts TimeSpan that will be added to start of the Event object
         */
        void Shift(const TimeSpan & ts);

        /**
         * @brief Splits Event object starting with from and then shifts the later part
         * 
         * @param ts TimeSpan that will be added to start of the later Event object
         * @param from index of Event repetition from where it will be split and shifted
         * @param owner who is spliting these events
         * @return std::shared_ptr<Event> shared pointer to new Event object,
         *  it doesn't have to be same Type
         * @throws InvalidUseException if it is tried to split the EventObject at start or at the end
         */
        virtual std::shared_ptr<Event> SplitShift(const TimeSpan & ts, int from,
            const std::shared_ptr<Person> & owner) = 0;

        /**
         * @brief Fills output parametr with VirtualEvent objects symbolizing instances of this 
         *  Event object between given DateTimes
         * 
         * @param[out] putHere Here will be inserted VirtualEvents that represents instance of Event
         * @param from 
         * @param to 
         * @param ptr shared pointer to this Event object 
         */
        virtual void FillWithVirtualEvents(std::vector<VirtualEvent> & putHere, const DateTime & from,
             const DateTime & to, std::shared_ptr<Event> & ptr) const = 0;
        /**
         * @brief Fills output parametr with VirtualEvent objects symbolizing instances of this 
         *  Event object that contains given string
         * 
         * @param[out] putHere Here will be inserted VirtualEvents that represents instance of Event
         * @param ptr shared ptr to this Event object
         * @param search string that is searched for
         */
        void FillWithVirtualEvent(std::vector<VirtualEvent> & putHere, std::shared_ptr<Event> & ptr,
            const std::string & search = "") const;

        /**
         * @brief Exports this Event object to given ofstream
         * 
         * @param[out] file here it will be exported
         */
        void Export(std::ofstream & file) const;
        /**
         * @brief Export Event type specific info 
         * 
         * @param[out] file here it will be exported
         */
        virtual void ExportEventTypeSpecificInfo(std::ofstream & file) const = 0;
};

/**
 * @brief Compares two shared pointer accorfing to operator < between Events objects
 *  
 */
bool CompareSharedPtrEvents(const std::shared_ptr<Event> & e1, const std::shared_ptr<Event> & e2);
/**
 * @brief Compares two shared pointer accorfing to operator == between Event objects
 *  
 */
bool AreSharedPtrEventsSame(const std::shared_ptr<Event> & e1, const std::shared_ptr<Event> & e2);

#endif //Event_b2be9c82b0b54601b3cd1dc5e7a8c09e
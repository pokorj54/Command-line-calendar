#include "Event.hpp"

#include <algorithm>

using namespace std;

Event::Event(const string & name, const string & place, const DateTime & start,
    const TimeSpan & duration, const shared_ptr<Person> & owner): name(name), place(place),
    start(start), duration(duration)
{
    participants.insert(make_pair(owner->GetName(),owner)); 
}

void Event::PrintParticipants(ostream & os) const
{
    for(const pair<string, weak_ptr<Person>> & p : participants)
    {
        shared_ptr<Person> person = p.second.lock();
        person->Print(os);
        os << endl;
    }
}

bool Event::operator < (const Event & e) const
{
    if(start != e.start)
    {
        return start < e.start;
    }
    else if(name != e.name)
    {
        return name < e.name;
    }
    return place < e.place;
}
bool Event::operator == (const Event & e) const
{
    return !(e < *this) && !(*this < e);
}

const string & Event::GetName() const
{
    return name;
}
const string & Event::GetPlace() const
{
    return place;
}
const DateTime & Event::GetStart() const
{
    return start;
}

void Event::SetName(const string & newName)
{
    name = newName;
}
void Event::SetPlace(const string & newPlace)
{
    place = newPlace;
}

bool Event::AddPerson(const shared_ptr<Person> & p)
{
    if(participants.count(p->GetName()) > 0)
    {
        return false;
    }
    participants.insert(make_pair(p->GetName(), p));
    return true;
}
bool Event::RemovePerson(const string & p)
{
    if(participants.count(p) > 0)
    {
        participants.erase(p);
        return true;
    }
    return false;
}
void Event::AddMissingParticipants(const shared_ptr<Event> & e)
{
    e->participants = this->participants;
    for(const pair<string, weak_ptr<Person>> & p : e->participants)
    {
        shared_ptr<Person> person = p.second.lock();
        person->AddEvent(e);
    }
}
void Event::RemoveAllParticipants(const std::shared_ptr<Event> & e)
{
    for(const pair<string, weak_ptr<Person>> & p : e->participants)
    {
        shared_ptr<Person> person = p.second.lock();
        person->RemoveEvent(e);
    }
    participants.clear();
}
void Event::Shift(const TimeSpan & ts)
{
    start = start + ts;
}

void Event::FillWithVirtualEvent(vector<VirtualEvent> & putHere, shared_ptr<Event> & ptr,
    const string & search) const
{
    string lowName = name;
    string lowPlace = place;
    transform(lowName.begin(), lowName.end(), lowName.begin(), ::tolower);
    transform(lowPlace.begin(), lowPlace.end(), lowPlace.begin(), ::tolower);
    if(lowName.find(search) != string::npos || lowPlace.find(search) != string::npos)
    {
        putHere.push_back(VirtualEvent(start, start + duration,  ptr, NO_START_SELECTED));
    }
}

void Event::Export(ofstream & file) const
{
    file << CMD_CREATE << " ";
    start.Print(file, IE_DATETIME_FORMAT);
    file << " ";
    duration.Print(file, IE_TIMESPAN_FORMAT);
    file << " \"" << name << "\" \"" << place << "\"" << endl;
    ExportEventTypeSpecificInfo(file);
    for(const pair<string, weak_ptr<Person>> & p : participants)
    {
        shared_ptr<Person> person = p.second.lock();
        file << CMD_ADD << " \"" << person->GetName() << "\"" << endl; 
    }
} 

bool CompareSharedPtrEvents(const shared_ptr<Event> & e1, const shared_ptr<Event> & e2)
{
    return *e1 < *e2;
}
bool AreSharedPtrEventsSame(const shared_ptr<Event> & e1, const shared_ptr<Event> & e2)
{
    return *e1 == *e2;
}
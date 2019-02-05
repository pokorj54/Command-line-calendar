#include "EventContainer.hpp"

#include <algorithm>
#include <fstream>

using namespace std;

bool EventContainer::Add(const shared_ptr<Event> & event)
{
    if(events.empty())
    {
        events.push_back(event);
        return true; 
    }
    vector<shared_ptr<Event>>::iterator it;
    it = lower_bound(events.begin(), events.end(), event, CompareSharedPtrEvents);
    if(it != events.end() && AreSharedPtrEventsSame(*it, event))
    {
        return false;
    }
    events.insert(it, event);
    return true;
}
void EventContainer::Remove(const shared_ptr<Event> & event)
{
    vector<shared_ptr<Event>>::iterator it;
    it = lower_bound(events.begin(), events.end(), event, CompareSharedPtrEvents);
    if(it != events.end() && AreSharedPtrEventsSame(*it, event))
    {
        events.erase(it);
    }
}

void EventContainer::FillWithVirtualEvents(vector<VirtualEvent> & putHere, const DateTime & from,
    const DateTime & to) const
{
    for(std::shared_ptr<Event> e : events)
    {
        e->FillWithVirtualEvents(putHere, from, to, e);
    }
}
void EventContainer::FillWithVirtualEvents(vector<VirtualEvent> & putHere, const string & search) const
{
    for(std::shared_ptr<Event> e : events)
    {
        e->FillWithVirtualEvent(putHere, e, search);
    }
}

DateTime EventContainer::FindClosestAvailableTime(const DateTime & dt, const TimeSpan & ts) const
{
    DateTime dtCopy = dt;
    DateTime res = dt;
    vector<VirtualEvent> instances;
    while(res >= dtCopy)
    {
        DateTime tmp = dtCopy;
        FillWithVirtualEvents(instances, tmp, dtCopy.AddDays(30));
        sort(instances.begin(), instances.end());
        for(const VirtualEvent & v : instances)
        {
            if(res <= v.GetEnd() && res + ts> v.GetStart())
            {
                res = v.GetEnd();
            }
        }
    }
    return res;
}

bool EventContainer::Export(const string & fileName) const
{
    ofstream file;
    file.open(FILE_PATH + fileName + FILE_SUFFIX);
    for(const shared_ptr<Event> & e : events)
    {
        if(file.fail())
        {
            file.close();
            return false;
        }
        e->Export(file);
        file << CMD_DESELECT << endl;
    }
    file << CMD_EXIT << endl;
    file.close();
    return !file.fail();
}
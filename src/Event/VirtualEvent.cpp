#include "VirtualEvent.hpp"

using namespace std;

VirtualEvent::VirtualEvent(const DateTime & start, const DateTime & end,
    const shared_ptr<Event> & source, int serialNumber): start(start), end(end), source(source),
    serialNumber(serialNumber)
{}


bool VirtualEvent::operator < (const VirtualEvent & v) const
{
    return this->start < v.start;
}

const DateTime & VirtualEvent::GetStart() const
{
    return start;
}
const DateTime & VirtualEvent::GetEnd() const
{
    return end;
}
shared_ptr<Event> VirtualEvent::GetSource() const
{
    return source.lock();
}
int VirtualEvent::GetSerialNumber() const
{
    return serialNumber;
}

void VirtualEvent::Print(ostream & os, bool startWithDate) const
{
    shared_ptr<Event> tmp = source.lock();
    os << tmp->GetPlace() << ": " << tmp->GetName();
    if(serialNumber >= 0)
    {
        os << "(" << serialNumber << ")";
    }
    os << ": ";
    start.Print(os, startWithDate ? DEFAULT_DATETIME_FORMAT : DEFAULT_TIME_FORMAT);
    os << " - ";
    end.Print(os, start.isSameDate(end) ? DEFAULT_TIME_FORMAT : DEFAULT_DATETIME_FORMAT);
}
void VirtualEvent::PrintSource(std::ostream & os) const
{
    source.lock()->Print(os);
}
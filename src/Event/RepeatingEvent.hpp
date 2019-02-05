#ifndef RepeatingEvent_d990ac2d48434e71bdd81c9412620e6f
#define RepeatingEvent_d990ac2d48434e71bdd81c9412620e6f

#include "Event.hpp"
#include "../Helpers/DateTime.hpp"

#include <iostream>

/**
 * @brief Abstract class that provides additional interface and united methods for repeating events
 * 
 */
class RepeatingEvent: public Event
{
    protected:
        std::size_t repeats;
        /**
         * @brief Commont part for method FillWithVirtualEvents
         * 
         * @param periode number of time intervals in which is RepeaTingEvent repetiotion measured
         * @param t time adding method that symbolizes in which time units is repeat interval defined
         */
        void _FillWithVirtualEvents(std::vector<VirtualEvent> & putHere, const DateTime & from,
            const DateTime & to, std::shared_ptr<Event> & ptr, int periode,
            DateTime::TimeAddMethod t) const;
        /**
         * @brief Commont part for method SplitShift
         * 
         * @param periode number of time intervals in which is RepeaTingEvent repetiotion measured
         * @param t time adding method that symbolizes in which time units is repeat interval defined
         */
        std::shared_ptr<Event> _SplitShift(const TimeSpan & ts, int from,
            const std::shared_ptr<Person> & owner, int periode, DateTime::TimeAddMethod t);
    public:
        RepeatingEvent(const std::string & name, const std::string & place, const DateTime & start,
            const TimeSpan & duration, const std::shared_ptr<Person> & owner, std::size_t repeats = 0);
        virtual ~RepeatingEvent() = default;

        /**
         * @brief Makes RepeatingEvent object of the same type but different information
         * 
         */
        virtual std::shared_ptr<Event> MakeSimilar(const std::string & name, const std::string & place,
            const DateTime & start, const TimeSpan & duration, const std::shared_ptr<Person> & owner,
            std::size_t repeats) const = 0;
};

#endif //RepeatingEvent_d990ac2d48434e71bdd81c9412620e6f
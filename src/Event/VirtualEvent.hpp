#ifndef VirtualEvent_e253d096f8a941668e8711211c417939
#define VirtualEvent_e253d096f8a941668e8711211c417939

#include "Event.hpp"
#include "../Helpers/DateTime.hpp"

#include <iostream>
#include <memory>

class Event;

/**
 * @brief Represent an particular instance of Event object
 * 
 */
class VirtualEvent
{
    private:
        DateTime start;
        DateTime end;
        std::weak_ptr<Event> source;
        int serialNumber;
    public:
        VirtualEvent(const DateTime & start, const DateTime & end,
            const std::shared_ptr<Event> & source, int serialNumber);

        /**
         * @brief Compares two VirtualEvent objects by start
         * 
         * @param v second VirtualEvent object
         */
        bool operator < (const VirtualEvent & v) const;

        const DateTime & GetStart() const;
        const DateTime & GetEnd() const;
        std::shared_ptr<Event> GetSource() const;
        int GetSerialNumber() const;

        /**
         * @brief Prints information about this instance 
         * 
         * @param[out] os here it will be printed
         * @param startWithDate if the displayed DatetTime shows date along with time
         */
        void Print(std::ostream & os, bool startWithDate = false) const;
        /**
         * @brief Prints source
         * 
         * @param[out] os here it will be printed
         */
        void PrintSource(std::ostream & os) const;
};

#endif //VirtualEvent_e253d096f8a941668e8711211c417939
#ifndef OneTimeEvent_18cb032c08694a0f8c627ff6d4c70b72
#define OneTimeEvent_18cb032c08694a0f8c627ff6d4c70b72

#include "Event.hpp"

/**
 * @brief Represents Event that cannnot be repeated
 * 
 */
class OneTimeEvent: public Event
{
    public:
        OneTimeEvent(const std::string & name, const std::string & place, const DateTime & start,
            const TimeSpan & duration, const std::shared_ptr<Person> & owner);


        void Print(std::ostream & os) const override;
        
        /**
         * @brief Adds VirtualEvent object instance if thi Event is happening between from and to
         * 
         * @param[out] putHere here it could be the VirtualEvent inserted
         * @param ptr pointer to this Event object
         */
        void FillWithVirtualEvents(std::vector<VirtualEvent> & putHere, const DateTime & from,
             const DateTime & to, std::shared_ptr<Event> & ptr) const override;
        
        /**
         * @brief Does not have an interpretation 
         * 
         * @pthrows InvalidUseException
         */
        std::shared_ptr<Event> SplitShift(const TimeSpan & ts, int from,
            const std::shared_ptr<Person> & owner) override;

        /**
         * @brief Exports that it is nonrepeating Event object
         * 
         * @param file here it will be exported
         */
        void ExportEventTypeSpecificInfo(std::ofstream & file) const;
};

#endif //OneTimeEvent_18cb032c08694a0f8c627ff6d4c70b72
#ifndef NDaysRepeatingEvent_f43928057f43458aa084b82d7bae5312
#define NDaysRepeatingEvent_f43928057f43458aa084b82d7bae5312

#include "RepeatingEvent.hpp"

/**
 * @brief Represents Event that repeats with periode of N days
 * 
 */
class NDaysRepeatingEvent: public RepeatingEvent
{
    private:
        int periode;
    public:
        NDaysRepeatingEvent(const std::string & name, const std::string & place,
            const DateTime & start,const TimeSpan & duration, const std::shared_ptr<Person> & owner,
            int periode, std::size_t repeats = 0);
        /**
         * @brief Creates NDaysRepeatingEvent with same periode but other parametrs can vary
         * 
         * return shared_ptr<Event> the newly created Event object
         */
        std::shared_ptr<Event> MakeSimilar(const std::string & name, const std::string & place,
            const DateTime & start, const TimeSpan & duration, const std::shared_ptr<Person> & owner,
            std::size_t repeats) const;

        void Print(std::ostream & os) const override;

        void FillWithVirtualEvents(std::vector<VirtualEvent> & putHere, const DateTime & from,
             const DateTime & to, std::shared_ptr<Event> & ptr) const override;

        /**
         * @brief Splits Event object starting with from and then shifts the later part
         *  if one of the splits ends up without repeats OneTimeEvent object will be created, 
         *  if it is the first part then this will get shifted, otherwise the newly created 
         *  Event object will be shifted
         *
         * @return std::shared_ptr<Event> Newly created Event object (OneTimeEvent or 
         *  NDaysRepeatingEvent)
         * @throws InvalidUseException if it is tried to split the EventObject at start
         */
        std::shared_ptr<Event> SplitShift(const TimeSpan & ts, int from,
            const std::shared_ptr<Person> & owner) override;

        /**
         * @brief Exports that it is NDaysRepeatingEvent and information about repeats
         * 
         * @param file here it will be exported
         */
        void ExportEventTypeSpecificInfo(std::ofstream & file) const;
};

#endif //NDaysRepeatingEvent_f43928057f43458aa084b82d7bae5312
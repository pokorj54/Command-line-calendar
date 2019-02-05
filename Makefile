#variables
PROGRAM=calendar
CL=g++
CC=g++
FLAGS=-Wall -pedantic -Wno-long-long -O0 -ggdb -std=c++11

#.PHONY x means that x isn't file
.PHONY: all compile run clean doc count vrun

#commands
all: compile doc

compile: bin/InvalidDateTimeException.o bin/InvalidDateTimeShiftException.o bin/InvalidNoArgumentsException.o bin/InvalidCommandUseException.o bin/InvalidDateTimeFormatException.o bin/InvalidTimeSpanFormatException.o bin/InvalidUseException.o bin/InvalidArgumentException.o bin/DateTime.o bin/TimeSpan.o bin/Person.o bin/PersonDatabase.o bin/Event.o bin/RepeatingEvent.o bin/OneTimeEvent.o bin/MonthyDateRepeatingEvent.o bin/NDaysRepeatingEvent.o bin/YearlyRepeatingEvent.o bin/EventType.o bin/EventContainer.o bin/VirtualEvent.o bin/CalendarType.o bin/Calendar.o bin/MonthlyCalendar.o bin/WeeklyCalendar.o bin/DailyCalendar.o bin/AllEventsCalendar.o bin/CommandLine.o bin/main.o
	$(CL) $^ -o $(PROGRAM)	

run: 
	./$(PROGRAM)

vrun:
	valgrind ./$(PROGRAM)

clean: 
	rm -rf bin doc $(PROGRAM)

doc:
	doxygen Doxyfile

count:
	wc -l src/*/*.?pp src/*.?pp

bin/%.o: src/%.cpp
	mkdir -p bin
	$(CC) $(FLAGS) -c $< -o $@

#for cpp files in folders
bin/%.o: src/*/%.cpp
	mkdir -p bin
	$(CC) $(FLAGS) -c $< -o $@

bin/AllEventsCalendar.o: src/Calendar/AllEventsCalendar.cpp src/Calendar/AllEventsCalendar.hpp src/Calendar/Calendar.hpp src/Event/Event.hpp src/Helpers/DateTime.hpp src/Helpers/TimeSpan.hpp src/Exceptions/InvalidTimeSpanFormatException.hpp src/Exceptions/Exception.hpp src/constants.hpp src/Exceptions/InvalidDateTimeException.hpp src/Exceptions/InvalidDateTimeShiftException.hpp src/Exceptions/InvalidDateTimeFormatException.hpp src/Person/Person.hpp src/Event/Event.hpp src/Event/EventContainer.hpp src/Event/Event.hpp src/Event/VirtualEvent.hpp src/Helpers/DateTime.hpp src/Event/VirtualEvent.hpp src/Exceptions/InvalidUseException.hpp src/Exceptions/Exception.hpp src/Event/EventType.hpp src/Event/OneTimeEvent.hpp src/Event/Event.hpp src/Event/EventContainer.hpp src/Helpers/DateTime.hpp src/Exceptions/InvalidUseException.hpp

bin/Calendar.o: src/Calendar/Calendar.cpp src/Calendar/Calendar.hpp src/Event/Event.hpp src/Helpers/DateTime.hpp src/Helpers/TimeSpan.hpp src/Exceptions/InvalidTimeSpanFormatException.hpp src/Exceptions/Exception.hpp src/constants.hpp src/Exceptions/InvalidDateTimeException.hpp src/Exceptions/InvalidDateTimeShiftException.hpp src/Exceptions/InvalidDateTimeFormatException.hpp src/Person/Person.hpp src/Event/Event.hpp src/Event/EventContainer.hpp src/Event/Event.hpp src/Event/VirtualEvent.hpp src/Helpers/DateTime.hpp src/Event/VirtualEvent.hpp src/Exceptions/InvalidUseException.hpp src/Exceptions/Exception.hpp src/Event/EventType.hpp src/Event/OneTimeEvent.hpp src/Event/Event.hpp src/Event/EventContainer.hpp src/Helpers/DateTime.hpp

bin/CalendarType.o: src/Calendar/CalendarType.cpp src/Calendar/CalendarType.hpp

bin/DailyCalendar.o: src/Calendar/DailyCalendar.cpp src/Calendar/DailyCalendar.hpp src/Calendar/Calendar.hpp src/Event/Event.hpp src/Helpers/DateTime.hpp src/Helpers/TimeSpan.hpp src/Exceptions/InvalidTimeSpanFormatException.hpp src/Exceptions/Exception.hpp src/constants.hpp src/Exceptions/InvalidDateTimeException.hpp src/Exceptions/InvalidDateTimeShiftException.hpp src/Exceptions/InvalidDateTimeFormatException.hpp src/Person/Person.hpp src/Event/Event.hpp src/Event/EventContainer.hpp src/Event/Event.hpp src/Event/VirtualEvent.hpp src/Helpers/DateTime.hpp src/Event/VirtualEvent.hpp src/Exceptions/InvalidUseException.hpp src/Exceptions/Exception.hpp src/Event/EventType.hpp src/Event/OneTimeEvent.hpp src/Event/Event.hpp src/Event/EventContainer.hpp src/Helpers/DateTime.hpp

bin/MonthlyCalendar.o: src/Calendar/MonthlyCalendar.cpp src/Calendar/MonthlyCalendar.hpp src/Calendar/Calendar.hpp src/Event/Event.hpp src/Helpers/DateTime.hpp src/Helpers/TimeSpan.hpp src/Exceptions/InvalidTimeSpanFormatException.hpp src/Exceptions/Exception.hpp src/constants.hpp src/Exceptions/InvalidDateTimeException.hpp src/Exceptions/InvalidDateTimeShiftException.hpp src/Exceptions/InvalidDateTimeFormatException.hpp src/Person/Person.hpp src/Event/Event.hpp src/Event/EventContainer.hpp src/Event/Event.hpp src/Event/VirtualEvent.hpp src/Helpers/DateTime.hpp src/Event/VirtualEvent.hpp src/Exceptions/InvalidUseException.hpp src/Exceptions/Exception.hpp src/Event/EventType.hpp src/Event/OneTimeEvent.hpp src/Event/Event.hpp src/Event/EventContainer.hpp src/Helpers/DateTime.hpp

bin/WeeklyCalendar.o: src/Calendar/WeeklyCalendar.cpp src/Calendar/WeeklyCalendar.hpp src/Calendar/Calendar.hpp src/Event/Event.hpp src/Helpers/DateTime.hpp src/Helpers/TimeSpan.hpp src/Exceptions/InvalidTimeSpanFormatException.hpp src/Exceptions/Exception.hpp src/constants.hpp src/Exceptions/InvalidDateTimeException.hpp src/Exceptions/InvalidDateTimeShiftException.hpp src/Exceptions/InvalidDateTimeFormatException.hpp src/Person/Person.hpp src/Event/Event.hpp src/Event/EventContainer.hpp src/Event/Event.hpp src/Event/VirtualEvent.hpp src/Helpers/DateTime.hpp src/Event/VirtualEvent.hpp src/Exceptions/InvalidUseException.hpp src/Exceptions/Exception.hpp src/Event/EventType.hpp src/Event/OneTimeEvent.hpp src/Event/Event.hpp src/Event/EventContainer.hpp src/Helpers/DateTime.hpp

bin/EventContainer.o: src/Event/EventContainer.cpp src/Event/EventContainer.hpp src/Event/Event.hpp src/Helpers/DateTime.hpp src/Helpers/TimeSpan.hpp src/Exceptions/InvalidTimeSpanFormatException.hpp src/Exceptions/Exception.hpp src/constants.hpp src/Exceptions/InvalidDateTimeException.hpp src/Exceptions/InvalidDateTimeShiftException.hpp src/Exceptions/InvalidDateTimeFormatException.hpp src/Person/Person.hpp src/Event/Event.hpp src/Event/EventContainer.hpp src/Event/VirtualEvent.hpp src/Exceptions/InvalidUseException.hpp src/Exceptions/Exception.hpp src/Event/EventType.hpp

bin/Event.o: src/Event/Event.cpp src/Event/Event.hpp src/Helpers/DateTime.hpp src/Helpers/TimeSpan.hpp src/Exceptions/InvalidTimeSpanFormatException.hpp src/Exceptions/Exception.hpp src/constants.hpp src/Exceptions/InvalidDateTimeException.hpp src/Exceptions/InvalidDateTimeShiftException.hpp src/Exceptions/InvalidDateTimeFormatException.hpp src/Person/Person.hpp src/Event/Event.hpp src/Event/EventContainer.hpp src/Event/Event.hpp src/Event/VirtualEvent.hpp src/Helpers/DateTime.hpp src/Event/VirtualEvent.hpp src/Exceptions/InvalidUseException.hpp src/Exceptions/Exception.hpp src/Event/EventType.hpp

bin/EventType.o: src/Event/EventType.cpp src/Event/EventType.hpp

bin/MonthyDateRepeatingEvent.o: src/Event/MonthyDateRepeatingEvent.cpp src/Event/MonthyDateRepeatingEvent.hpp src/Event/RepeatingEvent.hpp src/Event/Event.hpp src/Helpers/DateTime.hpp src/Helpers/TimeSpan.hpp src/Exceptions/InvalidTimeSpanFormatException.hpp src/Exceptions/Exception.hpp src/constants.hpp src/Exceptions/InvalidDateTimeException.hpp src/Exceptions/InvalidDateTimeShiftException.hpp src/Exceptions/InvalidDateTimeFormatException.hpp src/Person/Person.hpp src/Event/Event.hpp src/Event/EventContainer.hpp src/Event/Event.hpp src/Event/VirtualEvent.hpp src/Helpers/DateTime.hpp src/Event/VirtualEvent.hpp src/Exceptions/InvalidUseException.hpp src/Exceptions/Exception.hpp src/Event/EventType.hpp src/Event/OneTimeEvent.hpp

bin/NDaysRepeatingEvent.o: src/Event/NDaysRepeatingEvent.cpp src/Event/NDaysRepeatingEvent.hpp src/Event/RepeatingEvent.hpp src/Event/Event.hpp src/Helpers/DateTime.hpp src/Helpers/TimeSpan.hpp src/Exceptions/InvalidTimeSpanFormatException.hpp src/Exceptions/Exception.hpp src/constants.hpp src/Exceptions/InvalidDateTimeException.hpp src/Exceptions/InvalidDateTimeShiftException.hpp src/Exceptions/InvalidDateTimeFormatException.hpp src/Person/Person.hpp src/Event/Event.hpp src/Event/EventContainer.hpp src/Event/Event.hpp src/Event/VirtualEvent.hpp src/Helpers/DateTime.hpp src/Event/VirtualEvent.hpp src/Exceptions/InvalidUseException.hpp src/Exceptions/Exception.hpp src/Event/EventType.hpp src/Event/OneTimeEvent.hpp

bin/OneTimeEvent.o: src/Event/OneTimeEvent.cpp src/Event/OneTimeEvent.hpp src/Event/Event.hpp src/Helpers/DateTime.hpp src/Helpers/TimeSpan.hpp src/Exceptions/InvalidTimeSpanFormatException.hpp src/Exceptions/Exception.hpp src/constants.hpp src/Exceptions/InvalidDateTimeException.hpp src/Exceptions/InvalidDateTimeShiftException.hpp src/Exceptions/InvalidDateTimeFormatException.hpp src/Person/Person.hpp src/Event/Event.hpp src/Event/EventContainer.hpp src/Event/Event.hpp src/Event/VirtualEvent.hpp src/Helpers/DateTime.hpp src/Event/VirtualEvent.hpp src/Exceptions/InvalidUseException.hpp src/Exceptions/Exception.hpp src/Event/EventType.hpp

bin/RepeatingEvent.o: src/Event/RepeatingEvent.cpp src/Event/RepeatingEvent.hpp src/Event/Event.hpp src/Helpers/DateTime.hpp src/Helpers/TimeSpan.hpp src/Exceptions/InvalidTimeSpanFormatException.hpp src/Exceptions/Exception.hpp src/constants.hpp src/Exceptions/InvalidDateTimeException.hpp src/Exceptions/InvalidDateTimeShiftException.hpp src/Exceptions/InvalidDateTimeFormatException.hpp src/Person/Person.hpp src/Event/Event.hpp src/Event/EventContainer.hpp src/Event/Event.hpp src/Event/VirtualEvent.hpp src/Helpers/DateTime.hpp src/Event/VirtualEvent.hpp src/Exceptions/InvalidUseException.hpp src/Exceptions/Exception.hpp src/Event/EventType.hpp src/Event/OneTimeEvent.hpp

bin/VirtualEvent.o: src/Event/VirtualEvent.cpp src/Event/VirtualEvent.hpp src/Event/Event.hpp src/Helpers/DateTime.hpp src/Helpers/TimeSpan.hpp src/Exceptions/InvalidTimeSpanFormatException.hpp src/Exceptions/Exception.hpp src/constants.hpp src/Exceptions/InvalidDateTimeException.hpp src/Exceptions/InvalidDateTimeShiftException.hpp src/Exceptions/InvalidDateTimeFormatException.hpp src/Person/Person.hpp src/Event/Event.hpp src/Event/EventContainer.hpp src/Event/Event.hpp src/Event/VirtualEvent.hpp src/Exceptions/InvalidUseException.hpp src/Exceptions/Exception.hpp src/Event/EventType.hpp

bin/YearlyRepeatingEvent.o: src/Event/YearlyRepeatingEvent.cpp src/Event/YearlyRepeatingEvent.hpp src/Event/RepeatingEvent.hpp src/Event/Event.hpp src/Helpers/DateTime.hpp src/Helpers/TimeSpan.hpp src/Exceptions/InvalidTimeSpanFormatException.hpp src/Exceptions/Exception.hpp src/constants.hpp src/Exceptions/InvalidDateTimeException.hpp src/Exceptions/InvalidDateTimeShiftException.hpp src/Exceptions/InvalidDateTimeFormatException.hpp src/Person/Person.hpp src/Event/Event.hpp src/Event/EventContainer.hpp src/Event/Event.hpp src/Event/VirtualEvent.hpp src/Helpers/DateTime.hpp src/Event/VirtualEvent.hpp src/Exceptions/InvalidUseException.hpp src/Exceptions/Exception.hpp src/Event/EventType.hpp src/Event/OneTimeEvent.hpp

bin/InvalidArgumentException.o: src/Exceptions/InvalidArgumentException.cpp src/Exceptions/InvalidArgumentException.hpp src/Exceptions/Exception.hpp

bin/InvalidCommandUseException.o: src/Exceptions/InvalidCommandUseException.cpp src/Exceptions/InvalidCommandUseException.hpp src/Exceptions/Exception.hpp

bin/InvalidDateTimeException.o: src/Exceptions/InvalidDateTimeException.cpp src/Exceptions/InvalidDateTimeException.hpp src/Exceptions/Exception.hpp

bin/InvalidDateTimeFormatException.o: src/Exceptions/InvalidDateTimeFormatException.cpp src/Exceptions/InvalidDateTimeFormatException.hpp src/Exceptions/Exception.hpp

bin/InvalidDateTimeShiftException.o: src/Exceptions/InvalidDateTimeShiftException.cpp src/Exceptions/InvalidDateTimeShiftException.hpp src/Exceptions/Exception.hpp

bin/InvalidNoArgumentsException.o: src/Exceptions/InvalidNoArgumentsException.cpp src/Exceptions/InvalidNoArgumentsException.hpp src/Exceptions/Exception.hpp

bin/InvalidTimeSpanFormatException.o: src/Exceptions/InvalidTimeSpanFormatException.cpp src/Exceptions/InvalidTimeSpanFormatException.hpp src/Exceptions/Exception.hpp

bin/InvalidUseException.o: src/Exceptions/InvalidUseException.cpp src/Exceptions/InvalidUseException.hpp src/Exceptions/Exception.hpp

bin/DateTime.o: src/Helpers/DateTime.cpp src/Helpers/DateTime.hpp src/Helpers/TimeSpan.hpp src/Exceptions/InvalidTimeSpanFormatException.hpp src/Exceptions/Exception.hpp src/constants.hpp src/Exceptions/InvalidDateTimeException.hpp src/Exceptions/InvalidDateTimeShiftException.hpp src/Exceptions/InvalidDateTimeFormatException.hpp

bin/TimeSpan.o: src/Helpers/TimeSpan.cpp src/Helpers/TimeSpan.hpp src/Exceptions/InvalidTimeSpanFormatException.hpp src/Exceptions/Exception.hpp src/constants.hpp

bin/Person.o: src/Person/Person.cpp src/Person/Person.hpp src/Event/Event.hpp src/Helpers/DateTime.hpp src/Helpers/TimeSpan.hpp src/Exceptions/InvalidTimeSpanFormatException.hpp src/Exceptions/Exception.hpp src/constants.hpp src/Exceptions/InvalidDateTimeException.hpp src/Exceptions/InvalidDateTimeShiftException.hpp src/Exceptions/InvalidDateTimeFormatException.hpp src/Person/Person.hpp src/Event/VirtualEvent.hpp src/Event/Event.hpp src/Exceptions/InvalidUseException.hpp src/Exceptions/Exception.hpp src/Event/EventType.hpp src/Event/EventContainer.hpp src/constants.hpp src/Exceptions/InvalidDateTimeFormatException.hpp src/Exceptions/InvalidTimeSpanFormatException.hpp src/Helpers/TimeSpan.hpp

bin/PersonDatabase.o: src/Person/PersonDatabase.cpp src/Person/PersonDatabase.hpp src/Person/Person.hpp src/Event/Event.hpp src/Helpers/DateTime.hpp src/Helpers/TimeSpan.hpp src/Exceptions/InvalidTimeSpanFormatException.hpp src/Exceptions/Exception.hpp src/constants.hpp src/Exceptions/InvalidDateTimeException.hpp src/Exceptions/InvalidDateTimeShiftException.hpp src/Exceptions/InvalidDateTimeFormatException.hpp src/Person/Person.hpp src/Event/VirtualEvent.hpp src/Event/Event.hpp src/Exceptions/InvalidUseException.hpp src/Exceptions/Exception.hpp src/Event/EventType.hpp src/Event/EventContainer.hpp

bin/CommandLine.o: src/CommandLine.cpp src/CommandLine.hpp src/Person/PersonDatabase.hpp src/Person/Person.hpp src/Event/Event.hpp src/Helpers/DateTime.hpp src/Helpers/TimeSpan.hpp src/Exceptions/InvalidTimeSpanFormatException.hpp src/Exceptions/Exception.hpp src/constants.hpp src/Exceptions/InvalidDateTimeException.hpp src/Exceptions/InvalidDateTimeShiftException.hpp src/Exceptions/InvalidDateTimeFormatException.hpp src/Person/Person.hpp src/Event/VirtualEvent.hpp src/Event/Event.hpp src/Exceptions/InvalidUseException.hpp src/Exceptions/Exception.hpp src/Event/EventType.hpp src/Event/EventContainer.hpp src/Calendar/Calendar.hpp src/Event/Event.hpp src/Event/OneTimeEvent.hpp src/Event/Event.hpp src/Event/EventContainer.hpp src/Helpers/DateTime.hpp src/Event/Event.hpp src/Exceptions/InvalidNoArgumentsException.hpp src/Exceptions/Exception.hpp src/Exceptions/InvalidCommandUseException.hpp src/Exceptions/InvalidUseException.hpp src/Exceptions/InvalidArgumentException.hpp src/Event/EventType.hpp src/Calendar/CalendarType.hpp src/Person/Person.hpp src/Event/OneTimeEvent.hpp src/Event/MonthyDateRepeatingEvent.hpp src/Event/RepeatingEvent.hpp src/Event/Event.hpp src/Helpers/DateTime.hpp src/Event/NDaysRepeatingEvent.hpp src/Event/YearlyRepeatingEvent.hpp src/Calendar/DailyCalendar.hpp src/Calendar/Calendar.hpp src/Calendar/MonthlyCalendar.hpp src/Calendar/WeeklyCalendar.hpp src/Calendar/AllEventsCalendar.hpp

bin/main.o: src/main.cpp src/CommandLine.hpp src/Person/PersonDatabase.hpp src/Person/Person.hpp src/Event/Event.hpp src/Helpers/DateTime.hpp src/Helpers/TimeSpan.hpp src/Exceptions/InvalidTimeSpanFormatException.hpp src/Exceptions/Exception.hpp src/constants.hpp src/Exceptions/InvalidDateTimeException.hpp src/Exceptions/InvalidDateTimeShiftException.hpp src/Exceptions/InvalidDateTimeFormatException.hpp src/Person/Person.hpp src/Event/VirtualEvent.hpp src/Event/Event.hpp src/Exceptions/InvalidUseException.hpp src/Exceptions/Exception.hpp src/Event/EventType.hpp src/Event/EventContainer.hpp src/Calendar/Calendar.hpp src/Event/Event.hpp src/Event/OneTimeEvent.hpp src/Event/Event.hpp src/Event/EventContainer.hpp src/Helpers/DateTime.hpp src/Event/Event.hpp src/Helpers/TimeSpan.hpp src/constants.hpp

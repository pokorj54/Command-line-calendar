# Command Line Calendar

BI-PA2: Semestral work of pokorj54

### Interface
- User can communicate with the program using built command line
- Commandline will answer user with standard input
- At the verry left of the command line is a prefix symbolizing current state of the application in format: [name of loggedin user/][information about Calendar on which is being work on][particular instance of a Event which is selected]>
- User can use command which can be followed by arguments
- Arguments are defaultly separated by spaces, to include space in an argument, place " before and after the argument
- Command line can ask additional questions if it needs more information about what user want to do

### Commands
- After failed command you will be informed by short message, but don't expect confirmation message after commands that were succesfully completed
- To get list of all possible commands type command help
- If you want info about specific command type help <command>

### Start and end
- At start you will be asked if you want to import files
- If you answer possitively and import files exists then all events from initial import files will be loaded
- Now you can start typing commands
- If you wnt to end the program use command exit
- Then you will be asked if you want to export all events from the runnning program
- After you answer the program will end

### Time Formats
- %Y-%m-%dT%H:%M:%S for date and time
- %Y-%m-%d for date only
- %d:%H:%M:%S for duration
- Date and time formats work in the same way like strftime
- In duration literals can be hold any integer numbers



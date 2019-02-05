#ifndef constants_be021602387442e09ea474ec0ef02603
#define constants_be021602387442e09ea474ec0ef02603

/**
 * @brief format in which application displays and accept DateTime 
 *  it is strftime format
 */
const std::string DEFAULT_DATETIME_FORMAT = "%Y-%m-%dT%H:%M:%S";
/**
 * @brief format in which application displays and accept date only DateTime
 *  it is strftime format
 */
const std::string DEFAULT_DATE_FORMAT = "%Y-%m-%d";
/**
 * @brief format in which application displays time part of DateTime
 *  it is strftime format
 */
const std::string DEFAULT_TIME_FORMAT = "%H:%M:%S";
/**
 * @brief format in which application displays and accept TimeSpan as duration
 *  format has to be valid - TimeSpan::IsFormatValid
 */
const std::string DEFAULT_TIMESPAN_FORMAT = "%d:%H:%M:%S";

/**
 * @brief Day in which weeks start - 0 = Sunday
 * 
 */
const int DEFAULT_WEEK_START = 1;

/**
 * @brief DateTime format that is used for import and export
 * 
 */
const std::string IE_DATETIME_FORMAT = "%Y-%m-%dT%H:%M:%S";
/**
 * @brief TimeSpan format that is used for import and export
 * 
 */
const std::string IE_TIMESPAN_FORMAT = "%d:%H:%M:%S";

//VirtualEvent constants for serialNum
const int NOT_SERIABLE = -1;
const int NO_START_SELECTED = -2;

//file constants for import and export
const std::string FILE_PATH = "./examples/";
const std::string FILE_SUFFIX = ".calendar"; 
const std::string FILE_RESERVED_PREFIX = "_"; 
const std::string NAMES_FILE = "names"; 

//Command that are exported
const std::string CMD_CREATE = "create";
const std::string CMD_ADD = "add";
const std::string CMD_DESELECT = "deselect";
const std::string CMD_LOGOUT = "logout";
const std::string CMD_EXIT = "exit";

const char CHAR_YES = 'y';
const char CHAR_NO = 'n';

const std::string BLUE_COLOR = "\x1B[34m";
const std::string WHITE_COLOR = "\x1B[0m";


#endif //constants_be021602387442e09ea474ec0ef02603
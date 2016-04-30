#ifndef DATETIME_H_INLCUDE
#define DATETIME_H_INLCUDE

#include "mql4-def.h"
#include "mql4-data.h"

//TimeCurrent
//Returns the last known server time (time of the last quote receipt) in the datetime format
//TimeLocal
//Returns the local computer time in datetime format
//TimeGMT
//Returns GMT in datetime format with the Daylight Saving Time by local time of the computer, where the client terminal is running
//TimeDaylightSavings
//Returns the sign of Daylight Saving Time switch
//TimeGMTOffset
//Returns the current difference between GMT time and the local computer time in seconds, taking into account DST switch
//TimeToStruct
//Converts a datetime value into a variable of MqlDateTime structure type
//StructToTime
//Converts a variable of MqlDateTime structure type into a datetime value
//Day
//Returns the current day of the month, i.e., the day of month of the last known server time
//DayOfWeek
//Returns the current zero-based day of the week of the last known server time
//DayOfYear
//Returns the current day of the year i.e., the day of year of the last known server time
//Hour
//Returns the hour of the last known server time by the moment of the program start
//Minute
//Returns the current minute of the last known server time by the moment of the program start
//Month
//Returns the current month as number, i.e., the number of month of the last known server time
//Seconds
//Returns the amount of seconds elapsed from the beginning of the current minute of the last known server time by the moment of the program start
//TimeDay
//Returns the day of month of the specified date
//TimeDayOfWeek
//Returns the zero-based day of week of the specified date
//TimeDayOfYear
//Returns the day of year of the specified date
//TimeHour
//Returns the hour of the specified time
//TimeMinute
//Returns the minute of the specified time
//TimeMonth
//Returns the month number of the specified time
//TimeSeconds
//Returns the amount of seconds elapsed from the beginning of the minute of the specified time
//TimeYear
//Returns year of the specified date
//Year
//Returns the current year, i.e., the year of the last known server time

namespace MQL4 {

/**
 * @brief TimeCurrent Returns the last known server time, time of the last quote receipt for one of the symbols selected in the "Market Watch" window. In the OnTick() handler, this function returns the time of the received handled tick. In other cases (for example, call in handlers OnInit(), OnDeinit(), OnTimer() and so on) this is the time of the last quote receipt for any symbol available in the "Market Watch" window, the time shown in the title of this window. The time value is formed on a trade server and does not depend on the time settings on your computer. There are 2 variants of the function.
 * @return Value of datetime type
 */
extern datetime  TimeCurrent();


/**
 * @brief TimeCurrent Returns the last known server time, time of the last quote receipt for one of the symbols selected in the "Market Watch" window. In the OnTick() handler, this function returns the time of the received handled tick. In other cases (for example, call in handlers OnInit(), OnDeinit(), OnTimer() and so on) this is the time of the last quote receipt for any symbol available in the "Market Watch" window, the time shown in the title of this window. The time value is formed on a trade server and does not depend on the time settings on your computer. There are 2 variants of the function.
 * @param dt_struct
 * [out] MqlDateTime structure type variable.
 * Note
 * If the MqlDateTime structure type variable has been passed as a parameter, it is filled accordingly.
 * To arrange high-resolution counters and timers, use the GetTickCount() function, which produces values in milliseconds.
 * During testing in the Strategy Tester, TimeCurrent() is simulated according to historical data.
 * @return Value of datetime type
 */
extern datetime  TimeCurrent( MqlDateTime&  dt_struct );




/**
 * @brief StringToTime The function converts a string containing time or date in "yyyy.mm.dd [hh:mi]" format into datetime type.
 * @param value [in]  String in " yyyy.mm.dd hh:mi " format.
 * @return Value of datetime type containing total number of seconds that elapsed since 01.01.1970.
 */
extern datetime  StringToTime(
   const string&  value      // date string
);

/**
 * @brief StringToTime The function converts a string containing time or date in "yyyy.mm.dd[ |,][hh:mi]" format into datetime type.
 * @param value [in]  String in "yyyy.mm.dd[ |,]hh:mi" format.
 * @return Value of datetime type containing total number of seconds that elapsed since 01.01.1970.
 */
extern datetime  StringToTime(
   const char* value      // date string
);

/**
 * @brief StringToTime The function converts a string containing time or date in "yyyy.mm.dd[ |,][hh:mi]" format into datetime type.
 * @param value [in]  String in "yyyy.mm.dd[ |,]hh:mi" format.
 * @return Value of datetime type containing total number of seconds that elapsed since 01.01.1970.
 */
extern datetime  StringToTime(
   const string&  value      // date string
);

/**
 * @brief ForexStringToTime converts a string to datetime
 * @param value, string in "yyyy.mm.dd,hh:mi"
 * @return value of datetime
 */
extern datetime ForexStringToTime(const string &value);
extern datetime ForexStringToTime(const char* value);

} //namespace MQL4

#endif // DATETIME_H_INLCUDE


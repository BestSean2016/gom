#include <cstring>
#include "datetime.h"

namespace MQL4 {

datetime TimeCurrent()
{
    return time(0);
}

datetime TimeCurrent( MqlDateTime& dt_struct )
{
    time_t t = time(0);
    struct tm* lt = localtime(&t);
    dt_struct.day = lt->tm_mday,
        dt_struct.day_of_week = lt->tm_wday,
        dt_struct.day_of_year = lt->tm_yday,
        dt_struct.hour = lt->tm_hour,
        dt_struct.min = lt->tm_min,
        dt_struct.mon = lt->tm_mon + 1,
        dt_struct.sec = lt->tm_sec,
        dt_struct.year = lt->tm_year + 1900;

    return t;
}


datetime  StringToTime(const string& value) {
    return StringToTime(value.c_str());
}

datetime  StringToTime(const char* value) {
    (void)value;
    return (0);
}

//forex
//date,      time, open,   high,   low,    close,  volume
//2016.04.08,16:22,108.600,108.601,108.551,108.555,86
//
datetime ForexStringToTime(const string& value) {
    return ForexStringToTime(value.c_str());
}

datetime ForexStringToTime(const char* value) {
    char* str = (char*)value;
    struct tm lt;
    memset(&lt, 0, sizeof(lt));
    lt.tm_year = atoi(str) - 1900;
    str += 5;   //str = strchr(str, '.') + 1;
    lt.tm_mon = atoi(str) - 1;
    str += 3;   //str = strchr(str, '.') + 1;
    lt.tm_mday = atoi(str);
    str += 3;   //str = strchr(str, ',') + 1;
    lt.tm_hour = atoi(str);
    str += 3;   //str = strchr(str, ':') + 1;
    lt.tm_min = atoi(str);
    return mktime(&lt);
}

} //namespace MQL4

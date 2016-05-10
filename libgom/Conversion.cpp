#include "Conversion.h"

namespace MQL4 {

string  DoubleToStr(
   double  value,     // value
   int     digits     // precision
   )
{
    (void)value;
    (void)digits;

    char buf[64];
    snprintf(buf, 64, "%f", value);
    return buf;
}


string  IntegerToString(
   long    number,            // number
   int     str_len,           // length of result string
   ushort  fill_symbol        // filler
   ) {
    (void)str_len;
    (void)fill_symbol;

    char buf[64];
    snprintf(buf, 64, "%ld", number);
    return buf;
}


//Rounding floating point number to a specified accuracy.
double NormalizeDouble(double value, int digits) {
    (void)digits;
    return value;
}

} //namespace MQL4

#include "Conversion.h"

namespace MQL4 {

string  DoubleToStr(
   double  value,     // value
   int     digits     // precision
   )
{
    char buf[64];
    snprintf(buf, 64, "%f", value);
    return buf;
}


string  IntegerToString(
   long    number,            // number
   int     str_len,           // length of result string
   ushort  fill_symbol        // filler
   ) {
    char buf[64];
    snprintf(buf, 64, "%ld", number);
    return buf;
}


//Rounding floating point number to a specified accuracy.
double NormalizeDouble(double value, int digits) {
    return value;
}

} //namespace MQL4

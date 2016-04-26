#ifndef CONVERSION_H
#define CONVERSION_H


#include <string>
using namespace std;

namespace MQL4 {

/**
 * @brief DoubleToStr Returns text string with the specified numerical value converted into a specified
 *        precision format.
 * @param value [in]  Floating point value.
 * @param digits [in]  Precision format, number of digits after decimal point (0-8).
 * @return Text string.
 */
extern string  DoubleToStr(
   double  value,     // value
   int     digits     // precision
   );



/**
 * @brief IntegerToString
 * This function converts value of integer type into a string of a specified length and returns the obtained string.
 * @param number [in]  Number for conversion.
 * @param str_len
 * [in]  String length. If the resulting string length is larger than the specified one, the string is not cut off. If it is smaller, filler symbols will be added to the left.
 * @param fill_symbol
 * [in]  Filler symbol. By default it is a space.
 * @return
 */
extern string  IntegerToString(
   long    number,              // number
   int     str_len=0,           // length of result string
   ushort  fill_symbol=' '      // filler
   );



/**
 * @brief NormalizeDouble
 * Rounding floating point number to a specified accuracy.
 * Note, Calculated values of StopLoss, TakeProfit, and values of open prices for pending orders must be normalized
 * with the accuracy, the value of which can be obtained by Digits().
 * Please note that when output to Journal using the Print() function, a normalized number may contain a greater number
 * of decimal places than you expect.
 * @param value [in] Value with a floating point.
 * @param digits [in]  Accuracy format, number of digits after point (0-8).
 * @return Value of double type with preset accuracy.
 */
extern double  NormalizeDouble(
   double  value,      // normalized number
   int     digits      // number of digits after decimal point
   );



/*
    CharToString
    CharArrayToString
    ColorToARGB
    ColorToString
    DoubleToString
    EnumToString
    IntegerToString
    ShortToString
    ShortArrayToString
    TimeToString
    NormalizeDouble
    StringToCharArray
    StringToColor
    StringToDouble
    StringToInteger
    StringToShortArray
    StringToTime
    StringFormat
    CharToStr
    DoubleToStr
    StrToDouble
    StrToInteger
    StrToTime
    TimeToStr
*/


} //namespace MQL4
#endif // CONVERSION_H

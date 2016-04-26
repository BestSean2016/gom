//+------------------------------------------------------------------+
//|                                                       stdlib.h |
//|                      Copyright S 2004, MetaQuotes Software Corp. |
//|                                       http://www.metaquotes.net/ |
//+------------------------------------------------------------------+
// #import "stdlib.ex4"
#ifndef STD_LIB_MQL4_H_INCLUDE
#define STD_LIB_MQL4_H_INCLUDE

#include "mql4-def.h"


#include "Math.h"
//#include "String.h"
#include "Conversion.h"
#include "string-ops.h"
#include "Tradeing.h"
#include "Checkup.h"
#include "AccountInfo.h"

namespace MQL4 {

extern string ErrorDescription(int error_code);
extern int    RGB(int red_value,int green_value,int blue_value);
extern bool   CompareDoubles(double number1,double number2);
extern string DoubleToStrMorePrecision(double number,int precision);
extern string IntegerToHexString(int integer_number);

extern void   Print(const char* s);
extern void   Print(const char* s, double v);

} //namespace MQL4

#endif //STD_LIB_MQL4_H_INCLUDE

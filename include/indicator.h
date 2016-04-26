#ifndef INDICATOR_H
#define INDICATOR_H
#include <string>

using namespace std;

namespace MQL4 {

/**
 * @brief iBars Returns the number of bars on the specified chart.
 * Note
 * For the current chart, the information about the amount of bars is in the Bars predefined variable.
 * Example:
 *   Print("Bar count on the 'EURUSD,H1' is ",iBars("EURUSD",PERIOD_H1));
 * @param symbol [in]  Symbol the data of which should be used to calculate indicator. NULL means the current symbol.
 * @param timeframe [in]  Timeframe. It can be any of ENUM_TIMEFRAMES enumeration values. 0 means the current chart timeframe.
 * @return The number of bars on the specified chart.
 */
int  iBars(
   string           symbol,          // symbol
   int              timeframe        // timeframe
   );




/**
 * @brief iMA Calculates the Moving Average indicator and returns its value.
 * Example:
 *  AlligatorJawsBuffer[i]=iMA(NULL,0,13,8,MODE_SMMA,PRICE_MEDIAN,i);
 *
 * @param symbol [in]  Symbol name on the data of which the indicator will be calculated. NULL means the current symbol.
 * @param timeframe [in]  Timeframe. It can be any of ENUM_TIMEFRAMES enumeration values. 0 means the current chart timeframe.
 * @param ma_period [in]  Averaging period for calculation.
 * @param ma_shift [in]  MA shift. Indicators line offset relate to the chart by timeframe.
 * @param ma_method [in]  Moving Average method. It can be any of ENUM_MA_METHOD enumeration values.
 * @param applied_price [in]  Applied price. It can be any of ENUM_APPLIED_PRICE enumeration values.
 * @param shift [in]  Index of the value taken from the indicator buffer (shift relative to the current bar the given amount of periods ago).
 * @return Numerical value of the Moving Average indicator.
 */
double  iMA(
   string          symbol,           // symbol
   ENUM_TIMEFRAMES timeframe,        // timeframe
   int             ma_period,        // MA averaging period
   int             ma_shift,         // MA shift
   int             ma_method,        // averaging method
   int             applied_price,    // applied price
   int             shift             // shift
   );


} //namespace MQL4








#endif // INDICATOR_H


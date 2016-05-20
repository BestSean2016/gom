#ifndef INDICATOR_H
#define INDICATOR_H
#include <string>
#include "mql4-def.h"

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
extern int  iBars(const char *     symbol,          // symbol
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
extern double  iMA(const char *symbol,           // symbol
                   int timeframe,        // timeframe
                   int             ma_period,        // MA averaging period
                   int             ma_shift,         // MA shift
                   int             ma_method,        // averaging method
                   int             applied_price,    // applied price
                   int             shift             // shift
                   );


/**
 * @brief iMACD Calculates the Moving Averages Convergence/Divergence indicator and returns its value.
 * Note
 * In some systems it is called MACD Histogram and plotted as two lines. In MetaTrader 4 client terminal MACD is plotted as histogram.
 * Example:
 *   if(iMACD(NULL,0,12,26,9,PRICE_CLOSE,MODE_MAIN,0)>iMACD(NULL,0,12,26,9,PRICE_CLOSE,MODE_SIGNAL,0)) return(0);
 *
 * @param symbol [in]  Symbol name on the data of which the indicator will be calculated. NULL means the current symbol.
 * @param timeframe [in]  Timeframe. It can be any of ENUM_TIMEFRAMES enumeration values. 0 means the current chart timeframe.
 * @param fast_ema_period [in]  Fast EMA averaging period.
 * @param slow_ema_period [in]  Slow EMA averaging period.
 * @param signal_period [in]  Signal line averaging period.
 * @param applied_price [in]  Applied price. It can be any of ENUM_APPLIED_PRICE enumeration values.
 * @param mode [in]  Indicator line index. It can be one of the Indicators line identifiers enumeration values (0-MODE_MAIN, 1-MODE_SIGNAL).
 * @param shift [in]  Index of the value taken from the indicator buffer (shift relative to the current bar the given amount of periods ago).
 * @return Numerical value of the Moving Average of Oscillator indicator.
 */

extern double  iMACD(const char *symbol,           // symbol
                     int          timeframe,        // timeframe
                     int          fast_ema_period,  // Fast EMA period
                     int          slow_ema_period,  // Slow EMA period
                     int          signal_period,    // Signal line period
                     int          applied_price,    // applied price
                     int          mode,             // line index
                     int          shift             // shift
                     );

extern void setCurrentDataPos(int pos);
extern void OnNewData(MqlTick& tick);

extern double Bid();
extern double Ask();


extern int gCurrentDataPos;

} //namespace MQL4








#endif // INDICATOR_H


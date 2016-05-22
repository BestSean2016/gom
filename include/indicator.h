#ifndef INDICATOR_H
#define INDICATOR_H
#include <string>
#include "mql4-def.h"
#include "mql4-data.h"

using namespace std;

namespace MQL4 {

class Indicator {
private:
    TradingDatas*     _datas;
    RatesData* _SelectedData;
    int*     _CurrentDataPos;
public:
    Indicator();
    ~Indicator();

    void setData(TradingDatas* datas, RatesData* SelectedData, int* CurrentDataPos) {
        _datas = datas;
        _SelectedData   = SelectedData  ;
        _CurrentDataPos = CurrentDataPos;
    }

  /**
   * @brief iMA Calculates the Moving Average indicator and returns its value.
   * Example:
   *  AlligatorJawsBuffer[i]=iMA(NULL,0,13,8,MODE_SMMA,PRICE_MEDIAN,i);
   *
   * @param symbol [in]  Symbol name on the data of which the indicator will be
   * calculated. NULL means the current symbol.
   * @param timeframe [in]  Timeframe. It can be any of ENUM_TIMEFRAMES
   * enumeration values. 0 means the current chart timeframe.
   * @param ma_period [in]  Averaging period for calculation.
   * @param ma_shift [in]  MA shift. Indicators line offset relate to the chart
   * by timeframe.
   * @param ma_method [in]  Moving Average method. It can be any of
   * ENUM_MA_METHOD enumeration values.
   * @param applied_price [in]  Applied price. It can be any of
   * ENUM_APPLIED_PRICE enumeration values.
   * @param shift [in]  Index of the value taken from the indicator buffer
   * (shift relative to the current bar the given amount of periods ago).
   * @return Numerical value of the Moving Average indicator.
   */
  double iMA(const char *symbol, // symbol
             int timeframe,      // timeframe
             int ma_period,      // MA averaging period
             int ma_shift,       // MA shift
             int ma_method,      // averaging method
             int applied_price,  // applied price
             int shift           // shift
             );

  /**
   * @brief iMACD Calculates the Moving Averages Convergence/Divergence
   * indicator and returns its value.
   * Note
   * In some systems it is called MACD Histogram and plotted as two lines. In
   * MetaTrader 4 client terminal MACD is plotted as histogram.
   * Example:
   *   if(iMACD(NULL,0,12,26,9,PRICE_CLOSE,MODE_MAIN,0)
   *      > iMACD(NULL,0,12,26,9,PRICE_CLOSE,MODE_SIGNAL,0))
   *   return(0);
   *
   * @param symbol [in]  Symbol name on the data of which the indicator will be
   * calculated. NULL means the current symbol.
   * @param timeframe [in]  Timeframe. It can be any of ENUM_TIMEFRAMES
   * enumeration values. 0 means the current chart timeframe.
   * @param fast_ema_period [in]  Fast EMA averaging period.
   * @param slow_ema_period [in]  Slow EMA averaging period.
   * @param signal_period [in]  Signal line averaging period.
   * @param applied_price [in]  Applied price. It can be any of
   * ENUM_APPLIED_PRICE enumeration values.
   * @param mode [in]  Indicator line index. It can be one of the Indicators
   * line identifiers enumeration values (0-MODE_MAIN, 1-MODE_SIGNAL).
   * @param shift [in]  Index of the value taken from the indicator buffer
   * (shift relative to the current bar the given amount of periods ago).
   * @return Numerical value of the Moving Average of Oscillator indicator.
   */

  double iMACD(const char *symbol,  // symbol
               int timeframe,       // timeframe
               int fast_ema_period, // Fast EMA period
               int slow_ema_period, // Slow EMA period
               int signal_period,   // Signal line period
               int applied_price,   // applied price
               int mode,            // line index
               int shift            // shift
               );

};

} // namespace MQL4

#endif // INDICATOR_H

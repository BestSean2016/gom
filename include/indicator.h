#ifndef INDICATOR_H
#define INDICATOR_H
#include <string>
#include "mql4-def.h"
#include "mql4-data.h"

using namespace std;

namespace MQL4 {

typedef struct TradingDatas {
  int _Digits;       /// Number of digits after decimal point for the current symbol
                     /// prices
  double _Point;     /// Size of the current symbol point in the quote currency
  int _LastError;    /// The last error code
  int _Period;       /// Timeframe of the current chart
  int _RandomSeed;   /// Current status of the generator of pseudo-random integers
  bool _StopFlag;    /// Program stop flag
  string _Symbol;    /// Symbol name of the current chart
  int _UninitReason; /// Uninitialization reason code
  double _Ask;       /// The latest known seller's price (ask price) of the current
                     /// symbol
  int _Bars;         /// Number of bars in the current chart
  double _Bid;       /// The latest known buyer's price (offer price, bid price) of
                     /// the current symbol
  double *_Close;    /// Series array that contains close prices for each bar of
                     /// the current chart
  double *_High;     /// Series array that contains the highest prices of each bar
                     /// of the current chart
  double *_Low;      /// Series array that contains the lowest prices of each bar of
                     /// the current chart
  double *_Open;     /// Series array that contains open prices of each bar of the
                     /// current chart
  datetime *_Time;   /// Series array that contains open time of each bar of the
                     /// current chart
  double *_Volume;   /// Series array that contains tick volumes of each bar of
                     /// the current chart

  TradingDatas()
      : _Digits(0), _Point(0), _LastError(0), _Period(0), _RandomSeed(0),
        _StopFlag(0), _Symbol(""), _UninitReason(0), _Ask(0), _Bars(0), _Bid(0),
        _Close(0), _High(0), _Low(0), _Open(0), _Time(0), _Volume(0) {}
  ~TradingDatas() {
    if (_Close)  delete[] _Close;
    if (_High)   delete[] _High;
    if (_Low)    delete[] _Low;
    if (_Open)   delete[] _Open;
    if (_Time)   delete[] _Time;
    if (_Volume) delete[] _Volume;
  }
} TradingDatas;

class Indicator {
public:
    TradingDatas datas;
    string     _SelectedSymbol;
    RatesData* _SelectedData;
    int        _CurrentDataPos;

public:
    Indicator();
    ~Indicator();


  /**
   * @brief iBars Returns the number of bars on the specified chart.
   * Note
   * For the current chart, the information about the amount of bars is in the
   * Bars predefined variable.
   * Example:
   *   Print("Bar count on the 'EURUSD,H1' is ",iBars("EURUSD",PERIOD_H1));
   * @param symbol [in]  Symbol the data of which should be used to calculate
   * indicator. NULL means the current symbol.
   * @param timeframe [in]  Timeframe. It can be any of ENUM_TIMEFRAMES
   * enumeration values. 0 means the current chart timeframe.
   * @return The number of bars on the specified chart.
   */
  int iBars(const char *symbol, // symbol
            int timeframe       // timeframe
            );

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

  void setCurrentDataPos(int pos);
  void OnNewData(MqlTick &tick);

  double Bid();
  double Ask();


  string Symbol() {
    if (!_SelectedData)
      return "";
    else
      return _SelectedData->symbol.symbol_name;
  }

  double Point() {
    double v = _SelectedData->data[1].close;
    double iv, p = 1, pnt = 1;

    do {
      v *= p;
      iv = static_cast<double>(static_cast<ulong>(v));
      p *= 10;
      pnt /= 10;
    } while (fabs(v - iv) > 0.000001);

    return pnt;
  }

};

} // namespace MQL4

#endif // INDICATOR_H

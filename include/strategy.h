#ifndef STRATEGY_H
#define STRATEGY_H

#include "stderror-mql4.h"
#include "stdlib-mql4.h"

#include "mql4-def.h"
#include "mql4-data.h"
#include "libgom.h"

#include "ta-lib/ta_libc.h"
#include "indicator.h"
#include "order.h"
#include "Tradeing.h"

namespace MQL4 {

class Indicator;

class Strategy {
public:
  Strategy();
  virtual ~Strategy();

protected:
  TradingDatas datas;
  string _SelectedSymbol;
  RatesData *_SelectedData;
  int _CurrentDataPos;

public:
  Indicator indicator;
  Order order;

public:
  virtual void OnInit() {}
  virtual void OnDeinit() {}
  virtual void OnTick() {}

  void OnNewData(MqlTick &tick);
public:
  Indicator* getIndicator() { return &indicator; }
  Order* getOrder() { return &order; }  
  TradingDatas *getTradingData() { return &datas; }
  string &getSelectedSymbol() { return _SelectedSymbol; }
  RatesData *getSelectedData() { return _SelectedData; }
  int *getCurrentDataPos() { return &_CurrentDataPos; }

public:
  void setSelectedData(RatesData* rates) {
      _SelectedData = rates;
      indicator.setData(&datas, _SelectedData, &_CurrentDataPos);
      order.setData(&datas, _SelectedData, &_CurrentDataPos);
  }
  void setCurrentDataPos(int pos);

  double Bid();
  double Ask();

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

#endif // STRATEGY_H

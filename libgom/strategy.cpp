#include "strategy.h"

namespace MQL4 {

Strategy::Strategy() {}

Strategy::~Strategy() {}

void Strategy::OnNewData(MqlTick &tick) {
  _SelectedData->addNewTick(tick);
  datas._Bars = static_cast<int>(_SelectedData->data.size());
  datas._Bid = tick.bid[0];
  datas._Ask = tick.ask[0];
}

double Strategy::Bid() { return datas._Bid; }
double Strategy::Ask() { return datas._Ask; }

void Strategy::setCurrentDataPos(int pos) {
  _CurrentDataPos = pos;
  datas._Last = datas._Bid = datas._Ask = _SelectedData->data[pos].close;
  indicator.setData(&datas, _SelectedData, &_CurrentDataPos);
  order.setData(&datas, _SelectedData, &_CurrentDataPos);
}

int Strategy::iBars(const char *symbol, // symbol
                    int timeframe       // timeframe
                    ) {
  string s(symbol);
  _SelectedData = MQL4::mapRatesData.getSymbol(
      MARKET_FOREX_FURTURES, s, (MQL4::ENUM_TIMEFRAMES)timeframe);
  int result = 0;
  if (_SelectedData)
    result = static_cast<int>(_SelectedData->rs.amount);

  datas._Bars = result;
  return result;
}

} // namespace MQL4

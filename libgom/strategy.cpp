#include "strategy.h"

namespace MQL4 {

Strategy::Strategy() {
  indicator.setData(&datas, _SelectedData, &_CurrentDataPos);
  order.setData(&datas, _SelectedData, &_CurrentDataPos);
  datas.setRatesData(_SelectedData);
}

Strategy::~Strategy() {}

void Strategy::OnNewData(MqlTick &tick) {
  _SelectedData->addNewTick(tick);
  datas.Bars = static_cast<int>(_SelectedData->data.size());
  datas.Bid = tick.bid[0];
  datas.Ask = tick.ask[0];
  datas.Last = tick.last;
  _CurrentDataPos = _SelectedData->data.size() - 1;
}

double Strategy::Bid() { return datas.Bid; }
double Strategy::Ask() { return datas.Ask; }

void Strategy::setCurrentDataPos(int pos) {
  _CurrentDataPos = pos;
  datas.Bars = static_cast<int>(_SelectedData->data.size());
  datas.Bid = datas.Ask = datas.Last = _SelectedData->data[pos].close;
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

  datas.Bars = result;
  indicator.setData(&datas, _SelectedData, &_CurrentDataPos);
  order.setData(&datas, _SelectedData, &_CurrentDataPos);
  datas.setRatesData(_SelectedData);
  return result;
}

} // namespace MQL4

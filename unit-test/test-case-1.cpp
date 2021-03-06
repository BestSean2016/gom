#include "gtest/gtest.h"

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <time.h>

#include <iostream>

#include "mql4-def.h"
#include "mql4-data.h"
#include "libgom.h"

#include "ta-lib/ta_libc.h"
#include "indicator.h"
#include "Checkup.h"
#include "Tradeing.h"
#include "order.h"
#include "strategy.h"

TEST(ForexStringToTime, Convertions) {
  MQL4::datetime t1 = MQL4::ForexStringToTime(
      "2016.04.08,16:22,108.600,108.601,108.551,108.555,86");
  struct tm lt;
  memset(&lt, 0, sizeof(lt));
  lt.tm_year = 2016 - 1900;
  lt.tm_mon = 3;
  lt.tm_mday = 8;
  lt.tm_hour = 16;
  lt.tm_min = 22;
  time_t t2 = mktime(&lt);
  // std::cout << t1 << ", " << t2 << endl;
  EXPECT_EQ(t1, t2);
}

TEST(read_forex_csv, DataAdaptor) {
  MQL4::RatesData rd;
  int result =
      rd.read_forex_csv(MQL4::MARKET_FOREX_FURTURES,
                        "/home/sean/projects/quants/gom/data/USDJPY1.csv");
  EXPECT_EQ(result, 0);
  EXPECT_EQ(rd.symbol.market, MQL4::MARKET_FOREX_FURTURES);
  EXPECT_EQ(rd.symbol.symbol_name, string("USDJPY"));
  EXPECT_EQ(rd.symbol.period, MQL4::ENUM_TIMEFRAMES::PERIOD_M1);
  EXPECT_EQ(rd.data.size(), (size_t)13455);

  MQL4::MqlRates r;
  memset(&r, 0, sizeof(r));

  // line 1
  r.close = 108.555, r.high = 108.601, r.low = 108.551, r.open = 108.600,
  r.tick_volume = 86;
  r.time = MQL4::ForexStringToTime(
      "2016.04.08,16:22,108.600,108.601,108.551,108.555,86");
  EXPECT_EQ((rd.data[0] == r), true);

  // line 1000
  // 2016.04.11,11:01,108.134,108.139,108.123,108.130,34
  r.open = 108.134, r.high = 108.139, r.low = 108.123, r.close = 108.130,
  r.tick_volume = 34;
  r.time = MQL4::ForexStringToTime("2016.04.11,11:01");
  EXPECT_EQ((rd.data[1000 - 1] == r), true);

  // line 3000
  // 2016.04.12,20:27,108.580,108.592,108.569,108.591,35
  r.open = 108.580, r.high = 108.592, r.low = 108.569, r.close = 108.591,
  r.tick_volume = 35;
  r.time = MQL4::ForexStringToTime("2016.04.12,20:27");
  EXPECT_EQ((rd.data[3000 - 1] == r), true);

  // line 6000
  // 2016.04.14,22:43,109.378,109.396,109.377,109.395,13
  r.open = 109.378, r.high = 109.396, r.low = 109.377, r.close = 109.395,
  r.tick_volume = 13;
  r.time = MQL4::ForexStringToTime("2016.04.14,22:43");
  EXPECT_EQ((rd.data[6000 - 1] == r), true);

  // line 12000
  // 2016.04.21,05:01,109.674,109.679,109.673,109.673,17
  r.open = 109.674, r.high = 109.679, r.low = 109.673, r.close = 109.673,
  r.tick_volume = 17;
  r.time = MQL4::ForexStringToTime("2016.04.21,05:01");
  EXPECT_EQ((rd.data[12000 - 1] == r), true);

  // line 13455
  // 2016.04.22,05:18,109.452,109.452,109.444,109.445,13
  r.open = 109.452, r.high = 109.452, r.low = 109.444, r.close = 109.445,
  r.tick_volume = 13;
  r.time = MQL4::ForexStringToTime("2016.04.22,05:18");
  EXPECT_EQ((rd.data[13455 - 1] == r), true);

  MQL4::TickData td;
  rd.reates_to_tick(td);
  EXPECT_EQ(rd.data.size(), td.data.size());
  for (size_t i = 0; i < rd.data.size(); ++i)
    EXPECT_EQ((rd.data[i] == td.data[i]), true);

  rd.releaseData();
  EXPECT_EQ((rd.rs.time == 0), true);
  EXPECT_EQ(rd.data.size(), (size_t)0);
  EXPECT_EQ(rd.rs.amount, (size_t)0);
}

TEST(serialization_of_forex_rates, serialization) {
  MQL4::RatesData rd;
  int result =
      rd.read_forex_csv(MQL4::MARKET_FOREX_FURTURES,
                        "/home/sean/projects/quants/gom/data/USDJPY1.csv");
  EXPECT_EQ(result, 0);
  EXPECT_EQ(rd.symbol.market, MQL4::MARKET_FOREX_FURTURES);
  EXPECT_EQ(rd.symbol.symbol_name, string("USDJPY"));
  EXPECT_EQ(rd.symbol.period, MQL4::ENUM_TIMEFRAMES::PERIOD_M1);
  EXPECT_EQ(rd.data.size(), (size_t)13455);

  // result = MQL4::serializateRates(rd, rd.data.size());
  // EXPECT_EQ(result == 0);
  EXPECT_EQ(rd.rs.size, rd.data.size() * 2);
  EXPECT_EQ(rd.rs.amount, rd.data.size());

  for (size_t i = 0; i < rd.data.size(); ++i) {
    bool t =
        (rd.data[i].open == rd.rs.open[i] &&
         rd.data[i].close == rd.rs.close[i] &&
         rd.data[i].open == rd.rs.open[i] && rd.data[i].high == rd.rs.high[i] &&
         rd.data[i].low == rd.rs.low[i] && rd.data[i].time == rd.rs.time[i] &&
         rd.data[i].tick_volume == rd.rs.tick_volume[i]);
    EXPECT_EQ(t, true);
  }

  rd.releaseData();
  EXPECT_EQ((rd.rs.time == 0), true);
  EXPECT_EQ(rd.data.size(), (size_t)0);
  EXPECT_EQ(rd.rs.amount, (size_t)0);
}

TEST(get_forex_data_from_path, get_forex_data) {
  int result =
      MQL4::mapRatesData.get_forex_data("/home/sean/projects/quants/gom/data");
  EXPECT_EQ(result, 0);

  std::string symbol_name("USDJPY");
  MQL4::RatesData *rd = MQL4::mapRatesData.getSymbol(
      MQL4::MARKET_FOREX_FURTURES, symbol_name, MQL4::PERIOD_M1);
  EXPECT_NE((void*)rd, (void*)0);
  EXPECT_EQ(rd->symbol.market, MQL4::MARKET_FOREX_FURTURES);
  EXPECT_EQ(rd->symbol.symbol_name, string("USDJPY"));
  EXPECT_EQ(rd->symbol.period, MQL4::ENUM_TIMEFRAMES::PERIOD_M1);
  EXPECT_EQ(rd->data.size(), (size_t)13455);

  EXPECT_EQ(MQL4::mapRatesData.size(), (size_t)8);
  MQL4::mapRatesData.releaseRatesFromMap();
  EXPECT_EQ(MQL4::mapRatesData.size(), (size_t)0);
}

TEST(TA_MA, test_ta_lib_for_ma) {
  int result =
      MQL4::mapRatesData.get_forex_data("/home/sean/projects/quants/gom/data");
  EXPECT_EQ(result, 0);

  std::string symbol_name("USDJPY");
  MQL4::RatesData *rd = MQL4::mapRatesData.getSymbol(
      MQL4::MARKET_FOREX_FURTURES, symbol_name, MQL4::PERIOD_M1);
  EXPECT_NE((void*)rd, (void*)0);

  double *outTrimaReal = new double[rd->rs.size * 4];
  double *outSmaReal = outTrimaReal + rd->rs.size;
  double *outEmaReal = outSmaReal + rd->rs.size;
  double *outWmaReal = outEmaReal + rd->rs.size;

  int outBegIdx, outNBElement;
  int period = 60;
  TA_RetCode code = TA_MA(
      0, (int)rd->rs.amount - 1, rd->rs.close, period, /* From 1 to 100000 */
      TA_MAType_TRIMA, &outBegIdx, &outNBElement, outTrimaReal);

  EXPECT_EQ(code, 0);
  EXPECT_EQ(outBegIdx, period - 1);
  EXPECT_EQ(outNBElement, (int)rd->rs.amount - outBegIdx);

  code = TA_MA(0, (int)rd->rs.amount - 1, rd->rs.close,
               period, /* From 1 to 100000 */
               TA_MAType_SMA, &outBegIdx, &outNBElement, outSmaReal);

  EXPECT_EQ(code, 0);
  EXPECT_EQ(outBegIdx, period - 1);
  EXPECT_EQ(outNBElement, (int)rd->rs.amount - outBegIdx);

  code = TA_MA(0, (int)rd->rs.amount - 1, rd->rs.close,
               period, /* From 1 to 100000 */
               TA_MAType_EMA, &outBegIdx, &outNBElement, outEmaReal);

  EXPECT_EQ(code, 0);
  EXPECT_EQ(outBegIdx, period - 1);
  EXPECT_EQ(outNBElement, (int)rd->rs.amount - outBegIdx);

  code = TA_MA(0, (int)rd->rs.amount - 1, rd->rs.close,
               period, /* From 1 to 100000 */
               TA_MAType_WMA, &outBegIdx, &outNBElement, outWmaReal);

  EXPECT_EQ(code, 0);
  EXPECT_EQ(outBegIdx, period - 1);
  EXPECT_EQ(outNBElement, (int)rd->rs.amount - outBegIdx);

  ofstream fout("test-ma.csv");
  fout << "Close Price, TRIma, Sma, Ema, Wma\n";
  for (int i = 0; i < outNBElement; ++i) {
    if (i < outBegIdx)
      fout << rd->rs.close[i] << ", "
           << ", "
           << ", "
           << ", " << endl;
    else
      fout << rd->rs.close[i] << ", " << outTrimaReal[i] << ", "
           << outSmaReal[i] << ", " << outEmaReal[i] << ", " << outWmaReal[i]
           << ", " << endl;
  }
  fout.close();

  delete[] outTrimaReal;
  MQL4::mapRatesData.releaseRatesFromMap();
}

TEST(TA_MACD, test_ta_lib_for_macd) {
  int result =
      MQL4::mapRatesData.get_forex_data("/home/sean/projects/quants/gom/data");
  EXPECT_EQ(result, 0);

  std::string symbol_name("USDJPY");
  MQL4::RatesData *rd = MQL4::mapRatesData.getSymbol(
      MQL4::MARKET_FOREX_FURTURES, symbol_name, MQL4::PERIOD_M1);
  EXPECT_NE((void*)rd, (void*)0);

  double *outMACD_1 = new double[rd->rs.size * 3];
  double *outMACDSignal_1 = outMACD_1 + rd->rs.size;
  double *outMACDHist_1 = outMACD_1 + rd->rs.size * 2;

  int outBegIdx, outNBElement;
  int period = 1;
  int fastPeriod = 20; /* From 2 to 100000 */
  int slowPeriod = 40; /* From 2 to 100000 */

  TA_RetCode code = TA_MACD(0, (int)rd->rs.amount - 1, rd->rs.close, fastPeriod,
                            slowPeriod, period, /* From 1 to 100000 */
                            &outBegIdx, &outNBElement, outMACD_1,
                            outMACDSignal_1, outMACDHist_1);

  EXPECT_EQ(code, 0);
  EXPECT_EQ(outBegIdx, slowPeriod - 2);
  EXPECT_EQ(outNBElement, (int)rd->rs.amount - outBegIdx - 2);

  ofstream fout("test-macd.csv");
  fout << "Close Price, macd, signal, hist, macd_, signal_, hist_\n";
  for (int i = 0; i < outNBElement; ++i) {
    if (i < outBegIdx)
      fout << rd->rs.close[i] << ", "
           << ", "
           << ", " << endl;
    else
      fout << rd->rs.close[i] << ", " << outMACD_1[i] << ", "
           << outMACDSignal_1[i] << ", " << outMACDHist_1[i] << endl;
  }
  fout.close();

  delete[] outMACD_1;
  MQL4::mapRatesData.releaseRatesFromMap();
}

TEST(ORDER, test_order) {
  /*string   symbol,            // symbol
  int      cmd,                 // operation
  double   volume,              // volume
  double   price,               // price
  int      slippage,            // slippage
  double   stoploss,            // stop loss
  double   takeprofit,          // take profit
  string   comment=NULL,        // comment
  int      magic=0,             // magic number
  datetime expiration=0,        // pending order expiration
  color    arrow_color=clrNONE  // color*/
  MQL4::Order order;

  int ticket =
      order.OrderSend("USDJPY", MQL4::ORDER_BUY, 41, 12.3, 1, 9.0, 18.0);

  EXPECT_EQ(order._Orders.size(), (size_t)1);
  MQL4::MqlTradeRequest *order_request = order.findInOrderMap(ticket);

  EXPECT_EQ(order_request->type, MQL4::ORDER_BUY);
  EXPECT_EQ(order_request->price, 12.3);
  EXPECT_EQ(order_request->sl, 9.0);
  EXPECT_EQ(order_request->tp, 18.0);
  EXPECT_EQ(order_request->symbol, "USDJPY");
  EXPECT_EQ(order_request->volume, 41);
  EXPECT_EQ(order_request->deviation, (unsigned long)1);
  EXPECT_EQ(order_request->status, MQL4::ENUM_ORDER_STATUS_OPENED);

  EXPECT_EQ(order.OrderSelect(0, MQL4::SELECT_BY_POS), true);
  EXPECT_EQ(order_request, order._SelectedOrder);

  EXPECT_EQ(order.OrderModify(ticket, 12.8, 8.0, 20.0, 0, clrNONE), true);
  EXPECT_EQ(order_request->type, MQL4::ORDER_BUY);
  EXPECT_EQ(order_request->price, 12.8);
  EXPECT_EQ(order_request->sl, 8.0);
  EXPECT_EQ(order_request->tp, 20.0);
  EXPECT_EQ(order_request->symbol, "USDJPY");
  EXPECT_EQ(order_request->volume, 41);
  EXPECT_EQ(order_request->deviation, (unsigned long)1);
  EXPECT_EQ(order_request->status, MQL4::ENUM_ORDER_STATUS_MODIFIED);

  EXPECT_EQ(order.OrderClose(ticket, 20, 14.8, 1, clrNONE), true);
  EXPECT_EQ(order_request->type, MQL4::ORDER_BUY);
  EXPECT_EQ(order_request->price, 12.8);
  EXPECT_EQ(order_request->sl, 8.0);
  EXPECT_EQ(order_request->tp, 20.0);
  EXPECT_EQ(order_request->symbol, "USDJPY");
  EXPECT_EQ(order_request->volume, 41);
  EXPECT_EQ(order_request->deviation, (unsigned long)1);
  EXPECT_EQ(order_request->status, MQL4::ENUM_ORDER_STATUS_CLOSED);

  EXPECT_EQ(order._Orders.size(), (size_t)0);
  EXPECT_EQ(order._HistoryOrders.size(), (size_t)2);
  EXPECT_EQ(order.OrdersTotal(), 0);
  EXPECT_EQ(order.HistoryTotal(), 1);

  EXPECT_EQ(order.OrderSelect(1, MQL4::SELECT_BY_POS), false);
  EXPECT_EQ((order._SelectedOrder == NULL), true);

  order_request = order._SelectedOrder;
}

TEST(Indicator, test_indicator) {
  int result =
      MQL4::mapRatesData.get_forex_data("/home/sean/projects/quants/gom/data");
  EXPECT_EQ(result, 0);

  MQL4::Strategy strategy;
  MQL4::Indicator* indicator = strategy.getIndicator();
  int Bars_ = strategy.iBars("USDJPY", MQL4::PERIOD_M1);
  EXPECT_EQ((strategy.getSelectedData() != 0), true);
  EXPECT_EQ(Bars_, 13455);

  strategy.setCurrentDataPos(Bars_ - 1);

  double MacdCurrent =
      indicator->iMACD(NULL, 0, 12, 26, 9, MQL4::PRICE_CLOSE, MODE_MAIN, 0);
  double MacdPrevious =
      indicator->iMACD(NULL, 0, 12, 26, 9, MQL4::PRICE_CLOSE, MODE_MAIN, 1);
  double SignalCurrent =
      indicator->iMACD(NULL, 0, 12, 26, 9, MQL4::PRICE_CLOSE, MODE_SIGNAL, 0);
  double SignalPrevious =
      indicator->iMACD(NULL, 0, 12, 26, 9, MQL4::PRICE_CLOSE, MODE_SIGNAL, 1);
  double MaCurrent =
      indicator->iMA(NULL, MQL4::PERIOD_M1, 26, 0, MQL4::MODE_EMA, MQL4::PRICE_CLOSE, 0);
  double MaPrevious =
      indicator->iMA(NULL, MQL4::PERIOD_M1, 26, 0, MQL4::MODE_EMA, MQL4::PRICE_CLOSE, 1);

  EXPECT_LT(abs(MacdCurrent - (0.000828180)), 0.00000001);
  EXPECT_LT(abs(MacdPrevious - (0.000801993)), 0.00000001);
  EXPECT_LT(abs(SignalCurrent - (0.001153298)), 0.00000001);
  EXPECT_LT(abs(SignalPrevious - (0.001234578)), 0.00000001);
  EXPECT_LT(abs(MaCurrent - (109.448948062)), 0.00000001);
  EXPECT_LT(abs(MaPrevious - (109.449263907)), 0.00000001);

  EXPECT_EQ(strategy.getSelectedData()->rs.statPrice.count,
            static_cast<size_t>(13455));
  EXPECT_LT(abs(strategy.getSelectedData()->rs.statPrice.mean - (108.913630546)),
            0.00000001);
  EXPECT_LT(abs(strategy.getSelectedData()->rs.statPrice.stdv - (0.563896570)),
            0.00000001);
  EXPECT_LT(abs(strategy.getSelectedData()->rs.statPrice.var - (0.317979342)),
            0.00000001);
  EXPECT_LT(abs(strategy.getSelectedData()->rs.statPrice.max - (109.886000000)),
            0.00000001);
  EXPECT_LT(abs(strategy.getSelectedData()->rs.statPrice.min - (107.665000000)),
            0.00000001);

  EXPECT_EQ(strategy.getSelectedData()->rs.statVolume.count,
            static_cast<size_t>(13455));
  EXPECT_LT(abs(strategy.getSelectedData()->rs.statVolume.mean - (35.5331103679)),
            0.00000001);
  EXPECT_LT(abs(strategy.getSelectedData()->rs.statVolume.stdv - (20.9486637760)),
            0.00000001);
  EXPECT_LT(abs(strategy.getSelectedData()->rs.statVolume.var - (438.8465139982)),
            0.00000001);
  EXPECT_LT(abs(strategy.getSelectedData()->rs.statVolume.max - (158.0000000000)),
            0.00000001);
  EXPECT_LT(abs(strategy.getSelectedData()->rs.statVolume.min - (1.0000000000)),
            0.00000001);

  EXPECT_EQ(strategy.getSelectedData()->rs.statPriceDelta.count,
            static_cast<size_t>(13455));
  EXPECT_LT(abs(strategy.getSelectedData()->rs.statPriceDelta.mean - (0.0000661513)),
            0.00000001);
  EXPECT_LT(abs(strategy.getSelectedData()->rs.statPriceDelta.stdv - (0.0171723960)),
            0.00000001);
  EXPECT_LT(abs(strategy.getSelectedData()->rs.statPriceDelta.var - (0.0002948912)),
            0.00000001);
  EXPECT_LT(abs(strategy.getSelectedData()->rs.statPriceDelta.max - (0.1120000000)),
            0.00000001);
  EXPECT_LT(abs(strategy.getSelectedData()->rs.statPriceDelta.min - (-0.4760000000)),
            0.00000001);

  EXPECT_EQ(strategy.getSelectedData()->rs.statVolumeDelta.count,
            static_cast<size_t>(13455));
  EXPECT_LT(abs(strategy.getSelectedData()->rs.statVolumeDelta.mean - (-0.0054258956)),
            0.00000001);
  EXPECT_LT(abs(strategy.getSelectedData()->rs.statVolumeDelta.stdv - (14.6253761723)),
            0.00000001);
  EXPECT_LT(abs(strategy.getSelectedData()->rs.statVolumeDelta.var - (213.9016281803)),
            0.00000001);
  EXPECT_LT(abs(strategy.getSelectedData()->rs.statVolumeDelta.max - (86.0000000000)),
            0.00000001);
  EXPECT_LT(abs(strategy.getSelectedData()->rs.statVolumeDelta.min - (-76.0000000000)),
            0.00000001);

  MQL4::TickVector ticks;
  int NEW_TICK_NUMBER = 10000 * 60;

  //srand(54321);
  //result = MQL4::forex_simulator_new_data(ticks, strategy.getSelectedData(), NEW_TICK_NUMBER, MQL4::ENUM_TIMEFRAMES::PERIOD_M1);
  //MQL4::TickVector2Csv(ticks, "ticks-54321.csv");
  //ticks.clear();
  //
  //
  //srand(33333);
  //result = MQL4::forex_simulator_new_data(ticks, strategy.getSelectedData(), NEW_TICK_NUMBER, MQL4::ENUM_TIMEFRAMES::PERIOD_M1);
  //MQL4::TickVector2Csv(ticks, "ticks-33333.csv");
  //ticks.clear();

  srand(12345);
  result = MQL4::forex_simulator_new_data(ticks, strategy.getSelectedData(), NEW_TICK_NUMBER, MQL4::ENUM_TIMEFRAMES::PERIOD_M1);
  //MQL4::TickVector2Csv(ticks, "ticks.csv");



  FILE *fstream = NULL;
  char buff[1024];

  //{
  //    fstream = popen("diff ticks.csv /home/sean/projects/quants/gom/unit-test/ticks-banchmark.csv","r");
  //    EXPECT_NE(fstream, (FILE*)NULL);
  //
  //    memset(buff,0,sizeof(buff));
  //    char* ptr = fgets(buff, sizeof(buff), fstream);
  //    EXPECT_EQ(ptr, (char*)NULL);
  //
  //    pclose(fstream);
  //}

  double p = strategy.Point();
  EXPECT_EQ(p, 0.001);

  for (int i = 0; i < NEW_TICK_NUMBER; i++)
    strategy.OnNewData(ticks[i]);

  MQL4::releaseTickVector(ticks);

  {
    strategy.getSelectedData()->ratesToCSV("rates.csv");

    fstream = popen("diff rates.csv /home/sean/projects/quants/gom/unit-test/rates-banchmark.csv","r");
    EXPECT_NE(fstream, (FILE*)NULL);

    memset(buff,0,sizeof(buff));
    char* ptr = fgets(buff, sizeof(buff), fstream);
    EXPECT_EQ(ptr, (char*)NULL);

    pclose(fstream);
  }

  MQL4::mapRatesData.releaseRatesFromMap();
}

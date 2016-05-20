//+------------------------------------------------------------------+
//|                                                  MACD Sample.mq4 |
//|                   Copyright 2005-2014, MetaQuotes Software Corp. |
//|                                              http://www.mql4.com |
//+------------------------------------------------------------------+
#include "stderror-mql4.h"
#include "stdlib-mql4.h"

#include "mql4-def.h"
#include "mql4-data.h"
#include "libgom.h"

#include "ta-lib/ta_libc.h"
#include "Tradeing.h"

#include "indicator.h"

#define copyright "2005-2014, MetaQuotes Software Corp."
#define link "http://www.mql4.com"

static double TakeProfit = 50;
static double Lots = 0.1;
static double TrailingStop = 30;
static double MACDOpenLevel = 3;
static double MACDCloseLevel = 2;
static int MATrendPeriod = 26;

using namespace MQL4;

void OnInit(void) {
  srand(time(0));
  MQL4::mapRatesData.get_forex_data("/home/sean/projects/quants/gom/data");
}

void OnDeinit(void) {
  MQL4::mapRatesData.releaseRatesFromMap();
  MQL4::destroyOrders();
}

void OnNewData(MqlTick &tick) {
  gSelectedData->addNewTick(tick);
  _Bars = static_cast<int>(MQL4::gSelectedData->data.size());
  _Bid = tick.bid[0];
  _Ask = tick.ask[0];
}

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void OnTick(void) {
  double MacdCurrent, MacdPrevious;
  double SignalCurrent, SignalPrevious;
  double MaCurrent, MaPrevious;
  int cnt, ticket, total;

  //---
  // initial data checks
  // it is important to make sure that the expert works with a normal
  // chart and the user did not make any mistakes setting external
  // variables (Lots, StopLoss, TakeProfit,
  // TrailingStop) in our case, we check TakeProfit
  // on a chart of less than 100 bars
  //---
  if (_Bars < 100) {
    Print("bars less than 100");
    return;
  }

  if (TakeProfit < 10) {
    Print("TakeProfit less than 10");
    return;
  }

  //--- to simplify the coding and speed up access data are put into internal
  // variables
  MacdCurrent = iMACD(NULL, 0, 12, 26, 9, PRICE_CLOSE, MODE_MAIN, 0);
  MacdPrevious = iMACD(NULL, 0, 12, 26, 9, PRICE_CLOSE, MODE_MAIN, 1);
  SignalCurrent = iMACD(NULL, 0, 12, 26, 9, PRICE_CLOSE, MODE_SIGNAL, 0);
  SignalPrevious = iMACD(NULL, 0, 12, 26, 9, PRICE_CLOSE, MODE_SIGNAL, 1);
  MaCurrent =
      iMA(NULL, PERIOD_CURRENT, MATrendPeriod, 0, MODE_EMA, PRICE_CLOSE, 0);
  MaPrevious =
      iMA(NULL, PERIOD_CURRENT, MATrendPeriod, 0, MODE_EMA, PRICE_CLOSE, 1);

  //cout << (MacdCurrent < 0) << ", " << (MacdCurrent > SignalCurrent) << ", "
  //     << (MacdPrevious < SignalPrevious) << ", "
  //     << (MathAbs(MacdCurrent) > (MACDOpenLevel * _Point)) << ", "
  //     << MathAbs(MacdCurrent) << ", " << (MACDOpenLevel * _Point) << ", "
  //     << (MaCurrent > MaPrevious) << endl;

  total = OrdersTotal();
  if (total < 1) {
    //--- no opened orders identified
    if (AccountFreeMargin() < (1000 * Lots)) {
      Print("We have no money. Free Margin = ", AccountFreeMargin());
      return;
    }

    //--- check for long position (BUY) possibility
    if (MacdCurrent < 0 && MacdCurrent > SignalCurrent &&
        MacdPrevious < SignalPrevious &&
        MathAbs(MacdCurrent) > (MACDOpenLevel * _Point) &&
        MaCurrent > MaPrevious) {

      ticket =
          OrderSend(Symbol(), OP_BUY, Lots, _Ask, 3, 0,
                    _Ask + TakeProfit * _Point, "macd sample", 16384, 0, Green);
      if (ticket > 0) {
        if (OrderSelect(ticket, SELECT_BY_TICKET, MODE_TRADES))
          Print("BUY order opened : ", OrderOpenPrice());
      } else
        Print("Error opening BUY order : ", GetLastError());

      return;
    }

    //--- check for short position (SELL) possibility
    if (MacdCurrent > 0 && MacdCurrent < SignalCurrent &&
        MacdPrevious > SignalPrevious &&
        MacdCurrent > (MACDOpenLevel * _Point) && MaCurrent < MaPrevious) {

      ticket =
          OrderSend(Symbol(), OP_SELL, Lots, _Bid, 3, 0,
                    _Bid - TakeProfit * _Point, "macd sample", 16384, 0, Red);
      if (ticket > 0) {
        if (OrderSelect(ticket, SELECT_BY_TICKET, MODE_TRADES))
          //Print("SELL order opened : ", OrderOpenPrice());
          printf("SELL order opened : %d, %.03f\n", gCurrentDataPos, OrderOpenPrice());
      } else
        Print("Error opening SELL order : ", GetLastError());
    }

    //--- exit from the "no opened orders" block
    return;
  }

  //--- it is important to enter the market correctly, but it is more important
  // to exit it correctly...
  for (cnt = 0; cnt < total; ++cnt) {
    if (!OrderSelect(cnt, SELECT_BY_POS, MODE_TRADES)) continue;

    if (OrderType() <= OP_SELL &&   // check for opened position
        OrderSymbol() == Symbol())  // check for symbol
    {
      //--- long position is opened
      if (OrderType() == OP_BUY) {
        //--- should it be closed?
        if (MacdCurrent > 0 && MacdCurrent < SignalCurrent &&
            MacdPrevious > SignalPrevious &&
            MacdCurrent > (MACDCloseLevel * _Point)) {
          //--- close order and exit
          if (!OrderClose(OrderTicket(), OrderLots(), _Bid, 3, Violet))
            Print("OrderClose error ", GetLastError());
          return;
        }
        //--- check for trailing stop
        if (TrailingStop > 0) {
          if (_Bid - OrderOpenPrice() > _Point * TrailingStop) {
            if (OrderStopLoss() < _Bid - _Point * TrailingStop) {
              //--- modify order and exit
              if (!OrderModify(OrderTicket(), OrderOpenPrice(),
                               _Bid - _Point * TrailingStop, OrderTakeProfit(),
                               0, Green))
                Print("OrderModify error ", GetLastError());
              return;
            }
          }
        }
      } else {  // go to short position
        //--- should it be closed?
        if (MacdCurrent < 0 && MacdCurrent > SignalCurrent &&
            MacdPrevious < SignalPrevious &&
            MathAbs(MacdCurrent) > (MACDCloseLevel * _Point)) {
          //--- close order and exit
          if (!OrderClose(OrderTicket(), OrderLots(), _Ask, 3, Violet))
            Print("OrderClose error ", GetLastError());
          return;
        }

        //--- check for trailing stop
        if (TrailingStop > 0) {
          if ((OrderOpenPrice() - _Ask) > (_Point * TrailingStop)) {
            if ((OrderStopLoss() > (_Ask + _Point * TrailingStop)) ||
                (OrderStopLoss() == 0)) {
              //--- modify order and exit
              if (!OrderModify(OrderTicket(), OrderOpenPrice(),
                               _Ask + _Point * TrailingStop, OrderTakeProfit(),
                               0, Red))
                Print("OrderModify error ", GetLastError());
              return;
            }
          }
        }

        //printf("%.03f\n", _Bid - OrderOpenPrice());
      }
    }
  }
  //---
}
//+------------------------------------------------------------------+

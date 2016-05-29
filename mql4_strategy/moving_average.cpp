#include "moving_average.h"

using namespace std;

#define copyright "2005-2014, MetaQuotes Software Corp."
#define link "http://www.mql4.com"
#define description "Moving Average sample expert advisor"

#define MAGICMA 20131111

namespace MQL4 {

//--- Inputs
static double Lots = 0.1;
static double MaximumRisk = 0.02;
static double DecreaseFactor = 3;
static int MovingPeriod = 12;
static int MovingShift = 6;
//+------------------------------------------------------------------+
//| Calculate open positions                                         |
//+------------------------------------------------------------------+
int MovingAverage::CalculateCurrentOrders(string symbol) {
  (void)symbol;
  int buys = 0, sells = 0;
  //---
  for (int i = 0; i < order.OrdersTotal(); i++) {
    if (order.OrderSelect(i, SELECT_BY_POS, MODE_TRADES) == false) break;
    if (order.OrderSymbol() == Symbol() && order.OrderMagicNumber() == MAGICMA) {
      if (order.OrderType() == OP_BUY) buys++;
      if (order.OrderType() == OP_SELL) sells++;
    }
  }
  //--- return orders volume
  if (buys > 0)
    return (buys);
  else
    return (-sells);
}
//+------------------------------------------------------------------+
//| Calculate optimal lot size                                       |
//+------------------------------------------------------------------+
double MovingAverage::LotsOptimized() {
  double lot = Lots;
  int orders = order.HistoryTotal();  // history orders total
  int losses = 0;               // number of losses orders without a break
                                //--- select lot size
  lot = NormalizeDouble(AccountFreeMargin() * MaximumRisk / 1000.0, 1);
  //--- calcuulate number of losses orders without a break
  if (DecreaseFactor > 0) {
    for (int i = orders - 1; i >= 0; i--) {
      if (order.OrderSelect(i, SELECT_BY_POS, MODE_HISTORY) == false) {
        Print("Error in history!");
        break;
      }
      if (order.OrderSymbol() != Symbol() || order.OrderType() > OP_SELL) continue;
      //---
      if (order.OrderProfit() > 0) break;
      if (order.OrderProfit() < 0) losses++;
    }
    if (losses > 1)
      lot = NormalizeDouble(lot - lot * losses / DecreaseFactor, 1);
  }
  //--- return lot size
  if (lot < 0.1) lot = 0.1;
  return (lot);
}
//+------------------------------------------------------------------+
//| Check for open order conditions                                  |
//+------------------------------------------------------------------+
void MovingAverage::CheckForOpen() {
  double ma;
  //int res;
  //--- go trading only for first tiks of new bar
  ////if (datas.Volume(0) > 1) return;
  //--- get Moving Average
  ma = indicator.iMA(NULL, 0, MovingPeriod, MovingShift, MODE_SMA, PRICE_CLOSE, 0);
  //--- sell conditions
  if (datas.Open(1) > ma && datas.Close(1) < ma) {
    //res =
      order.OrderSend(Symbol(), OP_SELL, LotsOptimized(), datas.Bid, 3, 0, 0, "",
                    MAGICMA, 0, Red);
    return;
  }
  //--- buy conditions
  if (datas.Open(1) < ma && datas.Close(1) > ma) {
    //res =
      order.OrderSend(Symbol(), OP_BUY, LotsOptimized(), datas.Ask, 3, 0, 0, "",
                    MAGICMA, 0, Blue);
    return;
  }
  //---
}
//+------------------------------------------------------------------+
//| Check for close order conditions                                 |
//+------------------------------------------------------------------+
void MovingAverage::CheckForClose() {
  double ma;
  //--- go trading only for first tiks of new bar
  ////if (datas.Volume(0) > 1) return;
  //--- get Moving Average
  ma = indicator.iMA(NULL, 0, MovingPeriod, MovingShift, MODE_SMA, PRICE_CLOSE, 0);
  //---
  for (int i = 0; i < order.OrdersTotal(); i++) {
    if (order.OrderSelect(i, SELECT_BY_POS, MODE_TRADES) == false) break;
    if (order.OrderMagicNumber() != MAGICMA || order.OrderSymbol() != Symbol()) continue;
    //--- check order type
    if (order.OrderType() == OP_BUY) {
      if (datas.Open(1) > ma && datas.Close(1) < ma) {
        if (!order.OrderClose(order.OrderTicket(), order.OrderLots(), datas.Bid, 3, White))
          Print("OrderClose error ", GetLastError());
      }
      break;
    }
    if (order.OrderType() == OP_SELL) {
      if (datas.Open(1) < ma && datas.Close(1) > ma) {
        if (!order.OrderClose(order.OrderTicket(), order.OrderLots(), datas.Ask, 3, White))
          Print("OrderClose error ", GetLastError());
      }
      break;
    }
  }
  //---
}
//+------------------------------------------------------------------+
//| OnTick function                                                  |
//+------------------------------------------------------------------+
void MovingAverage::OnTick() {
  //--- check for history and trading
  if (datas.Bars < 100 || IsTradeAllowed() == false) return;
  //--- calculate open orders by current symbol
  if (CalculateCurrentOrders(Symbol()) == 0)
    CheckForOpen();
  else
    CheckForClose();
  //---
}
//+------------------------------------------------------------------+

void MovingAverage::OnInit() {

}

void MovingAverage::OnDeinit() {
    order.closeAll();
    order.destroyOrders();
}

}//namespace MQL4

//+------------------------------------------------------------------+
//|                                               Moving Average.mq4 |
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

using namespace std;
using namespace MQL4;

#define copyright "2005-2014, MetaQuotes Software Corp."
#define link "http://www.mql4.com"
#define description "Moving Average sample expert advisor"

#define MAGICMA 20131111
//--- Inputs
static double Lots = 0.1;
static double MaximumRisk = 0.02;
static double DecreaseFactor = 3;
static int MovingPeriod = 12;
static int MovingShift = 6;
//+------------------------------------------------------------------+
//| Calculate open positions                                         |
//+------------------------------------------------------------------+
int CalculateCurrentOrders(string symbol) {
  (void)symbol;
  //int buys = 0, sells = 0;
  ////---
  //for (int i = 0; i < OrdersTotal(); i++) {
  //  if (OrderSelect(i, SELECT_BY_POS, MODE_TRADES) == false) break;
  //  if (OrderSymbol() == Symbol() && OrderMagicNumber() == MAGICMA) {
  //    if (OrderType() == OP_BUY) buys++;
  //    if (OrderType() == OP_SELL) sells++;
  //  }
  //}
  ////--- return orders volume
  //if (buys > 0)
  //  return (buys);
  //else
  //  return (-sells);
}
//+------------------------------------------------------------------+
//| Calculate optimal lot size                                       |
//+------------------------------------------------------------------+
double LotsOptimized() {
  //double lot = Lots;
  //int orders = HistoryTotal();  // history orders total
  //int losses = 0;               // number of losses orders without a break
  //                              //--- select lot size
  //lot = NormalizeDouble(AccountFreeMargin() * MaximumRisk / 1000.0, 1);
  ////--- calcuulate number of losses orders without a break
  //if (DecreaseFactor > 0) {
  //  for (int i = orders - 1; i >= 0; i--) {
  //    if (OrderSelect(i, SELECT_BY_POS, MODE_HISTORY) == false) {
  //      Print("Error in history!");
  //      break;
  //    }
  //    if (OrderSymbol() != Symbol() || OrderType() > OP_SELL) continue;
  //    //---
  //    if (OrderProfit() > 0) break;
  //    if (OrderProfit() < 0) losses++;
  //  }
  //  if (losses > 1)
  //    lot = NormalizeDouble(lot - lot * losses / DecreaseFactor, 1);
  //}
  ////--- return lot size
  //if (lot < 0.1) lot = 0.1;
  //return (lot);
  return (0);
}
//+------------------------------------------------------------------+
//| Check for open order conditions                                  |
//+------------------------------------------------------------------+
void CheckForOpen() {
  //double ma;
  ////int res;
  ////--- go trading only for first tiks of new bar
  //if (_Volume[0] > 1) return;
  ////--- get Moving Average
  //ma = iMA(NULL, 0, MovingPeriod, MovingShift, MODE_SMA, PRICE_CLOSE, 0);
  ////--- sell conditions
  //if (_Open[1] > ma && _Close[1] < ma) {
  //  //res =
  //    OrderSend(Symbol(), OP_SELL, LotsOptimized(), _Bid, 3, 0, 0, "",
  //                  MAGICMA, 0, Red);
  //  return;
  //}
  ////--- buy conditions
  //if (_Open[1] < ma && _Close[1] > ma) {
  //  //res =
  //    OrderSend(Symbol(), OP_BUY, LotsOptimized(), _Ask, 3, 0, 0, "",
  //                  MAGICMA, 0, Blue);
  //  return;
  //}
  ////---
}
//+------------------------------------------------------------------+
//| Check for close order conditions                                 |
//+------------------------------------------------------------------+
void CheckForClose() {
  //double ma;
  ////--- go trading only for first tiks of new bar
  //if (_Volume[0] > 1) return;
  ////--- get Moving Average
  //ma = iMA(NULL, 0, MovingPeriod, MovingShift, MODE_SMA, PRICE_CLOSE, 0);
  ////---
  //for (int i = 0; i < OrdersTotal(); i++) {
  //  if (OrderSelect(i, SELECT_BY_POS, MODE_TRADES) == false) break;
  //  if (OrderMagicNumber() != MAGICMA || OrderSymbol() != Symbol()) continue;
  //  //--- check order type
  //  if (OrderType() == OP_BUY) {
  //    if (_Open[1] > ma && _Close[1] < ma) {
  //      if (!OrderClose(OrderTicket(), OrderLots(), _Bid, 3, White))
  //        Print("OrderClose error ", GetLastError());
  //    }
  //    break;
  //  }
  //  if (OrderType() == OP_SELL) {
  //    if (_Open[1] < ma && _Close[1] > ma) {
  //      if (!OrderClose(OrderTicket(), OrderLots(), _Ask, 3, White))
  //        Print("OrderClose error ", GetLastError());
  //    }
  //    break;
  //  }
  //}
  ////---
}
//+------------------------------------------------------------------+
//| OnTick function                                                  |
//+------------------------------------------------------------------+
void OnTick_2() {
  ////--- check for history and trading
  //if (_Bars < 100 || IsTradeAllowed() == false) return;
  ////--- calculate open orders by current symbol
  //if (CalculateCurrentOrders(Symbol()) == 0)
  //  CheckForOpen();
  //else
  //  CheckForClose();
  ////---
}
//+------------------------------------------------------------------+
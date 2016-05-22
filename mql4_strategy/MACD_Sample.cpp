#include "macd_sample.h"


namespace MQL4 {

static double TakeProfit = 50;
static double Lots = 0.1;
static double TrailingStop = 30;
static double MACDOpenLevel = 3;
static double MACDCloseLevel = 2;
static int MATrendPeriod = 26;

void MacdSample::OnInit(void) {
  srand(time(0));
  mapRatesData.get_forex_data("/home/sean/projects/quants/gom/data");
}

void MacdSample::OnDeinit(void) {
  order.closeAll();

  order.destroyOrders();
  mapRatesData.releaseRatesFromMap();
}

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void MacdSample::OnTick(void) {
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
  if (datas._Bars < 100) {
    Print("bars less than 100");
    return;
  }

  if (TakeProfit < 10) {
    Print("TakeProfit less than 10");
    return;
  }

  //--- to simplify the coding and speed up access data are put into internal
  // variables
  MacdCurrent = indicator.iMACD(NULL, 0, 12, 26, 9, PRICE_CLOSE, MODE_MAIN, 0);
  MacdPrevious = indicator.iMACD(NULL, 0, 12, 26, 9, PRICE_CLOSE, MODE_MAIN, 1);
  SignalCurrent = indicator.iMACD(NULL, 0, 12, 26, 9, PRICE_CLOSE, MODE_SIGNAL, 0);
  SignalPrevious = indicator.iMACD(NULL, 0, 12, 26, 9, PRICE_CLOSE, MODE_SIGNAL, 1);
  MaCurrent =
      indicator.iMA(NULL, PERIOD_CURRENT, MATrendPeriod, 0, MODE_EMA, PRICE_CLOSE, 0);
  MaPrevious =
      indicator.iMA(NULL, PERIOD_CURRENT, MATrendPeriod, 0, MODE_EMA, PRICE_CLOSE, 1);

  //cout << (MacdCurrent < 0) << ", " << (MacdCurrent > SignalCurrent) << ", "
  //     << (MacdPrevious < SignalPrevious) << ", "
  //     << (MathAbs(MacdCurrent) > (MACDOpenLevel * _Point)) << ", "
  //     << MathAbs(MacdCurrent) << ", " << (MACDOpenLevel * _Point) << ", "
  //     << (MaCurrent > MaPrevious) << endl;

  total = order.OrdersTotal();
  if (total < 1) {
    //--- no opened orders identified
    if (AccountFreeMargin() < (1000 * Lots)) {
      Print("We have no money. Free Margin = ", AccountFreeMargin());
      return;
    }

    //--- check for long position (BUY) possibility
    if (MacdCurrent < 0 && MacdCurrent > SignalCurrent &&
        MacdPrevious < SignalPrevious &&
        MathAbs(MacdCurrent) > (MACDOpenLevel * datas._Point) &&
        MaCurrent > MaPrevious) {

      ticket =
          order.OrderSend(Symbol(), OP_BUY, Lots, datas._Ask, 3, 0,
                    datas._Ask + TakeProfit * datas._Point, "macd sample", 16384, 0, Green);
      if (ticket > 0) {
        if (order.OrderSelect(ticket, SELECT_BY_TICKET, MODE_TRADES))
          Print("BUY order opened : ", order.OrderOpenPrice());
      } else
        Print("Error opening BUY order : ", GetLastError());

      return;
    }

    //--- check for short position (SELL) possibility
    if (MacdCurrent > 0 && MacdCurrent < SignalCurrent &&
        MacdPrevious > SignalPrevious &&
        MacdCurrent > (MACDOpenLevel * datas._Point) && MaCurrent < MaPrevious) {

      ticket =
          order.OrderSend(Symbol(), OP_SELL, Lots, datas._Bid, 3, 0,
                    datas._Bid - TakeProfit * datas._Point, "macd sample", 16384, 0, Red);
      if (ticket > 0) {
        if (order.OrderSelect(ticket, SELECT_BY_TICKET, MODE_TRADES))
          //Print("SELL order opened : ", OrderOpenPrice());
          printf("SELL order opened : %d, %.03f\n", _CurrentDataPos, order.OrderOpenPrice());
      } else
        Print("Error opening SELL order : ", GetLastError());
    }

    //--- exit from the "no opened orders" block
    return;
  }

  //--- it is important to enter the market correctly, but it is more important
  // to exit it correctly...
  for (cnt = 0; cnt < total; ++cnt) {
    if (!order.OrderSelect(cnt, SELECT_BY_POS, MODE_TRADES)) continue;

    if (order.OrderType() <= OP_SELL &&   // check for opened position
        order.OrderSymbol() == Symbol())  // check for symbol
    {
      //--- long position is opened
      if (order.OrderType() == OP_BUY) {
        //--- should it be closed?
        if (MacdCurrent > 0 && MacdCurrent < SignalCurrent &&
            MacdPrevious > SignalPrevious &&
            MacdCurrent > (MACDCloseLevel * datas._Point)) {
          //--- close order and exit
          if (!order.OrderClose(order.OrderTicket(), order.OrderLots(), datas._Bid, 3, Violet))
            Print("OrderClose error ", GetLastError());
          return;
        }
        //--- check for trailing stop
        if (TrailingStop > 0) {
          if (datas._Bid - order.OrderOpenPrice() > datas._Point * TrailingStop) {
            if (order.OrderStopLoss() < datas._Bid - datas._Point * TrailingStop) {
              //--- modify order and exit
              if (!order.OrderModify(order.OrderTicket(), order.OrderOpenPrice(),
                               datas._Bid - datas._Point * TrailingStop, order.OrderTakeProfit(),
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
            MathAbs(MacdCurrent) > (MACDCloseLevel * datas._Point)) {
          //--- close order and exit
          if (!order.OrderClose(order.OrderTicket(), order.OrderLots(), datas._Ask, 3, Violet))
            Print("OrderClose error ", GetLastError());
          return;
        }

        //--- check for trailing stop
        if (TrailingStop > 0) {
          if ((order.OrderOpenPrice() - datas._Ask) > (datas._Point * TrailingStop)) {
            if ((order.OrderStopLoss() > (datas._Ask + datas._Point * TrailingStop)) ||
                (order.OrderStopLoss() == 0)) {
              //--- modify order and exit
              if (!order.OrderModify(order.OrderTicket(), order.OrderOpenPrice(),
                               datas._Ask + datas._Point * TrailingStop, order.OrderTakeProfit(),
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

} //namespace MQL4

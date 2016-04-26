#include "Tradeing.h"

namespace MQL4 {

int OrdersTotal() {
    return (0);
}

bool  OrderSelect(
   int     index,            // index or order ticket
   int     select,           // flag
   int     pool              // mode
)
{
    return true;
}

double  OrderOpenPrice() {
    return  (0);
}

int  OrderType() {
    return (0);
}

string  OrderSymbol() {
    return "";
}

int  OrderTicket() {
    return (0);
}

double  OrderLots() {
    return (0);
}

double  OrderStopLoss() {
    return (0);
}


bool  OrderModify(
   int        ticket,      // ticket
   double     price,       // price
   double     stoploss,    // stop loss
   double     takeprofit,  // take profit
   datetime   expiration,  // expiration
   color      arrow_color  // color
) {
    return false;
}


double  OrderTakeProfit()
{
    return (0);
}


bool  OrderClose(
   int        ticket,      // ticket
   double     lots,        // volume
   double     price,       // close price
   int        slippage,    // slippage
   color      arrow_color  // color
) {
    return (0);
}


int  OrderSend(
   string   symbol,              // symbol
   int      cmd,                 // operation
   double   volume,              // volume
   double   price,               // price
   int      slippage,            // slippage
   double   stoploss,            // stop loss
   double   takeprofit,          // take profit
   string   comment,             // comment
   int      magic,               // magic number
   datetime expiration,          // pending order expiration
   color    arrow_color          // color
   ) {
    return (0);
}


} //namespace MQL4

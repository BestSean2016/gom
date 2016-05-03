#include "Tradeing.h"
#include <memory.h>
#include <string.h>

namespace MQL4 {

VecOrders        gOrders;
MapIntToOrders   gmapOrders;
MqlTradeRequest* gSelectedOrder = 0;


static unsigned int gticket = 100000;

int OrdersTotal() {
    return static_cast<int>(gOrders.size());
}

bool  OrderSelect(
   int     index,            // index or order ticket
   int     select,           // flag
   int     pool              // mode
) {
    (void)pool;

    if (select == SELECT_BY_POS) {
        if (index < 0 || index > static_cast<int>(gOrders.size()))
            return false;
        gSelectedOrder = gOrders[index];
    } else if (select == SELECT_BY_TICKET) {
        gSelectedOrder = findInOrderMap(gmapOrders, index);
        return (gSelectedOrder != 0);
    } else
        return false;

    return true;
}

double  OrderOpenPrice() {
    if (!gSelectedOrder) return (0);
    return gSelectedOrder->price;
}

int  OrderType() {
    if (!gSelectedOrder) return (-1);
    return gSelectedOrder->type;
}

string  OrderSymbol() {
    if (!gSelectedOrder) return "";
    return gSelectedOrder->symbol;
}

int  OrderTicket() {
    if (!gSelectedOrder) return -1;
    return gSelectedOrder->order;
}

double  OrderLots() {
    if (!gSelectedOrder) return 0;
    return (0);
}

double  OrderStopLoss() {
    if (!gSelectedOrder) return 0;
    return gSelectedOrder->sl;
}


bool  OrderModify(
   int        ticket,      // ticket
   double     price,       // price
   double     stoploss,    // stop loss
   double     takeprofit,  // take profit
   datetime   expiration,  // expiration
   color      arrow_color  // color
) {
    MqlTradeRequest* mtr = findInOrderMap(gmapOrders, ticket);
    if (!mtr)
        return false;
    else {
        mtr->price = price;
        mtr->sl = stoploss;
        mtr->expiration  = expiration;
        mtr->tp = takeprofit;
        mtr->arrow_color = arrow_color;
        mtr->status = ENUM_ORDER_STATUS_MODIFIED;
        mtr->modifytime = time(0);

        return true;
    }
}


double  OrderTakeProfit()
{
    if (!gSelectedOrder) return 0;
    return gSelectedOrder->tp;
}


bool  OrderClose(
   int        ticket,      // ticket
   double     lots,        // volume
   double     price,       // close price
   int        slippage,    // slippage
   color      arrow_color  // color
) {
    MqlTradeRequest* mtr = findInOrderMap(gmapOrders, ticket);
    if (!mtr)
        return false;
    else {
        MqlTradeRequest* mtrClose = new MqlTradeRequest;
        memcpy(mtrClose, mtr, sizeof(MqlTradeRequest));
        mtrClose->order = ++gticket;
        mtrClose->magic = mtr->order;
        mtrClose->volume = lots;
        mtrClose->price = price;
        mtrClose->deviation = slippage;
        mtrClose->arrow_color = arrow_color;
        mtrClose->status = ENUM_ORDER_STATUS_CLOSED;
        mtr->modifytime = mtrClose->modifytime = mtrClose->sendtime = time(0);
        mtr->status = ENUM_ORDER_STATUS_CLOSED;

        gOrders.push_back(mtrClose);
        gmapOrders.insert(std::pair<int, MqlTradeRequest*>(mtrClose->order, mtrClose));
        return true;
    }
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
    MqlTradeRequest* mtr = new MqlTradeRequest;
    mtr->symbol = symbol;
    mtr->type = (ENUM_ORDER_TYPE)cmd;
    mtr->volume = volume;
    mtr->price = price;
    mtr->deviation = slippage;
    mtr->sl = stoploss;
    mtr->tp = takeprofit;
    mtr->comment = comment;
    mtr->magic = magic;
    mtr->expiration = expiration;
    mtr->arrow_color = arrow_color;
    mtr->order = gticket++;
    mtr->sendtime = time(0);
    mtr->modifytime = 0;
    mtr->status = ENUM_ORDER_STATUS_OPENED;

    gOrders.push_back(mtr);
    gmapOrders.insert(std::pair<int, MqlTradeRequest*>(mtr->order, mtr));

    return mtr->order;
}

void destroyOrders() {
    gmapOrders.clear();
    for (auto &p : gOrders)
        delete p;
    gOrders .clear();
}


MqlTradeRequest* findInOrderMap(MapIntToOrders &mapOrders, int ticket) {
    return mapOrders.find(ticket)->second;
}

} //namespace MQL4

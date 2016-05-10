#include "Tradeing.h"
#include <memory.h>
#include <string.h>

namespace MQL4 {

VecOrders        gOrders;
MapIntToOrders   gmapOrders;
MqlTradeRequest* gSelectedOrder = 0;
string           gSelectedSymbol = "USDJPY";
RatesData*       gSelectedData = 0;

static unsigned int gticket = 100000;


bool selectSymbol(const char* symbol, ENUM_TIMEFRAMES timeframe) {
    string the_symbol;
    if (symbol == NULL)
        the_symbol = gSelectedSymbol;
    else
        the_symbol = symbol;

    gSelectedData = mapRatesData.getSymbol(MARKET_FOREX_FURTURES, the_symbol, timeframe);
    return (gSelectedData != 0);
}

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
        if (index < 1 || index > static_cast<int>(gOrders.size()))
            return false;
        gSelectedOrder = gOrders[index - 1];
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
        mtrClose->order = ++gticket;
        mtrClose->magic = mtr->order;
        mtrClose->volume = lots;
        mtrClose->price = price;
        mtrClose->deviation = slippage;
        mtrClose->arrow_color = arrow_color;
        mtrClose->status = ENUM_ORDER_STATUS_CLOSED;
        mtr->modifytime = mtrClose->modifytime = mtrClose->sendtime = time(0);
        mtr->status = ENUM_ORDER_STATUS_CLOSED;

        mtrClose->action       = mtr->action;               /// 交易操作类型
        mtrClose->magic        = mtr->magic;                /// EA交易 ID (魔幻数字)
        mtrClose->symbol       = mtr->symbol;               /// 交易的交易品种
        mtrClose->stoplimit    = mtr->stoplimit;            /// 订单止损限价点位
        mtrClose->sl           = mtr->sl;                   /// 订单止损价位点位
        mtrClose->tp           = mtr->tp;                   /// 订单盈利价位点位
        mtrClose->type         = mtr->type;                 /// 订单类型
        mtrClose->type_filling = mtr->type_filling;         /// 订单执行类型
        mtrClose->type_time    = mtr->type_time   ;         /// 订单执行时间
        mtrClose->expiration   = mtr->expiration  ;         /// 订单终止期 (为 ORDER_TIME_SPECIFIED 类型订单)
        mtrClose->comment      = mtr->comment     ;         /// 订单注释
        mtrClose->sendtime     = mtr->sendtime    ;         /// sending time

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
    mtr->status = ENUM_ORDER_STATUS_OPENED;\
    mtr->action = TRADE_ACTION_DEAL;

    gOrders.push_back(mtr);
    gmapOrders.insert(std::pair<int, MqlTradeRequest*>(mtr->order, mtr));

    return mtr->order;
}

void destroyOrders() {
    for (auto &p : gmapOrders)
        delete (p.second);

    gmapOrders.clear();
    //for (size_t i = 0; i < gOrders.size(); ++i) {
    //    delete gOrders[i];
    //}
    gOrders .clear();
}


MqlTradeRequest* findInOrderMap(MapIntToOrders &mapOrders, int ticket) {
    return mapOrders.find(ticket)->second;
}

} //namespace MQL4

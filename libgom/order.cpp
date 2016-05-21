#include "order.h"

namespace MQL4 {

Order::Order() : _SelectedOrder(0), _gticket(10000) {}
Order::~Order() {}

int Order::OrdersTotal() {
    return static_cast<int>(_Orders.size());
}

bool  Order::OrderSelect(
   int     index,            // index or order ticket
   int     select,           // flag
   int     pool              // mode
) {
    (void)pool;

    if (select == SELECT_BY_POS) {
        if (index < 0 || index >= static_cast<int>(_Orders.size()))
            return false;
        _SelectedOrder = _Orders[index];
    } else if (select == SELECT_BY_TICKET) {
        _SelectedOrder = findInOrderMap(index);
        return (_SelectedOrder != 0);
    } else
        return false;

    return true;
}

double  Order::OrderOpenPrice() {
    if (!_SelectedOrder) return (0);
    return _SelectedOrder->price;
}

int  Order::OrderType() {
    if (!_SelectedOrder) return (-1);
    return _SelectedOrder->type;
}

string  Order::OrderSymbol() {
    if (!_SelectedOrder) return "";
    return _SelectedOrder->symbol;
}

double Order::OrderProfit() {
    if (!_SelectedOrder) return 0;
    return _SelectedOrder->tp;
}



ulong Order::OrderMagicNumber() {
    if (!_SelectedOrder) return 0;
    return _SelectedOrder->magic;
}

int Order::HistoryTotal() {
    return OrdersHistoryTotal();
}

int Order::OrdersHistoryTotal() {
    int closed = 0;
    for (auto& p : _Orders)
        if (p->status == ENUM_ORDER_STATUS_CLOSED)
            ++closed;

    return closed;
}

int  Order::OrderTicket() {
    if (!_SelectedOrder) return -1;
    return _SelectedOrder->order;
}

double  Order::OrderLots() {
    if (!_SelectedOrder) return 0;
    return (0);
}

double  Order::OrderStopLoss() {
    if (!_SelectedOrder) return 0;
    return _SelectedOrder->sl;
}


bool  Order::OrderModify(
   int        ticket,      // ticket
   double     price,       // price
   double     stoploss,    // stop loss
   double     takeprofit,  // take profit
   datetime   expiration,  // expiration
   color      arrow_color  // color
) {
    MqlTradeRequest* mtr = findInOrderMap(ticket);
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


double  Order::OrderTakeProfit()
{
    if (!_SelectedOrder) return 0;
    return _SelectedOrder->tp;
}


bool  Order::OrderClose(
   int        ticket,      // ticket
   double     lots,        // volume
   double     price,       // close price
   int        slippage,    // slippage
   color      arrow_color  // color
) {
    MqlTradeRequest* mtr = findInOrderMap(ticket);
    if (!mtr)
        return false;
    else {
        MqlTradeRequest* mtrClose = new MqlTradeRequest;
        mtrClose->order = _gticket++;
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

        _Orders.push_back(mtrClose);
        _mapOrders.insert(std::pair<int, MqlTradeRequest*>(mtrClose->order, mtrClose));
        return true;
    }
}


int  Order::OrderSend(
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
    mtr->order = _gticket++;
    mtr->sendtime = time(0);
    mtr->modifytime = 0;
    mtr->status = ENUM_ORDER_STATUS_OPENED;\
    mtr->action = TRADE_ACTION_DEAL;

    _Orders.push_back(mtr);
    _mapOrders.insert(std::pair<int, MqlTradeRequest*>(mtr->order, mtr));

    return mtr->order;
}

void Order::destroyOrders() {
    for (auto &p : _mapOrders)
        delete (p.second);

    _mapOrders.clear();
    //for (size_t i = 0; i < _Orders.size(); ++i) {
    //    delete _Orders[i];
    //}
    _Orders .clear();
}


MqlTradeRequest* Order::findInOrderMap(int ticket) {
    return _mapOrders.find(ticket)->second;
}

} //namespace MQL4


#ifndef TRADEING_H
#define TRADEING_H

#include "mql4-def.h"

//OrderClose Closes opened order
//OrderCloseBy Closes an opened order by another opposite opened order
//OrderClosePrice Returns close price of the currently selected order
//OrderCloseTime Returns close time of the currently selected order
//OrderComment Returns comment of the currently selected order
//OrderCommission Returns calculated commission of the currently selected order
//OrderDelete Deletes previously opened pending order
//OrderExpiration Returns expiration date of the selected pending order
//OrderLots Returns amount of lots of the selected order
//OrderMagicNumber Returns an identifying (magic) number of the currently selected order
//OrderModify Modification of characteristics of the previously opened or pending orders
//OrderOpenPrice Returns open price of the currently selected order
//OrderOpenTime Returns open time of the currently selected order
//OrderPrint Prints information about the selected order in the log
//OrderProfit Returns profit of the currently selected order
//OrderSelect The function selects an order for further processing
//OrderSend The main function used to open an order or place a pending order
//OrdersHistoryTotal Returns the number of closed orders in the account history loaded into the terminal
//OrderStopLoss Returns stop loss value of the currently selected order
//OrdersTotal Returns the number of market and pending orders
//OrderSwap Returns swap value of the currently selected order
//OrderSymbol Returns symbol name of the currently selected order
//OrderTakeProfit Returns take profit value of the currently selected order
//OrderTicket Returns ticket number of the currently selected order
//OrderType Returns order operation type of the currently selected order

namespace MQL4 {

/**
 * @brief OrdersTotal Returns the number of market and pending orders.
 * @return Total amount of market and pending orders.
 */
extern int  OrdersTotal();


/**
 * @brief OrderSelect The function selects an order for further processing.
 * Note
 * The pool parameter is ignored if the order is selected by the ticket number. The ticket number is a unique
 *  order identifier.
 * To find out from what list the order has been selected, its close time must be analyzed. If the order close
 * time equals to 0, the order is open or pending and taken from the terminal open orders list.
 *
 * One can distinguish an opened order from a pending order by the order type. If the order close time does not
 * equal to 0, the order is a closed order or a deleted pending order and was selected from the terminal history.
 *
 * They also differ from each other by their order types.
 * The OrderSelect() function copies order data into program environment and all further calls of OrderClosePrice(),
 * OrderCloseTime(), OrderComment(), OrderCommission(), OrderExpiration(), OrderLots(), OrderMagicNumber(),
 * OrderOpenPrice(), OrderOpenTime(), OrderPrint(), OrderProfit(), OrderStopLoss(), OrderSwap(), OrderSymbol(),
 * OrderTakeProfit(), OrderTicket(), OrderType() functions return the data, copied earlier. It means that in some
 * cases the order details (open price, SL/TP levels or expiration date) may change and the data become non-actual.
 * It is strongly recommended to call the OrderSelect() function before request the order data.
 *
 * Consecutive selection of orders using the SELECT_BY_POS parameter returns information in the sequence in which
 *  it was received from the trading server. Sorting of the resulting list of orders cannot be guaranteed.
 *
 * @param index [in]  Order index or order ticket depending on the second parameter.
 * @param select [in]  Selecting flags. It can be any of the following values:
 *                     SELECT_BY_POS - index in the order pool,
 *                     SELECT_BY_TICKET - index is order ticket.
 * @param pool [in]  Optional order pool index. Used when the selected parameter is SELECT_BY_POS. It can be
 *                   any of the following values:
 *                   MODE_TRADES (default)- order selected from trading pool(opened and pending orders),
 *                   MODE_HISTORY - order selected from history pool (closed and canceled order).
 * @return It returns true if the function succeeds, otherwise falses. To get the error information,
 *         one has to call the GetLastError() function.
 */
extern bool  OrderSelect(
   int     index,            // index or order ticket
   int     select,           // flag
   int     pool=MODE_TRADES  // mode
   );



/**
 * @brief OrderOpenPrice Returns open price of the currently selected order.
 * Note
 * The order must be previously selected by the OrderSelect() function.
 * @return Open price of the currently selected order.
 */
extern double  OrderOpenPrice();



/**
 * @brief OrderType Returns order operation type of the currently selected order.
 * Note
 * The order must be previously selected by the OrderSelect() function.
 * @return Order operation type of the currently selected order. It can be any of the following values:
 * OP_BUY - buy order,
 * OP_SELL - sell order,
 * OP_BUYLIMIT - buy limit pending order,
 * OP_BUYSTOP - buy stop pending order,
 * OP_SELLLIMIT - sell limit pending order,
 * OP_SELLSTOP - sell stop pending order.
 */
extern int  OrderType();


/**
 * @brief OrderSymbol Returns symbol name of the currently selected order.
 * Note
 * The order must be previously selected by the OrderSelect() function.
 * @return The symbol name of the currently selected order.
 */
extern string  OrderSymbol();


/**
 * @brief OrderTicket Returns ticket number of the currently selected order.
 * Note
 * The order must be previously selected by the OrderSelect() function.
 * @return Ticket number of the currently selected order.
 */
extern int  OrderTicket();




/**
 * @brief OrderLots Returns amount of lots of the selected order.
 * Note
 * The order must be previously selected by the OrderSelect() function.
 * @return Amount of lots (trade volume) of the selected order.
 */
double  OrderLots();



/**
 * @brief OrderStopLoss Returns stop loss value of the currently selected order.
 * Note
 * The order must be previously selected by the OrderSelect() function.
 * @return Stop loss value of the currently selected order.
 */
double  OrderStopLoss();





/**
 * @brief OrderModify Modification of characteristics of the previously opened or pending orders.
 * Note
 * Open price and expiration time can be changed only for pending orders. If unchanged values are passed as the function parameters, the error 1 (ERR_NO_RESULT) will be generated.
 * Pending order expiration time can be disabled in some trade servers. In this case, when a non-zero value is specified in the expiration parameter, the error 147 (ERR_TRADE_EXPIRATION_DENIED) will be generated.
 * @param ticket [in]  Unique number of the order ticket.
 * @param price [in]  New open price of the pending order.
 * @param stoploss [in]  New StopLoss level.
 * @param takeprofit [in]  New TakeProfit level.
 * @param expiration [in]  Pending order expiration time.
 * @param arrow_color [in]  Arrow color for StopLoss/TakeProfit modifications in the chart. If the parameter is missing or has CLR_NONE value, the arrows will not be shown in the chart.
 * @return If the function succeeds, it returns true, otherwise false. To get the detailed error information, call the GetLastError() function.
 */
bool  OrderModify(
   int        ticket,      // ticket
   double     price,       // price
   double     stoploss,    // stop loss
   double     takeprofit,  // take profit
   datetime   expiration,  // expiration
   color      arrow_color  // color
);




/**
 * @brief OrderTakeProfit Returns take profit value of the currently selected order.
 * Note
 * The order must be previously selected by the OrderSelect() function.
 * @return Take profit value of the currently selected order.
 */
double  OrderTakeProfit();



/**
 * @brief OrderClose Closes opened order.
 * @param ticket [in]  Unique number of the order ticket.
 * @param lots [in]  Number of lots.
 * @param price [in]  Closing price.
 * @param slippage [in]  Value of the maximum price slippage in points.
 * @param arrow_color [in]  Color of the closing arrow on the chart. If the parameter is missing or has CLR_NONE value closing arrow will not be drawn on the chart.
 * @return Returns true if successful, otherwise false. To get additional error information, one has to call the GetLastError() function.
 */
bool  OrderClose(
   int        ticket,      // ticket
   double     lots,        // volume
   double     price,       // close price
   int        slippage,    // slippage
   color      arrow_color  // color
);




/**
 * @brief OrderSend The main function used to open market or place a pending order.
 * Note
 * At opening of a market order (OP_SELL or OP_BUY), only the latest prices of Bid (for selling) or Ask (for buying) can be used as open price. If operation is performed with a security differing from the current one, the MarketInfo() function must be used with MODE_BID or MODE_ASK parameter for the latest quotes for this security to be obtained.
 * Calculated or unnormalized price cannot be applied. If there has not been the requested open price in the price thread or it has not been normalized according to the amount of digits after decimal point, the error 129 (ERR_INVALID_PRICE) will be generated. If the requested open price is fully out of date, the error 138 (ERR_REQUOTE) will be generated independently on the slippage parameter. If the requested price is out of date, but present in the thread, the order will be opened at the current price and only if the current price lies within the range of price+-slippage.
 * StopLoss and TakeProfit levels cannot be too close to the market. The minimal distance of stop levels in points can be obtained using the MarketInfo() function with MODE_STOPLEVEL parameter. In the case of erroneous or unnormalized stop levels, the error 130 (ERR_INVALID_STOPS) will be generated. A zero value of MODE_STOPLEVEL means either absence of any restrictions on the minimal distance for Stop Loss/Take Profit or the fact that a trade server utilizes some external mechanisms for dynamic level control, which cannot be translated in the client terminal. In the second case, GetLastError() can return error 130, because MODE_STOPLEVEL is actually "floating" here.
 * At placing of a pending order, the open price cannot be too close to the market. The minimal distance of the pending price from the current market one in points can be obtained using the MarketInfo() function with the MODE_STOPLEVEL parameter. In case of false open price of a pending order, the error 130 (ERR_INVALID_STOPS) will be generated.
 * Applying of pending order expiration time can be disabled in some trade servers. In this case, when a non-zero value is specified in the expiration parameter, the error 147 (ERR_TRADE_EXPIRATION_DENIED) will be generated.
 * On some trade servers, the total amount of open and pending orders can be limited. If this limit has been exceeded, no new order will be opened (or no pending order will be placed) and trade server will return error 148 (ERR_TRADE_TOO_MANY_ORDERS).
 * @param symbol [in]  Symbol for trading.
 * @param cmd [in]  Operation type. It can be any of the Trade operation enumeration.
 * @param volume [in]  Number of lots.
 * @param price [in]  Order price.
 * @param slippage [in]  Maximum price slippage for buy or sell orders.
 * @param stoploss [in]  Stop loss level.
 * @param takeprofit [in]  Take profit level.
 * @param comment [in]  Order comment text. Last part of the comment may be changed by server. default is NULL
 * @param magic [in]  Order magic number. May be used as user defined identifier. default is 0
 * @param expiration [in]  Order expiration time (for pending orders only).default is 0
 * @param arrow_color [in]  Color of the opening arrow on the chart. If parameter is missing or has CLR_NONE value opening arrow is not drawn on the chart. default is clrNONE
 * @return Returns number of the ticket assigned to the order by the trade server or -1 if it fails. To get additional error information, one has to call the GetLastError() function.
 */
int  OrderSend(
   string   symbol,              // symbol
   int      cmd,                 // operation
   double   volume,              // volume
   double   price,               // price
   int      slippage,            // slippage
   double   stoploss,            // stop loss
   double   takeprofit,          // take profit
   string   comment=NULL,        // comment
   int      magic=0,             // magic number
   datetime expiration=0,        // pending order expiration
   color    arrow_color=clrNONE  // color
   );


} //namespace MQL4

#endif // TRADEING_H

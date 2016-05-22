#ifndef ORDER_H
#define ORDER_H

#include "stderror-mql4.h"
#include "stdlib-mql4.h"

#include "mql4-def.h"
#include "mql4-data.h"
#include "libgom.h"

#include "ta-lib/ta_libc.h"
#include "indicator.h"
#include "Tradeing.h"

namespace MQL4 {

/**
 * @breif
 * 使用OrderSend()函数通过向开仓位置发送命令进行交易，和放置、修改或删除待办
 * 订单命令一样。每个交易命令引用要求操作类型。交易操作在ENUM_TRADE_REQUEST_ACTIONS
 * 项目中描述。
 */
enum ENUM_TRADE_REQUEST_ACTIONS {
  TRADE_ACTION_DEAL, ///为规定参数的立即执行放置交易命令（市场命令）
  TRADE_ACTION_PENDING, ///在制定环境下执行放置交易命令（待办订单）
  TRADE_ACTION_SLTP,   ///修改折仓并取走开仓利润值
  TRADE_ACTION_MODIFY, ///修改先前放置的命令参量
  TRADE_ACTION_REMOVE, ///删除先前放置的待办订单命令
};

#ifdef ___MQL5___
enum ENUM_ORDER_TYPE {
  ORDER_TYPE_BUY,             ///市场购买订单
  ORDER_TYPE_SELL,            ///市场卖出订单
  ORDER_TYPE_BUY_LIMIT,       ///限制买入待办订单
  ORDER_TYPE_SELL_LIMIT,      ///限制卖出待办订单
  ORDER_TYPE_BUY_STOP,        ///停止买入待办订单
  ORDER_TYPE_SELL_STOP,       ///停止卖出待办订单
  ORDER_TYPE_BUY_STOP_LIMIT,  ///在到达订单价格之上，是限制买入订单安置在停止限制价格中
  ORDER_TYPE_SELL_STOP_LIMIT, ///在到达订单价格之上，是限制卖出订单安置在停止限制价格中
};
#else  //___MQL4___
enum ENUM_ORDER_TYPE {
  ORDER_BUY,             ///市场购买订单
  ORDER_SELL,            ///市场卖出订单
  ORDER_BUYLIMIT,        ///限制买入待办订单
  ORDER_SELLLIMIT,       ///限制卖出待办订单
  ORDER_BUYSTOP,         ///停止买入待办订单
  ORDER_SELLSTOP,        ///停止卖出待办订单
  ORDER_BUY_STOP_LIMIT,  ///在到达订单价格之上，是限制买入订单安置在停止限制价格中
  ORDER_SELL_STOP_LIMIT, ///在到达订单价格之上，是限制卖出订单安置在停止限制价格中
};
#endif //___MQL5___

/**
 * @brief The ENUM_ORDER_TYPE_FILLING enum
 * @param ORDER_FILLING_FOK
 * 执行政策意味着订单只可以在指定额度执行。如果当前市场不提供金融工具需要的额度，订单将无法执行。需要的交易量可以使用市场此刻几种可用的提供来执行。
 * @param ORDER_FILLING_IOC
 * 该模式意味着交易者同意在订单指定范围内，以市场可用的最大交易量执行交易。如果无法执行全部订单交易量，那么剩下的交易量将被取消。
 * @param ORDER_FILLING_RETURN 该政策只用于市场订单 (ORDER_TYPE_BUY 和
 * ORDER_TYPE_SELL)，限价和止损限价订单
 * (ORDER_TYPE_BUY_LIMIT，ORDER_TYPE_SELL_LIMIT，ORDER_TYPE_BUY_STOP_LIMIT 和
 * ORDER_TYPE_SELL_STOP_LIMIT ) 并且只用于市场或交易
 * 执行的交易品种。如果部分执行市场或剩下交易量的限价订单没有取消，则是会进一步处理。为了激活ORDER_TYPE_BUY_STOP_LIMIT
 * 和 ORDER_TYPE_SELL_STOP_LIMIT
 * 订单，将会创建ORDER_FILLING_RETURN执行类型相应的限价订单
 * ORDER_TYPE_BUY_LIMIT/ORDER_TYPE_SELL_LIMIT 。
 */
enum ENUM_ORDER_TYPE_FILLING {
  ORDER_FILLING_FOK,
  ORDER_FILLING_IOC,
  ORDER_FILLING_RETURN,
};

/**
 * @brief The ENUM_ORDER_TYPE_TIME enum
 * @param ORDER_TIME_GTC 取消订单
 * @param ORDER_TIME_DAY 前交易日订单
 * @param ORDER_TIME_SPECIFIED 过期订单
 * @param ORDER_TIME_SPECIFIED_DAY
 * 订单将生效直至指定日期的23:59:59。如果该时间超出了交易期，那么该订单会在最近的交易时间内到期。
 */
enum ENUM_ORDER_TYPE_TIME {
  ORDER_TIME_GTC,
  ORDER_TIME_DAY,
  ORDER_TIME_SPECIFIED,
  ORDER_TIME_SPECIFIED_DAY,
};

enum ENUM_SELECT_BY_TYPE {
  SELECT_BY_POS,    /// index is order ticket
  SELECT_BY_TICKET, /// index in the order pool
};

enum ENUM_ORDER_MODE {
  MODE_TRADES, ///(default)- order selected from trading pool(opened and
  /// pending orders),
  MODE_HISTORY, ///- order selected from history pool (closed and canceled
  /// order).
};

enum ENUM_ORDER_STATUS {
  ENUM_ORDER_STATUS_OPENED,
  ENUM_ORDER_STATUS_MODIFIED,
  ENUM_ORDER_STATUS_CLOSED,
};

/**
 * @breif 客户端与交易服务器执行其他安置操作相互作用，通过使用交易请求来执行。
 *        交易请求由特殊预定MqlTradeRequest类型的结构来体现，包含必要的执行交易订单。
 *        该请求执行结果由MqlTradeResult的类型结构来表示.
 * @param action 交易操作类型，可以是 ENUM_TRADE_REQUEST_ACTIONS
 * 项目值中的一个。
 * @param magic
 * EA交易ID，允许操作分析交易命令过程，当发送交易请求时，每个EA交易都能建立自己独特的ID
 * @param order 命令按钮，用来修改待办订单。
 * @param symbol 交易品种命令，不需要修改命令和关闭放置操作。
 * @param volume 要求命令成交手数，标识每笔订单真实成交量取决于订单执行类型。
 * @param price
 * 价格，必须执行到达命令，交易品种的市场底单，它的执行类型是“市场执行”（SYMBOL_TRADE_EXECUTION_MARKET）
 * ， TRADE_ACTION_DEAL 类型，不要求价格说明。
 * @param stoplimit
 * 价格价值，当价格达到price值时（必要条件），Limit安置待办订单，直到待办订单部能安置。
 * @param sl 在不利于价格活动的情况下的止损数值
 * @param tp 在优惠价格活动的情况下目标数值
 * @param deviation 最大价格偏差，指定在 points 中
 * @param type 命令类型，可以是 ENUM_ORDER_TYPE项目值中的一个
 * @param type_filling 命令执行类型，可以是 ENUM_ORDER_TYPE_FILLING
 * 项目值中的一个
 * @param type_time 命令终结类型，可以是 ENUM_ORDER_TYPE_TIME 项目值中的一个
 * @param expiration 命令终结期限（ ORDER_TIME_SPECIFIED 命令类型）
 * @param comment 命令注解文本
 */

typedef struct MqlTradeRequest {
  ENUM_TRADE_REQUEST_ACTIONS action;    /// 交易操作类型
  ulong magic;                          /// EA交易 ID (魔幻数字)
  ulong order;                          /// 订单号
  ulong deviation;                      /// 需求价格最可能的偏差
  ENUM_ORDER_TYPE type;                 /// 订单类型
  ENUM_ORDER_TYPE_FILLING type_filling; /// 订单执行类型
  ENUM_ORDER_TYPE_TIME type_time;       /// 订单执行时间
  datetime expiration;                  /// 订单终止期 (为 ORDER_TIME_SPECIFIED 类型订单)
  int arrow_color;                      /// arrow color in chart
  ENUM_ORDER_STATUS status;             /// the status of theorder
  datetime sendtime;                    /// sending time
  datetime modifytime;                  /// modify time
  double volume;                        /// 一手需求的交易量
  double price;                         /// 价格
  double stoplimit;                     /// 订单止损限价点位
  double sl;                            /// 订单止损价位点位
  double tp;                            /// 订单盈利价位点位
  double profit;                        /// profit for now
  string comment;                       /// 订单注释
  string symbol;                        /// 交易的交易品种
} MqlTradeRequest;

typedef std::vector<MqlTradeRequest *> VecOrders;
typedef std::map<int, MqlTradeRequest *> MapIntToOrders;

class Order {
public:
  Order();
  ~Order();

  VecOrders _Orders;
  VecOrders _HistoryOrders;
  MapIntToOrders _mapOrders;
  MqlTradeRequest *_SelectedOrder;
  unsigned int _gticket;


private:
    TradingDatas*     _datas;
    RatesData* _SelectedData;
    int*     _CurrentDataPos;
public:
    void setData(TradingDatas* datas, RatesData* SelectedData, int* CurrentDataPos) {
        _datas = datas;
        _SelectedData   = SelectedData  ;
        _CurrentDataPos = CurrentDataPos;
    }

public:
  /**
   * @brief OrdersTotal Returns the number of market and pending orders.
   * @return Total amount of market and pending orders.
   */
  int OrdersTotal();

  /**
   * @brief OrderSelect The function selects an order for further processing.
   * Note
   * The pool parameter is ignored if the order is selected by the ticket
   * number. The ticket number is a unique order identifier.
   * To find out from what list the order has been selected, its close time must
   * be analyzed. If the order close time equals to 0, the order is open or
   * pending and taken from the terminal open orders list.
   * One can distinguish an opened order from a pending order by the order type.
   * If the order close time does not  equal to 0, the order is a closed order or
   * a deleted pending order and was selected from the terminal history.
   * They also differ from each other by their order types. The OrderSelect()
   * function copies order data into program environment and all further calls of
   * OrderClosePrice(), OrderCloseTime(), OrderComment(), OrderCommission(),
   * OrderExpiration(), OrderLots(), OrderMagicNumber(), OrderOpenPrice(),
   * OrderOpenTime(), OrderPrint(), OrderProfit(), OrderStopLoss(), OrderSwap(),
   * OrderSymbol(), OrderTakeProfit(), OrderTicket(), OrderType() functions
   * return the data, copied earlier. It means that in some cases the order
   * details (open price, SL/TP levels or expiration date) may change and the
   * data become non-actual.
   * It is strongly recommended to call the OrderSelect() function before
   * request the order data.
   *
   * Consecutive selection of orders using the SELECT_BY_POS parameter returns
   * information in the sequence in which it was received from the trading
   * server. Sorting of the resulting list of orders cannot be guaranteed.
   *
   * @param index [in]  Order index or order ticket depending on the second
   * parameter. index from 1
   * @param select [in]  Selecting flags. It can be any of the following values:
   *                     SELECT_BY_POS - index in the order pool,
   *                     SELECT_BY_TICKET - index is order ticket.
   * @param pool [in]  Optional order pool index. Used when the selected
   * parameter is SELECT_BY_POS. It can be any of the following values:
   *                   MODE_TRADES (default)- order selected from trading
   * pool(opened and pending orders),
   *                   MODE_HISTORY - order selected from history pool (closed
   * and canceled order).
   * @return It returns true if the function succeeds, otherwise falses. To get
   * the error information, one has to call the GetLastError() function.
   */
  bool OrderSelect(int index,             // index or order ticket
                          int select,            // flag
                          int pool = MODE_TRADES // mode
                          );

  /**
   * @brief OrderOpenPrice Returns open price of the currently selected order.
   * Note
   * The order must be previously selected by the OrderSelect() function.
   * @return Open price of the currently selected order.
   */
  double OrderOpenPrice();

  /**
   * @brief OrderType Returns order operation type of the currently selected
   * order.
   * Note
   * The order must be previously selected by the OrderSelect() function.
   * @return Order operation type of the currently selected order. It can be any
   * of the following values:
   * OP_BUY - buy order,
   * OP_SELL - sell order,
   * OP_BUYLIMIT - buy limit pending order,
   * OP_BUYSTOP - buy stop pending order,
   * OP_SELLLIMIT - sell limit pending order,
   * OP_SELLSTOP - sell stop pending order.
   */
  int OrderType();

  /**
   * @brief OrderSymbol Returns symbol name of the currently selected order.
   * Note
   * The order must be previously selected by the OrderSelect() function.
   * @return The symbol name of the currently selected order.
   */
  string OrderSymbol();

  /**
   * @brief OrderTicket Returns ticket number of the currently selected order.
   * Note
   * The order must be previously selected by the OrderSelect() function.
   * @return Ticket number of the currently selected order.
   */
  int OrderTicket();

  /**
   * @brief OrderLots Returns amount of lots of the selected order.
   * Note
   * The order must be previously selected by the OrderSelect() function.
   * @return Amount of lots (trade volume) of the selected order.
   */
  double OrderLots();

  /**
   * @brief OrderStopLoss Returns stop loss value of the currently selected
   * order.
   * Note
   * The order must be previously selected by the OrderSelect() function.
   * @return Stop loss value of the currently selected order.
   */
  double OrderStopLoss();

  /**
   * @brief OrderModify Modification of characteristics of the previously opened
   * or pending orders.
   * Note
   * Open price and expiration time can be changed only for pending orders. If
   * unchanged values are
   * passed as the function parameters, the error 1 (ERR_NO_RESULT) will be
   * generated.
   * Pending order expiration time can be disabled in some trade servers. In
   * this
   * case, when a non-zero
   *  value is specified in the expiration parameter, the error 147
   * (ERR_TRADE_EXPIRATION_DENIED) will
   * be generated.
   * @param ticket [in]  Unique number of the order ticket.
   * @param price [in]  New open price of the pending order.
   * @param stoploss [in]  New StopLoss level.
   * @param takeprofit [in]  New TakeProfit level.
   * @param expiration [in]  Pending order expiration time.
   * @param arrow_color [in]  Arrow color for StopLoss/TakeProfit modifications
   * in
   * the chart. If the
   *  parameter is missing or has CLR_NONE value, the arrows will not be shown
   * in
   * the chart.
   * @return If the function succeeds, it returns true, otherwise false. To get
   * the detailed error
   * information, call the GetLastError() function.
   */
  bool OrderModify(int ticket,          // ticket
                          double price,        // price
                          double stoploss,     // stop loss
                          double takeprofit,   // take profit
                          datetime expiration, // expiration
                          color arrow_color    // color
                          );

  /**
   * @brief OrderTakeProfit Returns take profit value of the currently selected
   * order.
   * Note
   * The order must be previously selected by the OrderSelect() function.
   * @return Take profit value of the currently selected order.
   */
  double OrderTakeProfit();

  /**
   * @brief OrderClose Closes opened order.
   * @param ticket [in]  Unique number of the order ticket.
   * @param lots [in]  Number of lots.
   * @param price [in]  Closing price.
   * @param slippage [in]  Value of the maximum price slippage in points.
   * @param arrow_color [in]  Color of the closing arrow on the chart. If the
   * parameter is missing or has CLR_NONE value closing arrow will not be drawn
   * on
   * the chart.
   * @return Returns true if successful, otherwise false. To get additional
   * error
   * information, one has to call the GetLastError() function.
   */
  bool OrderClose(int ticket,       // ticket
                         double lots,      // volume
                         double price,     // close price
                         int slippage,     // slippage
                         color arrow_color // color
                         );

  /**
   * @brief OrderSend The main function used to open market or place a pending
   * order.
   * Note
   * At opening of a market order (OP_SELL or OP_BUY), only the latest prices of
   * Bid (for selling) or Ask (for buying) can be used as open price. If
   * operation is performed with a security differing from the current one, the
   * MarketInfo() function must be used with MODE_BID or MODE_ASK parameter for
   * the latest quotes for this security to be obtained.
   * Calculated or unnormalized price cannot be applied. If there has not been
   * the requested open price in the price thread or it has not been normalized
   * according to the amount of digits after decimal point, the error 129
   * (ERR_INVALID_PRICE) will be generated. If the requested open price is fully
   * out of date, the error 138 (ERR_REQUOTE) will be generated independently on
   * the slippage parameter. If the requested price is out of date, but present
   * in the thread, the order will be opened at the current price and only if
   * the current price lies within the range of price+-slippage.
   * StopLoss and TakeProfit levels cannot be too close to the market. The
   * minimal distance of stop levels in points can be obtained using the
   * MarketInfo() function with MODE_STOPLEVEL parameter. In the case of
   * erroneous or unnormalized stop levels, the error 130 (ERR_INVALID_STOPS)
   * will be generated. A zero value of MODE_STOPLEVEL means either absence of
   * any restrictions on the minimal distance for Stop Loss/Take Profit or the
   * fact that a trade server utilizes some external mechanisms for dynamic
   * level control, which cannot be translated in the client terminal. In the
   * second case, GetLastError() can return error 130, because MODE_STOPLEVEL is
   * actually  "floating" here.
   * At placing of a pending order, the open price cannot be too close to the
   * market. The minimal distance of the pending price from the current market
   * one in points can be obtained using the MarketInfo() function with the
   * MODE_STOPLEVEL parameter. In case of false open price of a pending order,
   * the error 130 (ERR_INVALID_STOPS) will be generated. Applying of pending
   * order expiration time can be disabled in some trade servers. In this case,
   * when a non-zero value is specified in the expiration parameter, the error
   * 147 (ERR_TRADE_EXPIRATION_DENIED) will be generated. On some trade servers,
   * the total amount of open and pending orders can be limited. If this limit
   * has been exceeded, no new order will be opened (or no pending order will be
   * placed) and trade server will return error 148 (ERR_TRADE_TOO_MANY_ORDERS).
   * @param symbol [in]  Symbol for trading.
   * @param cmd [in]  Operation type. It can be any of the Trade operation
   * enumeration.
   * @param volume [in]  Number of lots.
   * @param price [in]  Order price.
   * @param slippage [in]  Maximum price slippage for buy or sell orders.
   * @param stoploss [in]  Stop loss level.
   * @param takeprofit [in]  Take profit level.
   * @param comment [in]  Order comment text. Last part of the comment may be
   * changed by server. default is NULL
   * @param magic [in]  Order magic number. May be used as user defined
   * identifier. default is 0
   * @param expiration [in]  Order expiration time (for pending orders
   * only).default is 0
   * @param arrow_color [in]  Color of the opening arrow on the chart. If
   * parameter is missing or has CLR_NONE value opening arrow is not drawn on
   * the chart. default is clrNONE
   * @return Returns number of the ticket assigned to the order by the trade
   * server or -1 if it fails. To get additional error information, one has to
   * call the GetLastError() function.
   */
  int OrderSend(string symbol,              // symbol
                       int cmd,                    // operation
                       double volume,              // volume
                       double price,               // price
                       int slippage,               // slippage
                       double stoploss,            // stop loss
                       double takeprofit,          // take profit
                       string comment = "",        // comment
                       int magic = 0,              // magic number
                       datetime expiration = 0,    // pending order expiration
                       color arrow_color = clrNONE // color
                       );

  /**
   * @brief destroyOrders delete all order, vector, map, ... etc in memory.
   */
  void destroyOrders();

  /**
   * @brief OrderMagicNumber Returns an identifying (magic) number of the
   * currently selected order
   * @return Returns an identifying (magic) number of the currently selected
   * order
   */
  ulong OrderMagicNumber();

  /**
   * @brief OrdersHistoryTotal Returns the number of closed orders in the
   * account history loaded into the terminal.
   * @return Returns the number of closed orders in the account history loaded
   * into the terminal.
   */
  int OrdersHistoryTotal();
  int HistoryTotal();

  /**
   * @brief OrderProfit returns profit of the currently selected order
   * @return profit of the currently selected order
   */
  double OrderProfit();

  void closeAll();
  MqlTradeRequest *findInOrderMap(int ticket);
};

} // namespace MQL4

#endif // ORDER_H

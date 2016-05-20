#ifndef TRADEING_H
#define TRADEING_H

#include "mql4-def.h"
#include "mql4-data.h"

// OrderClose Closes opened order
// OrderCloseBy Closes an opened order by another opposite opened order
// OrderClosePrice Returns close price of the currently selected order
// OrderCloseTime Returns close time of the currently selected order
// OrderComment Returns comment of the currently selected order
// OrderCommission Returns calculated commission of the currently selected order
// OrderDelete Deletes previously opened pending order
// OrderExpiration Returns expiration date of the selected pending order
// OrderLots Returns amount of lots of the selected order
// OrderMagicNumber Returns an identifying (magic) number of the currently
// selected order
// OrderModify Modification of characteristics of the previously opened or
// pending orders
// OrderOpenPrice Returns open price of the currently selected order
// OrderOpenTime Returns open time of the currently selected order
// OrderPrint Prints information about the selected order in the log
// OrderProfit Returns profit of the currently selected order
// OrderSelect The function selects an order for further processing
// OrderSend The main function used to open an order or place a pending order
// OrdersHistoryTotal Returns the number of closed orders in the account history
// loaded into the terminal
// OrderStopLoss Returns stop loss value of the currently selected order
// OrdersTotal Returns the number of market and pending orders
// OrderSwap Returns swap value of the currently selected order
// OrderSymbol Returns symbol name of the currently selected order
// OrderTakeProfit Returns take profit value of the currently selected order
// OrderTicket Returns ticket number of the currently selected order
// OrderType Returns order operation type of the currently selected order

namespace MQL4 {

extern bool selectSymbol(const char* symbol,
                         ENUM_TIMEFRAMES timeframe = PERIOD_M1);

extern int forex_simulator_new_data(TickVector& ticks, const RatesData* rd,
                                    int len);
extern void releaseTickVector(TickVector& ticks);
extern void TickVector2Csv(TickVector& ticks, const char* filepath);

}  // namespace MQL4

#endif  // TRADEING_H

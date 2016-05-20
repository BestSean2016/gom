#ifndef CHECKUP_H
#define CHECKUP_H
#include "mql4-def.h"
#include <string>

using namespace std;

/*
    GetLastError
    IsStopped
    UninitializeReason
    MQLInfoInteger
    MQLInfoString
    MQLSetInteger
    TerminalInfoInteger
    TerminalInfoDouble
    TerminalInfoString
    Symbol
    Period
    Digits
    Point
    IsConnected
    IsDemo
    IsDllsAllowed
    IsExpertEnabled
    IsLibrariesAllowed
    IsOptimization
    IsTesting
    IsTradeAllowed
    IsTradeContextBusy
    IsVisualMode
    TerminalCompany
    TerminalName
    TerminalPath
*/

namespace MQL4 {

/**
 * @brief GetLastError Returns the contents of the system variable _LastError.
 * Note
 * After the function call, the contents of _LastError are reset.
 * For convenience, trade errors are additionally listed in the Trade Server
 * Return Codes section.
 * @return Returns the value of the last error that occurred during the
 * execution of an mql4 program.
 */
extern int GetLastError();

/**
 * @brief Symbol Returns the name of a symbol of the current chart.
 * @return  Value of the _Symbol system variable, which stores the name of the
 * current chart symbol.
 */
extern string Symbol();

/**
 * @brief Point Returns the point size of the current symbol in the quote
 * currency.
 * @return The value of the _Point variable which stores the point size of the
 * current symbol in the quote currency.
 */
extern double Point();

/**
 * @brief Checks if the Expert Advisor is allowed to trade and trading context
 * is not busy.
 * OrderSend(), OrderClose(), OrderCloseBy(), OrderModify(), OrderDelete()
 * trading functions changing the state of a trading account can be called only
 * if trading by Expert Advisors is allowed (the "Allow live trading" checkbox
 * is enabled in the Expert Advisor or script properties).
 * @param [in]  Symbol.
 * @param [in]  Time to check status.
 * @return Returns true if the Expert Advisor is allowed to trade and trading
 * context is not busy, otherwise returns false.
 */

bool IsTradeAllowed(string symbol = "", datetime tested_time = 0);

extern int _LastError;

}  // namespace MQL4

#endif  // CHECKUP_H

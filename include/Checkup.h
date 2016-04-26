#ifndef CHECKUP_H
#define CHECKUP_H

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
 * For convenience, trade errors are additionally listed in the Trade Server Return Codes section.
 * @return Returns the value of the last error that occurred during the execution of an mql4 program.
 */
extern int  GetLastError();


/**
 * @brief Symbol Returns the name of a symbol of the current chart.
 * @return  Value of the _Symbol system variable, which stores the name of the current chart symbol.
 */
extern string  Symbol();




/**
 * @brief Point Returns the point size of the current symbol in the quote currency.
 * @return The value of the _Point variable which stores the point size of the current symbol in the quote currency.
 */
extern double  Point();



extern int _LastError;

} //namespace MQL4

#endif // CHECKUP_H

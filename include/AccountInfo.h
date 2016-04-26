#ifndef ACCOUNT_INFOMATION_H
#define ACCOUNT_INFOMATION_H

/*
    AccountInfoDouble
    AccountInfoInteger
    AccountInfoString
    AccountBalance
    AccountCredit
    AccountCompany
    AccountCurrency
    AccountEquity
    AccountFreeMargin
    AccountFreeMarginCheck
    AccountFreeMarginMode
    AccountLeverage
    AccountMargin
    AccountName
    AccountNumber
    AccountProfit
    AccountServer
    AccountStopoutLevel
    AccountStopoutMode
*/

namespace MQL4 {


/**
 * @brief AccountFreeMargin Returns free margin value of the current account.
 * @return  Free margin value of the current account.
 */
extern double  AccountFreeMargin();


} //namespace MQL4

#endif // ACCOUNT_INFOMATION_H

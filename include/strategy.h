#ifndef STRATEGY_H
#define STRATEGY_H

#include "stderror-mql4.h"
#include "stdlib-mql4.h"

#include "mql4-def.h"
#include "mql4-data.h"
#include "libgom.h"

#include "ta-lib/ta_libc.h"
#include "indicator.h"
#include "Tradeing.h"


namespace MQL4 {

typedef struct StrategyDatas {
    int       _Digits      ; ///Number of digits after decimal point for the current symbol prices
    double    _Point       ; ///Size of the current symbol point in the quote currency
    int       _LastError   ; ///The last error code
    int       _Period      ; ///Timeframe of the current chart
    int       _RandomSeed  ; ///Current status of the generator of pseudo-random integers
    bool      _StopFlag    ; ///Program stop flag
    string    _Symbol      ; ///Symbol name of the current chart
    int       _UninitReason; ///Uninitialization reason code
    double    _Ask         ; ///The latest known seller's price (ask price) of the current symbol
    int       _Bars        ; ///Number of bars in the current chart
    double    _Bid         ; ///The latest known buyer's price (offer price, bid price) of the current symbol
    double *  _Close       ; ///Series array that contains close prices for each bar of the current chart
    double *  _High        ; ///Series array that contains the highest prices of each bar of the current chart
    double *  _Low         ; ///Series array that contains the lowest prices of each bar of the current chart
    double *  _Open        ; ///Series array that contains open prices of each bar of the current chart
    datetime* _Time        ; ///Series array that contains open time of each bar of the current chart
    double *  _Volume      ; ///Series array that contains tick volumes of each bar of the current chart

    StrategyDatas()
        :_Digits      (0)
        ,_Point       (0)
        ,_LastError   (0)
        ,_Period      (0)
        ,_RandomSeed  (0)
        ,_StopFlag    (0)
        ,_Symbol      (0)
        ,_UninitReason(0)
        ,_Ask         (0)
        ,_Bars        (0)
        ,_Bid         (0)
        ,_Close       (0)
        ,_High        (0)
        ,_Low         (0)
        ,_Open        (0)
        ,_Time        (0)
        ,_Volume      (0)
    {

    }
    ~StrategyDatas() {
        if (_Close) delete [] _Close;
        if (_High ) delete [] _High;
        if (_Low  ) delete [] _Low;
        if (_Open ) delete [] _Open;
        if (_Time ) delete [] _Time;
        if (_Volume)delete [] _Volume;
    }
} StrategyDatas;

class Strategy
{
public:
    Strategy();


public:
    StrategyDatas datas;

    double Bid() { return datas._Bid; }
    double Ask() { return datas._Ask; }
    void OnNewData(MqlTick &tick) {
        _SelectedData->addNewTick(tick);
        _Bars = static_cast<int>(MQL4::gSelectedData->data.size());
        _Bid = tick.bid[0];
        _Ask = tick.ask[0];
    }

    string           _SelectedSymbol;
    RatesData*       _SelectedData;

};

} //namespace MQL4

#endif // STRATEGY_H

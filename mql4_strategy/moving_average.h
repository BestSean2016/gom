#ifndef MOVING_AVERAGE_H
#define MOVING_AVERAGE_H


//+------------------------------------------------------------------+
//|                                                  MACD Sample.mq4 |
//|                   Copyright 2005-2014, MetaQuotes Software Corp. |
//|                                              http://www.mql4.com |
//+------------------------------------------------------------------+
#include "stderror-mql4.h"
#include "stdlib-mql4.h"

#include "mql4-def.h"
#include "mql4-data.h"
#include "libgom.h"

#include "ta-lib/ta_libc.h"
#include "Tradeing.h"

#include "order.h"
#include "indicator.h"
#include "strategy.h"

namespace MQL4 {

class MovingAverage :public Strategy {
public:
    MovingAverage() {}
    virtual ~MovingAverage() {}

public:
    virtual void OnInit();
    virtual void OnTick();
    virtual void OnDeinit();

private:
    int CalculateCurrentOrders(string symbol);
    double LotsOptimized();
    void CheckForOpen();
    void CheckForClose();
};

} // namespace MQL4

#endif // MOVING_AVERAGE_H


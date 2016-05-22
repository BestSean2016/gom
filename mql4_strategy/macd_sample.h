#ifndef MACD_SAMPLE_H
#define MACD_SAMPLE_H

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

class MacdSample :public Strategy {
public:
    MacdSample() {}
    virtual ~MacdSample() {}

    void OnInit(void);
    void OnDeinit(void);
    virtual void OnTick(void);
};

}

#endif // MACD_SAMPLE_H


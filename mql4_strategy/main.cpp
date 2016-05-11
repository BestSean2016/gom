#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <time.h>

#include <iostream>

#include "mql4-def.h"
#include "mql4-data.h"
#include "libgom.h"

// #include "ta-lib/ta_libc.h"
#include "indicator.h"
#include "Tradeing.h"

using namespace std;

extern double TakeProfit    ;
extern double Lots          ;
extern double TrailingStop  ;
extern double MACDOpenLevel ;
extern double MACDCloseLevel;
extern int    MATrendPeriod ;

extern int    Bars_ ;
extern double Bid_  ;
extern double Ask_  ;
extern double _Point;

extern void OnInit();
extern void OnDeinit();
extern void OnTick();

int main()
{
    OnInit();

    Bars_ = MQL4::iBars("USDJPY", MQL4::PERIOD_M1);

    for (int i = 0; i < Bars_; i++) {
        OnTick();
    }

    OnDeinit();
    return 0;
}


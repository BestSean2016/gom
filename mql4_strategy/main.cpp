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

extern void OnInit();
extern void OnDeinit();
extern void OnTick();
extern void OnCalculateSomething();
extern void OnNewData();

int main()
{
    OnInit();

    int nBars = MQL4::iBars("USDJPY", MQL4::PERIOD_M1);
    MQL4::TickVector ticks;

    int result = MQL4::forex_simulator_new_data(ticks, MQL4::gSelectedData, 500);
    if (!result) {
        for (int i = 0; i < nBars; i++) {
            MQL4::setCurrentDataPos(i);
            OnNewData();
            OnTick();
        }
    }

    MQL4::releaseTickVector(ticks);
    OnDeinit();
    return 0;
}


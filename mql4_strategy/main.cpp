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
#include "Checkup.h"
#include "Tradeing.h"

using namespace std;
using namespace MQL4;

extern void OnInit();
extern void OnDeinit();
extern void OnTick();
\

#define NEW_TICK_NUMBER 100000

int main()
{
    OnInit();

    Indicator indicator;
    indicator.iBars("USDJPY", MQL4::PERIOD_M1);

    MQL4::TickVector ticks;
    srand(12345);
    int result = MQL4::forex_simulator_new_data(ticks, indicator._SelectedData, NEW_TICK_NUMBER, MQL4::ENUM_TIMEFRAMES::PERIOD_M1);
    if (!result) {
        for (int i = 0; i < NEW_TICK_NUMBER; i++) {
            indicator.OnNewData(ticks[i]);
            indicator.setCurrentDataPos(indicator.iBars("USDJPY", MQL4::PERIOD_M1));
            OnTick();
        }
    }

    MQL4::releaseTickVector(ticks);
    OnDeinit();
    return 0;
}


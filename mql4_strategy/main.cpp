#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <time.h>

#include <iostream>

#include "macd_sample.h"

using namespace std;

#define NEW_TICK_NUMBER 10000 * 60

int main()
{
    MQL4::MacdSample strategy;

    strategy.OnInit();
    int Bars = strategy.iBars("USDJPY", MQL4::PERIOD_M1);

    // MQL4::TickVector ticks;
    // srand(12345);
    // int result = MQL4::forex_simulator_new_data(ticks,
    //                                             strategy.getSelectedData(),
    //                                             NEW_TICK_NUMBER,
    //                                             MQL4::ENUM_TIMEFRAMES::PERIOD_M1);
    // if (!result) {
    //     for (int i = 0; i < NEW_TICK_NUMBER; i++) {
    //         strategy.OnNewData(ticks[i]);
    //         strategy.setCurrentDataPos(
    //                     strategy.iBars("USDJPY", MQL4::PERIOD_M1)
    //                     );
    //         strategy.OnTick();
    //     }
    // }
    //
    // MQL4::releaseTickVector(ticks);

    for (int i = 30; i < Bars; ++i) {
        strategy.setCurrentDataPos(i);
        strategy.OnTick();
    }


    strategy.OnDeinit();
    return 0;
}



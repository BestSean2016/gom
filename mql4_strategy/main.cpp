#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <time.h>

#include <iostream>

#include "macd_sample.h"
#include "moving_average.h"

using namespace std;

#define NEW_TICK_NUMBER 10000 * 60

int main()
{
    srand(time(0));
    MQL4::mapRatesData.get_forex_data("/home/sean/projects/quants/gom/data");

    MQL4::MacdSample stgMacd;
    MQL4::MovingAverage stgMa;

    stgMacd.OnInit();
    stgMa.OnInit();

    int Bars = stgMacd.iBars("USDJPY", MQL4::PERIOD_M1);
    Bars = stgMa.iBars("USDJPY", MQL4::PERIOD_M1);

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

    for (int i = 35; i < Bars; ++i) {
        //stgMacd.setCurrentDataPos(i);
        //stgMacd.OnTick();
        stgMa.setCurrentDataPos(i);
        stgMa.OnTick();
    }

    stgMa.OnDeinit();
    stgMacd.OnDeinit();

    MQL4::mapRatesData.releaseRatesFromMap();
    return 0;
}



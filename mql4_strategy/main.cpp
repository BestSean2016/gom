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

    for (int i = 0; i < nBars; i++) {
        MQL4::setCurrentDataPos(i);
        forex_simulator_new_data(MQL4::gSelectedData);
        OnNewData();
        OnTick();
    }

    OnDeinit();
    return 0;
}


#include "Tradeing.h"
#include <memory.h>
#include <string.h>
#include <fstream>

namespace MQL4 {

string           gSelectedSymbol = "USDJPY";
RatesData*       gSelectedData = 0;


bool selectSymbol(const char* symbol, ENUM_TIMEFRAMES timeframe) {
    string the_symbol;
    if (symbol == NULL)
        the_symbol = gSelectedSymbol;
    else
        the_symbol = symbol;

    gSelectedData = mapRatesData.getSymbol(MARKET_FOREX_FURTURES, the_symbol, timeframe);
    return (gSelectedData != 0);
}


int forex_simulator_new_data(TickVector& ticks, const RatesData* rd, int len) {
    if (!rd) return (-1);

    datetime ltime = rd->rs.time[rd->rs.amount - 1];
    double value[6];
    for (int i = 0; i < len; ++i) {
        MqlTick tick;
        MathGaussianNoise3(value, rd->rs.statPriceDelta.mean, rd->rs.statPriceDelta.stdv);
        MathGaussianNoise3(value + 3, rd->rs.statVolume.mean, rd->rs.statVolume.stdv);

        if (i) {
            tick.ask[0]  = value[0] + ticks[i - 1].ask[0];
            tick.bid[0]  = value[1] + ticks[i - 1].bid[0];
            tick.last    = value[2] + ticks[i - 1].last;
        } else {
            tick.ask[0]  = value[0] + rd->rs.close[rd->rs.amount - 1];
            tick.bid[0]  = value[1] + rd->rs.close[rd->rs.amount - 1];
            tick.last    = value[2] + rd->rs.close[rd->rs.amount - 1];
        }

        tick.ask_volume[0] = (value[3] < 0) ? 1 : value[3];// + ticks[i - 1].ask_volume[0];
        tick.bid_volume[0] = (value[4] < 0) ? 1 : value[4];// + ticks[i - 1].bid_volume[0];
        tick.last_volume   = (value[5] < 0) ? 1 : value[5];// + ticks[i - 1].last_volume;

        ltime += 1;
        tick.time = ltime;
        ticks.push_back(tick);
    }

    return (0);
}

void releaseTickVector(TickVector& ticks) {
    ticks.clear();
}


void TickVector2Csv(TickVector &ticks, const char* filepath) {
    ofstream out(filepath);
    out << ticks;
}

} //namespace MQL4

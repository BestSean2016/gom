#include "indicator.h"


namespace MQL4 {


int  iBars(
   string           symbol,          // symbol
   ENUM_TIMEFRAMES  timeframe        // timeframe
   ) {
    RatesData& rates = getSymbol(MARKET_FOREX_FURTURES, symbol, timeframe);
    return static_cast<int>(rates.rs.amount);
}


double  iMA(
   string          symbol,           // symbol
   ENUM_TIMEFRAMES timeframe,        // timeframe
   int             ma_period,        // MA averaging period
   int             ma_shift,         // MA shift
   int             ma_method,        // averaging method
   int             applied_price,    // applied price
   int             shift             // shift
   ) {
    return (0);
}

double  iMACD(
   string       symbol,           // symbol
   int          timeframe,        // timeframe
   int          fast_ema_period,  // Fast EMA period
   int          slow_ema_period,  // Slow EMA period
   int          signal_period,    // Signal line period
   int          applied_price,    // applied price
   int          mode,             // line index
   int          shift             // shift
   ) {
    return (0);
}

} //namespace MQL4

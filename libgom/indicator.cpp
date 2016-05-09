#include "mql4-data.h"
#include "indicator.h"
#include "ta-lib/ta_libc.h"

namespace MQL4 {


int  iBars(
   string           symbol,          // symbol
   ENUM_TIMEFRAMES  timeframe        // timeframe
   ) {
    RatesData* rates = MQL4::mapRatesData.getSymbol(MARKET_FOREX_FURTURES, symbol, timeframe);
    if (!rates)
        return (0);
    else
        return static_cast<int>(rates->rs.amount);
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


static double * getInputData(const RatesData* rates, int applied_price) {
    double * ptr = 0;
    switch(applied_price) {
    case PRICE_CLOSE:
        ptr = rates->rs.close;
        break;
    case PRICE_OPEN:
        ptr = rates->rs.open;
        break;
    case PRICE_HIGH:
        ptr = rates->rs.high;
        break;
    case PRICE_LOW:
        ptr = rates->rs.low;
        break;
    }

    return (ptr);
}

double  iMACD(
   const char*  symbol,           // symbol
   int          timeframe,        // timeframe
   int          fast_ema_period,  // Fast EMA period
   int          slow_ema_period,  // Slow EMA period
   int          signal_period,    // Signal line period
   int          applied_price,    // applied price
   int          mode,             // line index
   int          shift             // shift
   ) {
    string the_symbol;
    if (symbol == NULL)
        the_symbol = "USDJPY";
    else
        the_symbol = symbol;

    RatesData* rates = MQL4::mapRatesData.getSymbol(MARKET_FOREX_FURTURES, the_symbol, (ENUM_TIMEFRAMES)timeframe);

    double *outMACD = new double[rates->rs.size * 3];
    double *outMACDSignal = outMACD + rates->rs.size;
    double *outMACDHist   = outMACD + rates->rs.size * 2;

    int outBegIdx, outNBElement;
    double *inData = getInputData(rates, applied_price);

    //TA_RetCode code = TA_MACD(0,
    TA_MACD(0,
                              (int)rates->rs.amount - 1,
                              inData,
                              fast_ema_period,
                              slow_ema_period,
                              signal_period,
                              &outBegIdx,
                              &outNBElement,
                              outMACD,
                              outMACDSignal,
                              outMACDHist );

    delete outMACD;

    //
    // to do check the shift must less than amount
    //

    return (mode == MODE_MAIN) ? outMACD[rates->rs.amount - 1 - shift] : outMACDSignal[rates->rs.amount - 1 - shift];
}

} //namespace MQL4

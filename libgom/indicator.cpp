#include "mql4-data.h"
#include "indicator.h"
#include "ta-lib/ta_libc.h"
#include "Tradeing.h"


namespace MQL4 {
int gCurrentDataPos = 0;

void setCurrentDataPos(int pos) {gCurrentDataPos = pos;}

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

int  iBars(
   const char* symbol,          // symbol
   int         timeframe        // timeframe
   ) {
    string s(symbol);
    gSelectedData = MQL4::mapRatesData.getSymbol(MARKET_FOREX_FURTURES, s, (MQL4::ENUM_TIMEFRAMES)timeframe);
    if (!gSelectedData)
        return (0);
    else
        return static_cast<int>(gSelectedData->rs.amount);
}


double  iMA(
   const char *symbol,           // symbol
   int         timeframe,        // timeframe
   int         ma_period,        // MA averaging period
   int         ma_shift,         // MA shift
   int         ma_method,        // averaging method
   int         applied_price,    // applied price
   int         shift             // shift
   ) {
    MQL4::RatesData* rd = MQL4::gSelectedData;
    if (symbol != 0) {
        string the_symbol(symbol);
        rd = MQL4::mapRatesData.getSymbol(MARKET_CHINA_FURTURES, the_symbol, (ENUM_TIMEFRAMES)timeframe);
    }

    int outBegIdx, outNBElement;
    double *outReal = new double[gCurrentDataPos + 1];
    double *inData = getInputData(rd, applied_price);

    //
    // check ma_shift less than rs.amount
    //
    /*
     ENUM_DEFINE( TA_MAType_SMA,   Sma   ) =0,
     ENUM_DEFINE( TA_MAType_EMA,   Ema   ) =1,
     ENUM_DEFINE( TA_MAType_WMA,   Wma   ) =2,
     ENUM_DEFINE( TA_MAType_DEMA,  Dema  ) =3,
     ENUM_DEFINE( TA_MAType_TEMA,  Tema  ) =4,
     ENUM_DEFINE( TA_MAType_TRIMA, Trima ) =5,
     ENUM_DEFINE( TA_MAType_KAMA,  Kama  ) =6,
     ENUM_DEFINE( TA_MAType_MAMA,  Mama  ) =7,
     ENUM_DEFINE( TA_MAType_T3,    T3    ) =8
    */

    /*
     MODE_SMA, 0 //Simple averaging
     MODE_EMA, 1 //Exponential averaging
     MODE_SMMA,2 //Smoothed averaging
     MODE_LWMA,3 //Linear-weighted averaging
    */

    //
    //to to mapping
    //
    TA_MA( ma_shift,
           gCurrentDataPos, //(int)rd->rs.amount - 1,
           inData + ma_shift,
           ma_period,
           (TA_MAType)ma_method,
           &outBegIdx,
           &outNBElement,
           outReal );

    double retval = outReal[outNBElement - 1 - shift];
    delete [] outReal;

    return retval;
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
    MQL4::RatesData* rates = MQL4::gSelectedData;
    if (symbol != 0) {
        string the_symbol(symbol);
        rates = MQL4::mapRatesData.getSymbol(MARKET_CHINA_FURTURES, the_symbol, (ENUM_TIMEFRAMES)timeframe);
    }

    double *outMACD = new double[(gCurrentDataPos + 1) * 3];
    double *outMACDSignal = outMACD + (gCurrentDataPos + 1);
    double *outMACDHist   = outMACDSignal + (gCurrentDataPos + 1);

    int outBegIdx, outNBElement;
    double *inData = getInputData(rates, applied_price);

    //TA_RetCode code = TA_MACD(0,
    TA_MACD(0,
            gCurrentDataPos, //(int)rates->rs.amount - 1
            inData,
            fast_ema_period,
            slow_ema_period,
            signal_period,
            &outBegIdx,
            &outNBElement,
            outMACD,
            outMACDSignal,
            outMACDHist );

    //for (int i = 0; i < outNBElement; ++i) {
    //    cout << i << ", " << outMACD[i] << ", " << outMACDSignal[i] << ", " << outMACDHist[i] << endl;
    //}

    //
    // to do check the shift must less than amount
    //

    double retval = (mode == MODE_MAIN) ?
                outMACD[outNBElement - 2 - shift]
                :
                outMACDSignal[outNBElement - 2 - shift];

    delete [] outMACD;
    return retval;
}


} //namespace MQL4

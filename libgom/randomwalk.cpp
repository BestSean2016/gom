#include <stdlib.h>
#include <string.h>
#include "libgom.h"


bool operator== (MQL4::MqlRates& r1, MQL4::MqlRates& r2)
{
    return (r1.close == r2.close &&
            r1.high  == r2.high  &&
            r1.low   == r2.low   &&
            r1.open  == r2.open  &&
            r1.real_volume == r2.real_volume &&
            r1.spread == r2.spread &&
            r1.tick_volume == r2.tick_volume &&
            r1.time == r2.time);
}

bool operator== (MQL4::MqlRates& r , MQL4::MqlTick& t) {
    return (r.open == t.last && r.open == t.ask[0] && r.open == t.bid[0] &&
            r.tick_volume == t.last_volume && r.tick_volume == t.ask_volume[0] && r.tick_volume == t.bid_volume[0] &&
            r.time == t.time);
}

namespace MQL4 {

//forex
//date,      time, open,   high,   low,    close,  volume
//2016.04.08,16:22,108.600,108.601,108.551,108.555,86
//
static int get_forex_rates_data(MqlRates& rate, const string& str) {
    if (str.length() < 50)
        return ERR_NO_ENOGHT_FOREX_DATA_IN_LINE;

    char* p = (char*)str.c_str();
    rate.time = MQL4::ForexStringToTime(p);
    p += 17;
    rate.open = atof(p);
    p += 8;
    rate.high = atof(p);
    p += 8;
    rate.low = atof(p);
    p += 8;
    rate.close = atof(p);
    p += 8;
    rate.tick_volume = atol(p);

    return (0);
}

static int get_forex_furtures(RatesData &rd, const char* csvfile) {
    string str(csvfile);

    size_t found = str.rfind(CHAR_PATH_SPERATOR);
    string symbol_full = str.substr(found + 1, str.length() - found -1);
    //cout << symbol_full << endl;

    //get symbol and period
    size_t i = 0;
    while(!isdigit(symbol_full[i++]));
    if (i == symbol_full.length()) return ERR_ERROR_FOREX_FILEPATH;
    --i;
    symbol_full.copy(rd.symbol, i, 0);
    rd.period = (ENUM_TIMEFRAMES)atoi(symbol_full.substr(i, symbol_full.length() - i).c_str());

    //
    //TO DO: check the rd.et is valid
    //

    //read data
    std::ifstream fin(csvfile);
    while(getline(fin, str)) {
        MqlRates rate;
        if (get_forex_rates_data(rate, str))
            break;
        rd.data.push_back(rate);
    }

    //cout << rd.et << ',' << rd.symbol << endl;
    return (0);
}

int read_forex_csv(RatesData &rd, MARKETID market, const char* csvfile) {

    int result = ERR_UNKONW_MARKET;
    switch((int)market) {
    case MARKET_FOREX_FURTURES:
        result = get_forex_furtures(rd, csvfile);
        break;
    }

    return result;
}

int reates_to_tick(RatesData& rd, TickData& td) {
    strcpy(td.symbol,rd.symbol);
    td.market = rd.market;
    for (auto& p : rd.data) {
        MqlTick mt;
        mt.bid[0] = mt.ask[0] = mt.last = p.open,
                mt.bid_volume[0] = mt.ask_volume[0] = mt.last_volume = p.tick_volume,
                mt.time = p.time;
        td.data.push_back(mt);
    }

    return (0);
}

} //namespace MQL4

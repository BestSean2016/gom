#include "libgom.h"

namespace MQL4 {

static int get_forex_furtures(RatesData &rd, string& symbol_full) {
    //get symbol and period
    size_t i = 0;
    while(!isdigit(symbol_full[i++]));
    if (i == symbol_full.length()) return ERR_ERROR_FOREX_FILEPATH;
    --i;
    symbol_full.copy(rd.symbol, i, 0);
    rd.et = (ENUM_TIMEFRAMES)atoi(symbol_full.substr(i, symbol_full.length() - i).c_str());
    //check the rd.et is valid

    //read data

    //cout << rd.et << ',' << rd.symbol << endl;
    return (0);
}

int read_forex_csv(RatesData &rd, MARKETID market, const char* csvfile) {
    string str(csvfile);

    size_t found = str.rfind(CHAR_PATH_SPERATOR);
    string symbol_full = str.substr(found + 1, str.length() - found -1);
    //cout << symbol_full << endl;

    int result = ERR_UNKONW_MARKET;
    switch((int)market) {
    case MARKET_FOREX_FURTURES:
        result = get_forex_furtures(rd, symbol_full);
        break;
    }

    return result;
}


} //namespace MQL4

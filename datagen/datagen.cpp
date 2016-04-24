#include "libgom.h"


int main(const int argc, const char* argv[]) {
    if (argc < 2) return (-1);
    MQL4::RatesData rd;
    MQL4::read_forex_csv(rd, MQL4::MARKET_FOREX_FURTURES, argv[1]);

    MQL4::ForexStringToTime("2016.04.08,16:22,108.600,108.601,108.551,108.555,86");
    return (0);
}

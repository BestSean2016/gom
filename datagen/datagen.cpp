#include "libgom.h"


int main(const int argc, const char* argv[]) {
    if (argc < 2) return (-1);
    MQL4::RatesData rd;
    MQL4::read_forex_csv(rd, MQL4::MARKET_FOREX_FURTURES, argv[1]);
    return (0);
}

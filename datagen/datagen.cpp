#include "libgom.h"
#include <memory.h>
#include <string.h>

#define REQUIRE(x) std::cout << ((x) ? "true\n" : "false\n")

int main(const int argc, const char* argv[]) {
//    if (argc < 2) return (-1);
//    MQL4::RatesData rd;
//    MQL4::read_forex_csv(rd, MQL4::MARKET_FOREX_FURTURES, argv[1]);
//
//    MQL4::ForexStringToTime("2016.04.08,16:22,108.600,108.601,108.551,108.555,86");


    MQL4::RatesData rd;
    int result = MQL4::read_forex_csv(
                   rd,
                   MQL4::MARKET_FOREX_FURTURES,
                   "/home/sean/projects/quants/gom/data/USDJPY1.csv");
    REQUIRE(result == 0);
    REQUIRE(rd.symbol.market == MQL4::MARKET_FOREX_FURTURES);
    REQUIRE(rd.symbol.symbol_name == string("USDJPY"));
    REQUIRE(rd.symbol.period == MQL4::ENUM_TIMEFRAMES::PERIOD_M1);
    REQUIRE(rd.data.size() == 13455);

    MQL4::MqlRates r;
    memset(&r, 0, sizeof(r));

    //line 1
    r.close = 108.555, r.high = 108.601, r.low = 108.551, r.open = 108.600, r.tick_volume = 86;
    r.time = MQL4::ForexStringToTime("2016.04.08,16:22,108.600,108.601,108.551,108.555,86");
    REQUIRE((rd.data[1 - 1] == r));


    ////line 1000
    ////2016.04.11,11:01,108.134,108.139,108.123,108.130,34
    r.open = 108.134, r.high = 108.139, r.low = 108.123, r.close = 108.130, r.tick_volume = 34;
    r.time = MQL4::ForexStringToTime("2016.04.11,11:01");
    bool t = (rd.data[1000 - 1] == r);
    REQUIRE(t);

    //line 3000
    //2016.04.12,20:27,108.580,108.592,108.569,108.591,35
    r.open = 108.580, r.high = 108.592, r.low = 108.569, r.close = 108.591, r.tick_volume = 35;
    r.time = MQL4::ForexStringToTime("2016.04.12,20:27");
    t = (rd.data[3000 - 1] == r);
    REQUIRE(t);

    //line 6000
    //2016.04.14,22:43,109.378,109.396,109.377,109.395,13
    r.open = 109.378, r.high = 109.396, r.low = 109.377, r.close = 109.395, r.tick_volume = 13;
    r.time = MQL4::ForexStringToTime("2016.04.14,22:43");
    t = (rd.data[6000 - 1] == r);
    REQUIRE(t);

    //line 12000
    //2016.04.21,05:01,109.674,109.679,109.673,109.673,17
    r.open = 109.674, r.high = 109.679, r.low = 109.673, r.close = 109.673, r.tick_volume = 17;
    r.time = MQL4::ForexStringToTime("2016.04.21,05:01");
    t = (rd.data[12000 - 1] == r);
    REQUIRE(t);


    //line 13455
    //2016.04.22,05:18,109.452,109.452,109.444,109.445,13
    r.open = 109.452, r.high = 109.452, r.low = 109.444, r.close = 109.445, r.tick_volume = 13;
    r.time = MQL4::ForexStringToTime("2016.04.22,05:18");
    t = (rd.data[13455 - 1] == r);
    REQUIRE(t);

    MQL4::TickData td;
    reates_to_tick(rd, td);
    REQUIRE(rd.data.size() == td.data.size());
    for (size_t i = 0; i < rd.data.size(); ++i) {
        t = (rd.data[i] == td.data[i]);
        REQUIRE(t);
    }

    MQL4::releaseRates(rd);
    return (0);
}

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <time.h>

#include <iostream>

#include "mql4-def.h"
#include "libgom.h"

TEST_CASE( "ForexStringToTime", "Convertions") {
    MQL4::datetime t1 = MQL4::ForexStringToTime("2016.04.08,16:22,108.600,108.601,108.551,108.555,86");
    struct tm lt;
    memset(&lt, 0, sizeof(lt));
    lt.tm_year = 2016 - 1900;
    lt.tm_mon  = 3;
    lt.tm_mday = 8;
    lt.tm_hour = 16;
    lt.tm_min = 22;
    time_t t2 = mktime(&lt);
    std::cout << t1 << ", " << t2 << endl;
    REQUIRE( t1 == t2);
}


TEST_CASE( "read_forex_csv", "DataAdaptor") {
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
    bool t = (rd.data[0] == r);
    REQUIRE(t);


    //line 1000
    //2016.04.11,11:01,108.134,108.139,108.123,108.130,34
    r.open = 108.134, r.high = 108.139, r.low = 108.123, r.close = 108.130, r.tick_volume = 34;
    r.time = MQL4::ForexStringToTime("2016.04.11,11:01");
    t = (rd.data[1000 - 1] == r);
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
}

TEST_CASE( "serialization of forex rates", "serialization") {
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

    result = MQL4::serializateRates(rd, rd.data.size());
    REQUIRE(result == 0);
    REQUIRE(rd.rs.size == rd.data.size() * 2);
    REQUIRE(rd.rs.amount == rd.data.size());

    for (size_t i = 0; i < rd.data.size(); ++i) {
        bool t = (rd.data[i].open == rd.rs.open[i]
             && rd.data[i].close  == rd.rs.close[i]
             && rd.data[i].open   == rd.rs.open[i]
             && rd.data[i].high   == rd.rs.high[i]
             && rd.data[i].low    == rd.rs.low[i]
             && rd.data[i].time   == rd.rs.time[i]
             && rd.data[i].tick_volume == rd.rs.tick_volume[i]);
        REQUIRE(t);
    }

    MQL4::releaseRates(rd);
    REQUIRE(rd.rs.time == 0);
    REQUIRE(rd.data.size() == 0);
    REQUIRE(rd.rs.amount == 0);
}

TEST_CASE( "get_forex_data from path", "get_forex_data") {
    int result = MQL4::get_forex_data("/home/sean/projects/quants/gom/data");
    REQUIRE(result == 0);

    std::string symbol_name("USDJPY");
    MQL4::RatesData& rd = MQL4::getSymbol(MQL4::MARKET_FOREX_FURTURES, symbol_name, MQL4::PERIOD_M1);
    REQUIRE(rd.symbol.market == MQL4::MARKET_FOREX_FURTURES);
    REQUIRE(rd.symbol.symbol_name == string("USDJPY"));
    REQUIRE(rd.symbol.period == MQL4::ENUM_TIMEFRAMES::PERIOD_M1);
    REQUIRE(rd.data.size() == 13455);
}


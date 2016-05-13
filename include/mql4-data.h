#ifndef RATESDATA_H
#define RATESDATA_H


#include "mql4-def.h"
#include "Math.h"

namespace MQL4 {


//mql5
struct MqlParam
{
    ENUM_DATATYPE     type;                    // type of the input parameter, value of ENUM_DATATYPE
    long              integer_value;           // field to store an integer type
    double            double_value;            // field to store a double type
    string            string_value;            // field to store a string type
};


//The date type structure contains eight fields of the int type:
typedef struct MqlDateTime
{
    int year;           // Year
    int mon;            // Month
    int day;            // Day
    int hour;           // Hour
    int min;            // Minutes
    int sec;            // Seconds
    int day_of_week;    // Day of week (0-Sunday, 1-Monday, ... ,6-Saturday)
    int day_of_year;    // Day number of the year (January 1st is assigned the number value of zero)
}MqlDateTime;


//This is a structure for storing the latest prices of the symbol. It is designed for fast retrieval of the most requested information about current prices.
typedef struct MqlTick
{
    datetime     time;          // Time of the last prices update
    double       last;          // Price of the last deal (Last)
    DEEP_PRICE   bid;           // Bid price
    DEEP_PRICE   ask;           // Ask price
    ulong        last_volume;                // Volume for the current Last price
    DEEP_VOLUME  bid_volume;
    DEEP_VOLUME  ask_volume;
} MqlTick ;


//This structure stores information about the prices, volumes and spread.
typedef struct MqlRates
{
    datetime time;         // Period start time
    double   open;         // Open price
    double   high;         // The highest price of the period
    double   low;          // The lowest price of the period
    double   close;        // Close price
    ulong    tick_volume;  // Tick volume
    int      spread;       // Spread
    ulong    real_volume;  // Trade volume

    bool operator== (const MQL4::MqlRates& r2);
    bool operator== (const MQL4::MqlTick& t);

} MqlRates;


typedef struct RatesSerial {
    size_t     amount;
    size_t     size;
    datetime * time;         // Period start time
    double   * open;         // Open price
    double   * high;         // The highest price of the period
    double   * low;          // The lowest price of the period
    double   * close;        // Close price
    ulong    * tick_volume;  // Tick volume
    BASIC_STATISTICS  statPrice;
    BASIC_STATISTICS  statVolume;
    BASIC_STATISTICS  statPriceDelta;
    BASIC_STATISTICS  statVolumeDelta;
} RatesSerial;

typedef std::vector<MqlRates> RatesVector;
typedef std::vector<MqlTick>  TickVector;

///this structure stores infoamtion about the series of one symbol
typedef struct TickData {
    MARKETID    market;  //market id
    string      symbol;  //
    TickVector    data;
} TickData;

typedef struct SYMBOL {
    MARKETID        market;
    string          symbol_name;
    ENUM_TIMEFRAMES period;

    SYMBOL() {}
    SYMBOL(MARKETID marketid, string& symb, MQL4::ENUM_TIMEFRAMES perd)
        : market(marketid), symbol_name(symb), period(perd){
    }

    bool operator < (const SYMBOL& symbol) const {
        if (market != symbol.market)
            return market < symbol.market;
        else if (symbol_name != symbol.symbol_name)
            return symbol_name < symbol.symbol_name;
        else
            return period < symbol.period;
    }
} SYMBOL;




class RatesData
{
public:
    RatesData();
    ~RatesData();
public:
    string            key_; //key for search in map
    SYMBOL          symbol;
    RatesVector       data;
    RatesSerial         rs;

public:
    /* initial */
    int read_forex_csv(MARKETID market, const char* csvfile);

    /**
     * @brief serializateRates serializate rates data
     * @param newDataAmount reserved size of buffer of serializated
     * @return the result code, zero for succeed
     */
    int serializateRates(size_t newDataAmount);


    /**
     * @brief addRateData add a new RatesData
     * @param rate new data
     * @return the result code
     */
    int addRateData(MqlRates& rate);


    /**
     * @brief releaseRates release memory of RatesData
     * @param rd the RatesData space
     */
    void releaseData();

    /* convert to tick */
    int reates_to_tick(TickData& td);

private:
    /**
     * @brief get_forex_furtures_ get forex future data
     * @param csvfile the csvfile was export from mt4 software
     * @return the result
     */
    int get_forex_furtures_(const char* csvfile);



    //forex
    //date,      time, open,   high,   low,    close,  volume
    //2016.04.08,16:22,108.600,108.601,108.551,108.555,86
    //
    /**
     * @brief RatesData::get_forex_rates_data__ get one MqlRates data from a line
     *
     * data format :
     * date,      time, open,   high,   low,    close,  volume
     * 2016.04.08,16:22,108.600,108.601,108.551,108.555,86
     *
     * @param rate the data
     * @param str the text line from csv file
     * @return the result
     */
    int get_forex_rates_data__(MqlRates& rate, const string& str);

};

typedef std::map<string, RatesData*> MAP_RATES_DATA;
class MapRatesData {
public:
    MapRatesData();
    ~MapRatesData();

private:
    MAP_RATES_DATA map_;
public:
    //find
    RatesData * getSymbol(MARKETID market, string& symbol_name, ENUM_TIMEFRAMES tf);
    RatesData * getSymbol(string& key);

    //initial data
    int get_forex_data(const char* path);

    //release data
    void releaseRatesFromMap();

    //return size of map
    size_t size();
};


extern MapRatesData mapRatesData;

extern inline string &genSymbolKey(SYMBOL& symbol,string& key);
extern inline string &genSymbolKey(MARKETID market, string& symbol_name, ENUM_TIMEFRAMES tf,string& key);


} //namesapceMQL4

#endif // RATESDATA_H

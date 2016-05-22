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

    /**
     * @brief addNewTick add new tick data to ratedata
     * @param tick the new tick data
     */
    void addNewTick(MqlTick& tick);

    /**
     * @brief ratesToCSV save rates data to the csv
     * @param csvpath the new filepath
     */
    void ratesToCSV(const char* csvpath);

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


    bool is_new_rates_(ENUM_TIMEFRAMES period, datetime rates_time, datetime tick_time);
    void addRateData_(MqlTick& tick);
    void update_rate_(MqlRates& rates, MqlTick& tick);
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



typedef struct TradingDatas {
  int _Digits;       /// Number of digits after decimal point for the current symbol
                     /// prices
  int _LastError;    /// The last error code
  int _Period;       /// Timeframe of the current chart
  int _RandomSeed;   /// Current status of the generator of pseudo-random integers
  int _UninitReason; /// Uninitialization reason code
  int _Bars;         /// Number of bars in the current chart
  bool _StopFlag;    /// Program stop flag
  double _Ask;       /// The latest known seller's price (ask price) of the current
                     /// symbol
  double _Bid;       /// The latest known buyer's price (offer price, bid price) of
  double _Last;
  double _Point;     /// Size of the current symbol point in the quote currency
                     /// the current symbol
  double *_Close;    /// Series array that contains close prices for each bar of
                     /// the current chart
  double *_High;     /// Series array that contains the highest prices of each bar
                     /// of the current chart
  double *_Low;      /// Series array that contains the lowest prices of each bar of
                     /// the current chart
  double *_Open;     /// Series array that contains open prices of each bar of the
                     /// current chart
  datetime *_Time;   /// Series array that contains open time of each bar of the
                     /// current chart
  double *_Volume;   /// Series array that contains tick volumes of each bar of
                     /// the current chart
  string _Symbol;    /// Symbol name of the current chart

  TradingDatas()
      : _Digits(0),_LastError(0), _Period(0), _RandomSeed(0),
        _UninitReason(0), _Bars(0), _StopFlag(0), _Ask(0), _Bid(0),  _Last(0), _Point(0),
        _Close(0), _High(0), _Low(0), _Open(0), _Time(0), _Volume(0), _Symbol("")  {}
  ~TradingDatas() {
    if (_Close)  delete[] _Close;
    if (_High)   delete[] _High;
    if (_Low)    delete[] _Low;
    if (_Open)   delete[] _Open;
    if (_Time)   delete[] _Time;
    if (_Volume) delete[] _Volume;
  }
} TradingDatas;


extern inline string &genSymbolKey(SYMBOL& symbol,string& key);
extern inline string &genSymbolKey(MARKETID market, string& symbol_name, ENUM_TIMEFRAMES tf,string& key);

extern ostream& operator<< (ostream& out, TickVector vec);

} //namesapceMQL4

#endif // RATESDATA_H

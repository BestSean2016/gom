#ifndef MQL4DEF_H
#define MQL4DEF_H



#include "stderror-mql4.h"
#include "StdLibErr.h"
#include <string>
#include <vector>

using namespace std;


namespace MQL4 {

typedef time_t datetime;
typedef unsigned long ulong;
typedef unsigned int  color;

enum MARKETID {
    MARKET_FOREX_FURTURES,
    MARKET_CHINA_FURTURES,
    MARKET_CHINA_STOCKES,
};

#define SYMBOL_NAME_LENGTH 32
typedef char SYMBOL_NAME[SYMBOL_NAME_LENGTH];

#define MAX_DEEP_PRICE 5
typedef double DEEP_PRICE[MAX_DEEP_PRICE];
typedef ulong  DEEP_VOLUME[MAX_DEEP_PRICE];

//mql4
typedef enum ENUM_TIMEFRAMES {
    PERIOD_TICK     = -1,
    PERIOD_CURRENT  = 0 , //Current timeframe
    PERIOD_M1   =  1    , //1 minute
    PERIOD_M5   =  5    , //5 minutes
    PERIOD_M15  =  15   , //15 minutes
    PERIOD_M30  =  30   , //30 minutes
    PERIOD_H1   =  60   , //1 hour
    PERIOD_H4   =  240  , //4 hours
    PERIOD_D1   =  1440 , //1 day
    PERIOD_W1   =  10080, //1 week
    PERIOD_MN1  =  43200, //1 month
    PERIOD_M2   =  2    , //2 minutes
    PERIOD_M3   =  3    , //3 minutes
    PERIOD_M4   =  4    , //4 minutes
    PERIOD_M6   =  6    , //6 minutes
    PERIOD_M10  =  10   , //10 minutes
    PERIOD_M12  =  12   , //12 minutes
    PERIOD_M20  =  20   , //20 minutes
    PERIOD_H2   =  120  , //2 hours
    PERIOD_H3   =  180  , //3 hours
    PERIOD_H6   =  360  , //6 hours
    PERIOD_H8   =  480  , //8 hours
    PERIOD_H12  =  720  , //12 hours
} ENUM_TIMEFRAMES;

//mql4
//https://docs.mql4.com/constants/objectconstants/visible
//Visibility of Objects
#define OBJ_NO_PERIODS  -1  //The object is not drawn in all timeframes
#define EMPTY           -1  //The object is not drawn in all timeframes
#define OBJ_PERIOD_M1   0x0001  //The object is drawn in 1-minute chart
#define OBJ_PERIOD_M5   0x0002  //The object is drawn in 5-minute chart
#define OBJ_PERIOD_M15  0x0004  //The object is drawn in 15-minute chart
#define OBJ_PERIOD_M30  0x0008  //The object is drawn in 30-minute chart
#define OBJ_PERIOD_H1   0x0010  //The object is drawn in 1-hour chart
#define OBJ_PERIOD_H4   0x0020  //The object is drawn in 4-hour chart
#define OBJ_PERIOD_D1   0x0040  //The object is drawn in day charts
#define OBJ_PERIOD_W1   0x0080  //The object is drawn in week charts
#define OBJ_PERIOD_MN1  0x0100  //The object is drawn in month charts
#define OBJ_ALL_PERIODS 0x01ff  //The object is drawn in all timeframes

#define ArraySize(array) (sizeof((array)) / sizeof(array[0]))

//mql5
enum ENUM_DATATYPE {
    TYPE_BOOL	, //bool
    TYPE_CHAR	, //char
    TYPE_UCHAR	, //uchar
    TYPE_SHORT	, //short
    TYPE_USHORT	, //ushort
    TYPE_COLOR	, //color
    TYPE_INT	, //int
    TYPE_UINT	, //uint
    TYPE_DATETIME,//datetime
    TYPE_LONG	, //long
    TYPE_ULONG	, //ulong
    TYPE_FLOAT	, //float
    TYPE_DOUBLE	, //double
    TYPE_STRING	, //string
};


enum ENUM_APPLIED_PRICE {
    ID              , //Description
    PRICE_CLOSE     , //Close price
    PRICE_OPEN      , //Open price
    PRICE_HIGH      , //The maximum price for the period
    PRICE_LOW       , //The minimum price for the period
    PRICE_MEDIAN    , //Median price, (high + low)/2
    PRICE_TYPICAL   , //Typical price, (high + low + close)/3
    PRICE_WEIGHTED  , //Average price, (high + low + close + close)/4
};

enum ENUM_MA_METHOD {
    MODE_SMA, //Simple averaging
    MODE_EMA, //Exponential averaging
    MODE_SMMA, //Smoothed averaging
    MODE_LWMA, //Linear-weighted averaging
};

#define SELECT_BY_POS 0 //- index in the order pool,
#define SELECT_BY_TICKET 1 //- index is order ticket.

//Indicator Lines
//Indicator line identifiers used in iMACD(), iRVI() and iStochastic() indicators.
#define MODE_MAIN	0 //Base indicator line
#define MODE_SIGNAL	1 //Signal line
//Indicator line identifiers used in iADX() indicator.
#define MODE_MAIN    0	//Base indicator line
#define MODE_PLUSDI  1	//+DI indicator line
#define MODE_MINUSDI 2	//-DI indicator line
//Indicator line identifiers used in iBands(), iEnvelopes(), iEnvelopesOnArray() and iFractals() indicators.
#define MODE_LOWER	2	//Lower line
#define MODE_UPPER	1	//Upper line
//Indicator line identifiers used in iAlligator() and iGator() indicators.
#define MODE_GATORJAW	1	//Jaw line
#define MODE_GATORTEETH	2	//Teeth line
#define MODE_GATORLIPS	3	//Lips line
//Ichimoku Kinko Hyo identifiers used in iIchimoku() indicator call as source of requested data.
#define MODE_TENKANSEN	    1	//Tenkan-sen
#define MODE_KIJUNSEN	    2	//Kijun-sen
#define MODE_SENKOUSPANA	3	//Senkou Span A
#define MODE_SENKOUSPANB	4	//Senkou Span B
#define MODE_CHIKOUSPAN	    5	//Chikou Span

#define MODE_TRADES  0 //(default)- order selected from trading pool(opened and pending orders),
#define MODE_HISTORY 1 //- order selected from history pool (closed and canceled order).



#define OP_BUY	        0	//Buy operation
#define OP_SELL	        1	//Sell operation
#define OP_BUYLIMIT	    2	//Buy limit pending order
#define OP_SELLLIMIT	3	//Sell limit pending order
#define OP_BUYSTOP	    4	//Buy stop pending order
#define OP_SELLSTOP	    5	//Sell stop pending order



#ifndef NULL
#define NULL 0 //Zero for any types. Also indicates empty state of the string
#endif

#define EMPTY -1 //Indicates empty state of the parameter
#define EMPTY_VALUE 0x7FFFFFFF //Empty value in an indicator buffer. Default custom indicator empty value, 2147483647 (0x7FFFFFFF)
#define CLR_NONE -1 //Absence of color. Indicates empty state of colors
#define clrNONE -1  //Absence of color. Indicates empty state of colors
#define CHARTS_MAX 100 //The maximum possible number of simultaneously open charts in the terminal
#define INVALID_HANDLE -1 //Incorrect handle
#define IS_DEBUG_MODE 1 //Flag that a mql4-program operates in debug mode , non zero in debug mode, otherwise zero
#define IS_PROFILE_MODE 1 //Flag that a mql4-program operates in profiling mode, on zero in profiling mode, otherwise zero
#define WHOLE_ARRAY 0 //sed with array functions. Indicates that all array elements will be processed. Means the number of items remaining until the end of the array, i.e., the entire array will be processed
#define WRONG_VALUE -1 //The constant can be implicitly cast to any enumeration type



#define Green  0x00008001
#define Red    0x000000ff
#define Blue   0x00ff0000
#define Violet 0x00ee82ee


#define CHAR_PATH_SPERATOR '/'

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

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
} MqlRates;

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


typedef std::vector<MqlRates> RatesVector;
typedef std::vector<MqlTick>  TickVector;

///this structure stores infoamtion about the series of one symbol
typedef struct TickData {
    MARKETID    market;  //market id
    SYMBOL_NAME symbol;  //
    TickVector    data;
} TickData;

///this structure stores series of one rates
typedef struct RatesData {
    MARKETID    market;
    SYMBOL_NAME symbol;
    ENUM_TIMEFRAMES et;
    RatesVector   data;
} RatesData;

#ifdef __cplusplus
} //extern "C"
#endif //__cplusplus


} //namespace MQL4

#endif // MQL4DEF_H

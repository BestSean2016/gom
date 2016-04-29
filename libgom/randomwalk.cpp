#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sstream>

#include "libgom.h"


namespace MQL4 {

MapRatesData mapRatesData;

bool MqlRates::operator== (const MQL4::MqlRates& r2)
{
    return (close == r2.close &&
            high  == r2.high  &&
            low   == r2.low   &&
            open  == r2.open  &&
            tick_volume == r2.tick_volume &&
            //real_volume == r2.real_volume &&
            //spread == r2.spread &&
            time == r2.time);
}

bool MqlRates::operator== (const MqlTick& t) {
    return (open == t.last && open == t.ask[0] && open == t.bid[0] &&
            tick_volume == t.last_volume && tick_volume == t.ask_volume[0] &&
            tick_volume == t.bid_volume[0] && time == t.time);
}


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
    //rate.real_volume = 0;
    //rate.spread = 0;

    return (0);
}

static int get_forex_furtures(RatesData &rd, const char* csvfile) {
    string str(csvfile);

    size_t found = str.rfind(CHAR_PATH_SPERATOR);
    string symbol_full = str.substr(found + 1, str.length() - found -1);
    //cout << symbol_full << endl;

    //get symbol and period
    size_t i = 0;
    while(i < symbol_full.size() && !isdigit(symbol_full[i])) ++i;
    if (i == symbol_full.length()) return ERR_ERROR_FOREX_FILEPATH;

    rd.symbol.market = MARKET_FOREX_FURTURES;
    rd.symbol.symbol_name = symbol_full.substr(0, i);
    rd.symbol.period = (ENUM_TIMEFRAMES)atoi(symbol_full.substr(i, symbol_full.length() - i).c_str());
    genSymbolKey(MARKET_FOREX_FURTURES, rd.symbol.symbol_name, rd.symbol.period, rd.key_);
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

    serializateRates(rd, rd.data.size());

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

int get_forex_data(const char* path) {
    DIR *dir;
    struct dirent *ptr;
    struct stat file_stat;
    char base[1000];

    if ((dir=opendir(path)) == NULL)
        return ERR_WRONG_PATH;

    while ((ptr=readdir(dir)) != NULL) {
        if(strcmp(ptr->d_name,".")==0 || strcmp(ptr->d_name,"..")==0)    ///current dir OR parrent dir
            continue;
        else {
            string filepath(path);
            filepath.append("/");
            filepath.append(ptr->d_name);
            lstat(filepath.c_str(), &file_stat);
            if(S_ISREG(file_stat.st_mode)) {    ///file
                //printf("d_name:%s/%s\n",basePath,ptr->d_name);
                RatesData * rd = new RatesData;
                read_forex_csv(*rd, MARKET_FOREX_FURTURES, filepath.c_str());
                mapRatesData.insert(std::pair<string, RatesData*>(rd->key_, rd));
            } else if (S_ISDIR(file_stat.st_mode)) { ///dir
                memset(base,'\0',sizeof(base));
                strcpy(base, path);
                strcat(base,"/");
                strcat(base,ptr->d_name);
                get_forex_data(base);
            }
        }
    }
    closedir(dir);

    string s("0|USDJPY|1");
    RatesData* rd = getSymbol(s);
    rd->symbol.market = MARKET_FOREX_FURTURES;
    return (0);
}

int reates_to_tick(RatesData& rd, TickData& td) {
    td.symbol = rd.symbol.symbol_name;
    td.market = rd.symbol.market;
    for (auto& p : rd.data) {
        MqlTick mt;
        mt.bid[0] = mt.ask[0] = mt.last = p.open,
                mt.bid_volume[0] = mt.ask_volume[0] = mt.last_volume = p.tick_volume,
                mt.time = p.time;
        td.data.push_back(mt);
    }

    return (0);
}

int serializateRates(RatesData& rd, size_t newDataAmount) {
    rd.rs.size = rd.data.size() + newDataAmount;
    rd.rs.amount = rd.data.size();
    /*
    datetime * time;         // Period start time
    double   * open;         // Open price
    double   * high;         // The highest price of the period
    double   * low;          // The lowest price of the period
    double   * close;        // Close price
    ulong    * tick_volume;  // Tick volume
    */

    rd.rs.time  = reinterpret_cast<datetime*>(new char[
        (sizeof(datetime) + 4 * sizeof(double) + sizeof(ulong)) * rd.rs.size]);
    if (!rd.rs.time) return ERR_OUT_OF_MEMORY;
    rd.rs.open  = reinterpret_cast<double*>(rd.rs.time + rd.rs.size);
    rd.rs.high  = rd.rs.open + rd.rs.size;
    rd.rs.low   = rd.rs.high + rd.rs.size;
    rd.rs.close = rd.rs.low  + rd.rs.size;
    rd.rs.tick_volume = reinterpret_cast<ulong*>(rd.rs.close + rd.rs.size);


    for (size_t i = 0; i < rd.data.size(); ++i) {
        rd.rs.open[i]  = rd.data[i].open ,
        rd.rs.close[i] = rd.data[i].close,
        rd.rs.open[i]  = rd.data[i].open ,
        rd.rs.high[i]  = rd.data[i].high ,
        rd.rs.low[i]   = rd.data[i].low  ,
        rd.rs.time[i]  = rd.data[i].time ,
        rd.rs.tick_volume[i] = rd.data[i].tick_volume;
    }

    return (0);
}

int addRateData(RatesData& rd, MqlRates& rate) {
    if (rd.rs.amount + 1 > rd.rs.size) return ERR_OUT_OF_BUFFER;
    rd.data.push_back(rate);
    rd.rs.time [rd.rs.amount] = rate.time;
    rd.rs.open [rd.rs.amount] = rate.open;
    rd.rs.high [rd.rs.amount] = rate.high;
    rd.rs.low  [rd.rs.amount] = rate.low;
    rd.rs.close[rd.rs.amount] = rate.close;
    rd.rs.tick_volume[rd.rs.amount] = rate.tick_volume;
    ++rd.rs.amount;
    return (0);
}

void releaseRates(RatesData& rd) {
    delete [] reinterpret_cast<char*>(rd.rs.time);
    memset(&rd.rs, 0, sizeof(rd.rs));
    rd.data.clear();
}

void releaseRates(RatesData* rd) {
    delete [] reinterpret_cast<char*>(rd->rs.time);
    memset(&rd->rs, 0, sizeof(rd->rs));
    rd->data.clear();
}

void releaseRatesFromMap() {
    for(auto &iter : mapRatesData) {
        releaseRates(iter.second);
        delete iter.second;
    }
    mapRatesData.clear();
}


RatesData* getSymbol(MARKETID market, string& symbol_name, ENUM_TIMEFRAMES tf) {
    string key;
    MapRatesData::iterator iter = mapRatesData.find(genSymbolKey(market, symbol_name, tf, key));
    return iter->second;
    //if (iter == mapRatesData.end())
    //    return (0);
    //else
    //    return iter->second;
}

inline string& genSymbolKey(MQL4::SYMBOL &symbol, std::string &key) {
    stringstream ss;
    ss << symbol.market << "|" << symbol.symbol_name << "|" << symbol.period;
    ss >> key;
    return key;
}

inline string &genSymbolKey(MARKETID market, string& symbol_name, ENUM_TIMEFRAMES tf,string& key) {
    stringstream ss;
    ss << market << "|" << symbol_name << "|" << tf;
    ss >> key;
    return key;
}


RatesData* getSymbol(std::string &key) {
    MapRatesData::iterator iter = mapRatesData.find(key);
    return iter->second;
    //if (iter == mapRatesData.end())
    //    return (0);
    //else
    //    return iter->second;
}


} //namespace MQL4

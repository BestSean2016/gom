#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include "mql4-data.h"
#include "datetime.h"

namespace MQL4 {

//global data
MapRatesData mapRatesData;


//
// structMqlRates
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




//
// class RatesData
//

RatesData::RatesData() { }
RatesData::~RatesData() {}

/* initial data */
int RatesData::read_forex_csv(MARKETID market, const char* csvfile) {
    int result = ERR_UNKONW_MARKET;
    switch((int)market) {
    case MARKET_FOREX_FURTURES:
        result = get_forex_furtures_(csvfile);
        break;
    }

    return result;
}


//forex
//date,      time, open,   high,   low,    close,  volume
//2016.04.08,16:22,108.600,108.601,108.551,108.555,86
//

int RatesData::get_forex_rates_data__(MqlRates& rate, const string& str) {
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

int RatesData::get_forex_furtures_(const char* csvfile) {
    string str(csvfile);

    size_t found = str.rfind(CHAR_PATH_SPERATOR);
    string symbol_full = str.substr(found + 1, str.length() - found -1);
    //cout << symbol_full << endl;

    //get symbol and period
    size_t i = 0;
    while(i < symbol_full.size() && !isdigit(symbol_full[i])) ++i;
    if (i == symbol_full.length()) return ERR_ERROR_FOREX_FILEPATH;

    symbol.market = MARKET_FOREX_FURTURES;
    symbol.symbol_name = symbol_full.substr(0, i);
    symbol.period = (ENUM_TIMEFRAMES)atoi(symbol_full.substr(i, symbol_full.length() - i).c_str());
    genSymbolKey(MARKET_FOREX_FURTURES, symbol.symbol_name, symbol.period, key_);
    //
    //TO DO: check the rd.et is valid
    //

    //read data
    std::ifstream fin(csvfile);
    while(getline(fin, str)) {
        MqlRates rate;
        if (get_forex_rates_data__(rate, str))
            break;
        data.push_back(rate);
    }

    serializateRates(data.size());

    //cout << rd.et << ',' << rd.symbol << endl;
    return (0);
}


int RatesData::serializateRates(size_t newDataAmount) {
    rs.size   = data.size() + newDataAmount;
    rs.amount = data.size();
    /*
    datetime * time;         // Period start time
    double   * open;         // Open price
    double   * high;         // The highest price of the period
    double   * low;          // The lowest price of the period
    double   * close;        // Close price
    ulong    * tick_volume;  // Tick volume
    */

    rs.time  = reinterpret_cast<datetime*>(new char[
        (sizeof(datetime) + 4 * sizeof(double) + sizeof(ulong)) * rs.size]);
    if (!rs.time) return ERR_OUT_OF_MEMORY;
    rs.open  = reinterpret_cast<double*>(rs.time + rs.size);
    rs.high  = rs.open + rs.size;
    rs.low   = rs.high + rs.size;
    rs.close = rs.low  + rs.size;
    rs.tick_volume = reinterpret_cast<ulong*>(rs.close + rs.size);

    struct numeric_limits<double> nl;
    rs.statPrice.min = rs.statVolume.min =
            rs.statPriceDelta.min = rs.statVolumeDelta.min = nl.max();
    rs.statPrice.max = rs.statVolume.max = rs.statPriceDelta.max =
            rs.statVolumeDelta.max = rs.statVolumeDelta.max = nl.min();
    rs.statPrice.count = rs.statVolume.count
            = rs.statPriceDelta.count = rs.statVolumeDelta.count = data.size();

    double sumPrice = 0, sumVolume = 0, sumPriceDelta = 0, sumVolumeDelta = 0;
    double priceDelta = 0, volumeDelta = 0;

    for (size_t i = 0; i < rs.statPrice.count; ++i) {
        rs.open[i]  = data[i].open ,
        rs.close[i] = data[i].close,
        rs.open[i]  = data[i].open ,
        rs.high[i]  = data[i].high ,
        rs.low[i]   = data[i].low  ,
        rs.time[i]  = data[i].time ,
        rs.tick_volume[i] = data[i].tick_volume;

        sumPrice += rs.close[i];
        sumVolume += rs.tick_volume[i];
        rs.statPrice.max = max(rs.statPrice.max, rs.close[i]);
        rs.statPrice.min = min(rs.statPrice.min, rs.close[i]);
        rs.statVolume.max = max(rs.statVolume.max, static_cast<double>(rs.tick_volume[i]));
        rs.statVolume.min = min(rs.statVolume.min, static_cast<double>(rs.tick_volume[i]));

        if (i > 0) {
            priceDelta = rs.close[i] - rs.close[i - 1];
            sumPriceDelta += priceDelta;
            volumeDelta = static_cast<double>(static_cast<int>(rs.tick_volume[i])
                                              - static_cast<int>(rs.tick_volume[i - 1]));
            sumVolumeDelta += volumeDelta;

            rs.statPriceDelta.max = max(rs.statPriceDelta.max, priceDelta);
            rs.statPriceDelta.min = min(rs.statPriceDelta.min, priceDelta);
            rs.statVolumeDelta.max = max(rs.statVolumeDelta.max, volumeDelta);
            rs.statVolumeDelta.min = min(rs.statVolumeDelta.min, volumeDelta);
        }
    }

    rs.statPrice.mean  = sumPrice  / static_cast<double>(rs.statPrice.count);
    rs.statVolume.mean = sumVolume /static_cast<double>(rs.statVolume.count);
    rs.statPriceDelta.mean  = sumPriceDelta / static_cast<double>(rs.statPrice.count - 1);
    rs.statVolumeDelta.mean = sumVolumeDelta / static_cast<double>(rs.statPrice.count - 1);

    sumPrice = sumVolume = sumPriceDelta = sumVolumeDelta = 0;
    for (uint i = 0; i < rs.statPrice.count; ++i) {
         sumPrice += (rs.close[i] - rs.statPrice.mean) * (rs.close[i] - rs.statPrice.mean);
        sumVolume += (static_cast<double>(rs.tick_volume[i]) - rs.statVolume.mean)
                * (static_cast<double>(rs.tick_volume[i]) - rs.statVolume.mean);

        if (i > 0) {
            priceDelta = rs.close[i] - rs.close[i - 1];
            volumeDelta = static_cast<double>(static_cast<int>(rs.tick_volume[i])
                                              - static_cast<int>(rs.tick_volume[i - 1]));


            sumPriceDelta += (priceDelta - rs.statPriceDelta.mean)
                    * (priceDelta - rs.statPriceDelta.mean);
            sumVolumeDelta += (volumeDelta - rs.statVolumeDelta.mean)
                    * (volumeDelta - rs.statVolumeDelta.mean);
        }
    }

    rs.statPrice.var   = sumPrice / static_cast<double>(rs.statPrice.count - 1);
    rs.statPrice.stdv  = sqrt(rs.statPrice.var);
    rs.statVolume.var  = sumVolume / static_cast<double>(rs.statPrice.count - 1);
    rs.statVolume.stdv = sqrt(rs.statVolume.var);
    rs.statPriceDelta.var = sumPriceDelta / static_cast<double>(rs.statPrice.count - 2);
    rs.statPriceDelta.stdv = sqrt(rs.statPriceDelta.var);
    rs.statVolumeDelta.var = sumVolumeDelta / static_cast<double>(rs.statVolume.count - 2);
    rs.statVolumeDelta.stdv = sqrt(rs.statVolumeDelta.var);

    return (0);
}

int RatesData::reates_to_tick(TickData& td) {
    td.symbol = symbol.symbol_name;
    td.market = symbol.market;
    for (auto& p : data) {
        MqlTick mt;
        mt.bid[0] = mt.ask[0] = mt.last = p.open,
                mt.bid_volume[0] = mt.ask_volume[0] = mt.last_volume = p.tick_volume,
                mt.time = p.time;
        td.data.push_back(mt);
    }

    return (0);
}

int RatesData::addRateData(MqlRates& rate) {
    if (rs.amount + 1 > rs.size) return ERR_OUT_OF_BUFFER;
    data.push_back(rate);
    rs.time [rs.amount] = rate.time;
    rs.open [rs.amount] = rate.open;
    rs.high [rs.amount] = rate.high;
    rs.low  [rs.amount] = rate.low;
    rs.close[rs.amount] = rate.close;
    rs.tick_volume[rs.amount] = rate.tick_volume;
    ++rs.amount;
    return (0);
}

void RatesData::releaseData() {
    delete [] reinterpret_cast<char*>(rs.time);
    ::memset(&rs, 0, sizeof(rs));
    data.clear();
}


bool RatesData::is_new_rates_(ENUM_TIMEFRAMES period, datetime rates_time, datetime tick_time) {
    return (tick_time - rates_time >= period * 60);
}

void RatesData::addRateData_(MqlTick& tick) {
    MqlRates rates;
    rates.close = rates.high = rates.low = rates.open = tick.last;
    rates.tick_volume = tick.last_volume;
    rates.time = tick.time;
    addRateData(rates);
}

void RatesData::update_rate_(MqlRates& rates, MqlTick& tick) {
    rates.high  = max(rates.high, tick.last);
    rates.low   = min(rates.low , tick.last);
    rates.close = tick.last;
    rates.tick_volume += tick.last_volume;
}

void RatesData::addNewTick(MqlTick& tick) {
     MqlRates &rates = data[data.size() - 1];
     if (is_new_rates_(symbol.period, rates.time, tick.time))
         addRateData_(tick);
     else
         update_rate_(rates, tick);
}



//
// class map <--> rates data
//



MapRatesData::MapRatesData() {}
MapRatesData::~MapRatesData() {}

int MapRatesData::get_forex_data(const char* path) {
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
                rd->read_forex_csv(MARKET_FOREX_FURTURES, filepath.c_str());
                map_.insert(std::pair<string, RatesData*>(rd->key_, rd));
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

    return (0);
}

void MapRatesData::releaseRatesFromMap() {
    for(auto &iter : map_) {
        iter.second->releaseData();
        delete iter.second;
    }
    map_.clear();
}

size_t MapRatesData::size() {
    return map_.size();
}


RatesData* MapRatesData::getSymbol(MARKETID market, string& symbol_name, ENUM_TIMEFRAMES tf) {
    string key;
    MAP_RATES_DATA::iterator iter = map_.find(genSymbolKey(market, symbol_name, tf, key));
    return iter->second;
    //if (iter == mapRatesData.end())
    //    return (0);
    //else
    //    return iter->second;
}

RatesData* MapRatesData::getSymbol(std::string &key) {
    MAP_RATES_DATA::iterator iter = map_.find(key);
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

ostream& operator<< (ostream& out, TickVector vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        out << vec[i].time << ", "
            << vec[i].last << ", "
            << vec[i].bid[0] << ", "
            << vec[i].ask[0] << ", "
            << vec[i].last_volume << ", "
            << vec[i].bid_volume[0] << ", "
            << vec[i].ask_volume[0] << std::endl;
    }

    return out;
}

} //namespace MQL4

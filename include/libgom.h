#ifndef __LIBRARAY_GOD_OF_MONEY_H_INCLUDE__
#define __LIBRARAY_GOD_OF_MONEY_H_INCLUDE__

#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>

#include "mql4-def.h"


namespace MQL4 {

extern int getopt(int nargc, char* const *nargv, const char *ostr);
extern int read_forex_csv(RatesData& rd, MARKETID market, const char* csvfile);

} //namespace MQL4

#endif //__LIBRARAY_GOD_OF_MONEY_H_INCLUDE__

#include "Checkup.h"
#include "mql4-def.h"
#include "mql4-data.h"
#include "Tradeing.h"

namespace MQL4 {

int _LastError = 0;

int  GetLastError() {
    int e = _LastError;
    _LastError = 0;
    return e;
}

string  Symbol() {
    if (!gSelectedData)
        return "";
    else
        return gSelectedData->symbol.symbol_name;
}

double  Point() {
    double v = gSelectedData->data[1].close;
    double iv, p = 1;

    do {
        v *= p;
        iv = static_cast<double>(static_cast<ulong>(v));
        p *= 10;
    }while(fabs(v - iv) > 0.000001);

    return p;
}

} //namespace MQL4

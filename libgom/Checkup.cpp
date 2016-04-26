#include "Checkup.h"

namespace MQL4 {

int _LastError = 0;

int  GetLastError() {
    int e = _LastError;
    _LastError = 0;
    return e;
}

string  Symbol() {
    return "";
}

double  Point() {
    return (0);
}

} //namespace MQL4

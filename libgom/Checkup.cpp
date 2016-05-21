#include "Checkup.h"
#include "mql4-def.h"
#include "mql4-data.h"
#include "indicator.h"
#include "Tradeing.h"

namespace MQL4 {

int _LastError = 0;

int GetLastError() {
  int e = _LastError;
  _LastError = 0;
  return e;
}

bool IsTradeAllowed(string symbol, datetime tested_time) {
  (void)symbol;
  (void)tested_time;
  return true;
}

}  // namespace MQL4

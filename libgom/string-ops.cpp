#include "string-ops.h"

namespace MQL4 {

string StringSetChar(
   string    string_var,       // string
   int       pos,              // position
   ushort    value             // char code
   )
{
    string_var[pos] = (char)value;
    return string_var;
}

} //namespace MQL4

#ifndef STRINGOPS_H
#define STRINGOPS_H

#include <string>
using namespace std;

/*
StringAdd
StringBufferLen
StringCompare
StringConcatenate
StringFill
StringFind
StringGetCharacter
StringInit
StringLen
StringReplace
StringSetCharacter
StringSplit
StringSubstr
StringToLower
StringToUpper
StringTrimLeft
StringTrimRight
StringGetChar
StringSetChar
*/
namespace MQL4 {

/**
 * @brief StringSetChar Returns the string copy with changed character in the specified position.
 * If the value of pos parameter is less than string length and char code = 0, the string will be
 * truncated (to position, equal to pos). If the value of pos parameter is equal to string lenth,
 * the specified symbol will be added to the end of the string and string length will be increased by 1.
 * @param string_var [in]  Source string.
 * @param pos [in] The character position in the string. Can be from 0 to StringLen(text).
 * @param value [in]  New char ASCII-code.
 * @return The string copy with changed character in the specified position.
 */
extern string StringSetChar(
   string    string_var,       // string
   int       pos,              // position
   ushort    value             // char code
   );

} //namespace MQL4

#endif // STRINGOPS_H

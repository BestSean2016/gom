#ifndef MATH_H
#define MATH_H

#include <math.h>

namespace MQL4 {

/**
 * @brief MathAbs The function returns the absolute value (modulus) of the specified numeric value.
 * @param value
 * @return Value of double type more than or equal to zero.
 */
extern double  MathAbs(
   double  value      // numeric value
   );

/**
 * @brief MathFloor The function returns integer numeric value closest from below.
 * @param val [in]  Numeric value.
 * @return A numeric value representing the largest integer that is less than or equal to val.
 */
extern double  MathFloor(
   double  val     // number
   );


/**
 * @brief MathRound The function returns a value rounded off to the nearest integer of the specified numeric value.
 * @param value [in]  Numeric value before rounding.
 * @return Value rounded till to the nearest integer.
 */
extern double  MathRound(
   double  value      // value to be rounded
   );


extern double MathArccos       (double value);
extern double MathArcsin       (double value);
extern double MathArctan       (double value);
extern double MathCeil         (double value);
extern double MathCos          (double value);
extern double MathExp          (double value);
extern double MathLog          (double value);
extern double MathLog10        (double value);
extern double MathMax          (double value1, double value2);
extern double MathMin          (double value1, double value2);
extern double MathMod          (double value, double value2);
extern double MathPow          (double base, double exponent);
extern double MathRand         ();
extern double MathSin          (double value);
extern double MathSqrt         (double value);
extern void   MathSrand(unsigned int seed);
extern double MathTan          (double value);
extern bool   MathIsValidNumber(double value);


} //namespace MQL4

#endif // MATH_H

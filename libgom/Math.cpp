#include "stderror-mql4.h"
#include "stdlib-mql4.h"
#include "Math.h"

namespace MQL4 {

double  MathAbs(
   double  value      // numeric value
   ) {
    return fabs(value);
}


double  MathFloor(
   double  val     // number
   ) {
    return floor(val);
}

//The function returns a value rounded off to the nearest integer of the specified numeric value.
double  MathRound(
   double  value      // value to be rounded
   ) {
    return round(value);
}

double MathArccos       (double value) {return acos(value);}
double MathArcsin       (double value) {return asin(value);}
double MathArctan       (double value) {return atan(value);}
double MathCeil         (double value) {return ceil(value);}
double MathCos          (double value) {return cos(value);}
double MathExp          (double value) {return exp(value);}
double MathLog          (double value) {return log(value);}
double MathLog10        (double value) {return log10(value);}
double MathMax          (double value1, double value2) {return fmax(value1, value2);}
double MathMin          (double value1, double value2) {return fmin(value1, value2);}
double MathMod          (double value1, double value2) {return fmod(value1, value2);}
double MathPow          (double base, double exponent) {return pow(base, exponent);}
double MathRand         () {return rand();}
double MathSin          (double value) {return sin(value);}
double MathSqrt         (double value) {return sqrt(value);}
void   MathSrand        (unsigned int seed) {srand(seed);}
double MathTan          (double value) {return tan(value);}
bool   MathIsValidNumber(double value) {return (bool)isnan(value);}

} //namespace MQL4

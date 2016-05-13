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


bool   MathBasicStatistics(const double* value, const uint count, BASIC_STATISTICS& statistics) {
    if (!value || !count) return false;
    struct numeric_limits<double> nl;
    statistics.min = nl.max();
    statistics.max = nl.min();
    statistics.count = count;

    double sum = 0;
    for (uint i = 0; i < count; ++i) {
        sum += value[i];
        statistics.min = min(statistics.min, value[i]);
        statistics.max = max(statistics.max, value[i]);
    }

    statistics.mean = sum / static_cast<double>(count);

    sum = 0;
    for (uint i = 0; i < count; ++i)
        sum += ((value[i] - statistics.mean) * (value[i] - statistics.mean));

    statistics.var  = sum / static_cast<double>(count - 1);
    statistics.stdv = sqrt(statistics.var);

    return true;
}


void MathGaussianNoise(double mu, double sigma, double *array, size_t n)
{
    const double epsilon = std::numeric_limits<double>::min();
    const double two_pi = 2.0*3.14159265358979323846;

    double u1, u2;

    double* ptr = array;
    for (size_t i = 0; i < n; ++i, ++ptr) {
        do {
           u1 = rand() * (1.0 / RAND_MAX);
           u2 = rand() * (1.0 / RAND_MAX);
        } while ( u1 <= epsilon );

        *ptr = (sqrt(-2.0 * log(u1)) * cos(two_pi * u2)) * sigma + mu;
    }
}

void MathGaussianNoise2(double mu, double sigma, double* v1, double* v2) {
    const double epsilon = std::numeric_limits<double>::min();
    const double two_pi = 2.0*3.14159265358979323846;

    double u1, u2;

    do {
       u1 = rand() * (1.0 / RAND_MAX);
       u2 = rand() * (1.0 / RAND_MAX);
    } while ( u1 <= epsilon );

    *v1 = (sqrt(-2.0 * log(u1)) * cos(two_pi * u2)) * sigma + mu;
    *v2 = (sqrt(-2.0 * log(u1)) * sin(two_pi * u2)) * sigma + mu;
}



} //namespace MQL4

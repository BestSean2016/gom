#ifndef MATH_H
#define MATH_H

#include <sys/types.h>
#include <limits>
#include <math.h>
#include <iostream>

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


typedef struct BASIC_STATISTICS {
    size_t count;
    double mean;
    double var;
    double stdv;
    double min;
    double max;
}BASIC_STATISTICS;

template<class T>
bool   MathBasicStatistics(const T* value, const uint count, BASIC_STATISTICS& statistics) {
    if (!value || !count) return false;
    struct numeric_limits<double> nl;
    statistics.min = nl.max();
    statistics.max = nl.min();
    statistics.count = count;

    double sum = 0;
    for (uint i = 0; i < count; ++i) {
        sum += static_cast<double>(value[i]);
        statistics.min = min(statistics.min, static_cast<double>(value[i]));
        statistics.max = max(statistics.max, static_cast<double>(value[i]));
    }

    statistics.mean = sum / static_cast<double>(count);

    sum = 0;
    for (uint i = 0; i < count; ++i)
        sum += (static_cast<double>(value[i]) - statistics.mean)
             * (static_cast<double>(value[i]) - statistics.mean);

    statistics.var  = sum / static_cast<double>(count - 1);
    statistics.stdv = sqrt(statistics.var);

    return true;
}


extern void   MathGaussianNoise(double mu, double sigma, double* array, size_t n);
extern void   MathGaussianNoise2(double mu, double sigma, double* v1, double* v2);
template<class T>
void MathGaussianNoise3(T* v, double mu, double sigma, size_t n = 3) {
    const double epsilon = std::numeric_limits<double>::min();
    const double two_pi = 2.0*3.14159265358979323846;
    double u1, u2;
    (void)n;

    for (size_t i = 0; i < n; ++i) {
        do {
           u1 = rand() * (1.0 / RAND_MAX);
           u2 = rand() * (1.0 / RAND_MAX);
        } while ( u1 <= epsilon );
        v[i] = static_cast<T>((sqrt(-2.0 * log(u1)) * sin(two_pi * u2)) * sigma + mu);
    }
}

} //namespace MQL4

#endif // MATH_H

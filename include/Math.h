#ifndef MATH_H
#define MATH_H

#include <sys/types.h>
#include <limits>
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


typedef struct BASIC_STATISTICS {
    size_t count;
    double mean;
    double var;
    double stdv;
    double min;
    double max;
}BASIC_STATISTICS;

extern bool   MathBasicStatistics(const double* value, const uint count, BASIC_STATISTICS& statistics);

extern void   MathGaussianNoise(double mu, double sigma, double* array, size_t n);
extern void   MathGaussianNoise2(double mu, double sigma, double* v1, double* v2);
template<class T>
void MathGaussianNoise3(T* v, double mu, double sigma, size_t n = 3) {
    const double epsilon = std::numeric_limits<double>::min();
    const double two_pi = 2.0*3.14159265358979323846;
    double u1, u2;
    (void)n;

    do {
       u1 = rand() * (1.0 / RAND_MAX);
       u2 = rand() * (1.0 / RAND_MAX);
    } while ( u1 <= epsilon );

    v[0] = static_cast<T>((sqrt(-2.0 * log(u1)) * cos(two_pi * u2)) * sigma + mu);
    v[1] = static_cast<T>((sqrt(-2.0 * log(u1)) * sin(two_pi * u2)) * sigma + mu);

    do {
       u1 = rand() * (1.0 / RAND_MAX);
       u2 = rand() * (1.0 / RAND_MAX);
    } while ( u1 <= epsilon );

    v[2] = static_cast<T>((sqrt(-2.0 * log(u1)) * cos(two_pi * u2)) * sigma + mu);
}

} //namespace MQL4

#endif // MATH_H

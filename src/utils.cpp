//
// Created by francis on 10/16/19.
//

#include "utils.h"
#include "main.h"
#include <functional>
#include <cassert>


/**
 * @return x^n
 */
long double pow_(long double x, unsigned int n) {
    if (n == 0) return 1.0;
    if (n == 1) return x;
    if (n % 2 == 0) {
        long double x_to_the_n_over_2 = pow_(x, n / 2);
        return x_to_the_n_over_2 * x_to_the_n_over_2;
    } else {
        return x * pow_(x, n - 1);
    }
}

static long double log_series_term(long double x, unsigned int k) {
    //log(x) = - sum_(k=1)^∞ ((-1)^k (-1 + x)^k)/k for abs(-1 + x)<1
    int sign = (k % 2 == 0) ? -1 : 1;
    return sign * pow_(-1.0 + x, k) / ((double) k);
}

/**
 * between 0.5 and 1.5 Mathematica says this is accurate to +/- 10^-32.
 * between 0.9 and 1.1 Mathematica says this is accurate to +/- 10^-102.
 * @param in an input between 0.5 and 1.5
 * @return the log base e of in
 */
static long double log_e_series_at_1(long double in) {
    static const unsigned int MAX_LOG_SERIES = 100;
    auto f = std::bind(log_series_term, in, std::placeholders::_1); // NOLINT(modernize-avoid-bind)
    return sum(f, 1.0, MAX_LOG_SERIES);
}

long double log_e(long double in) {
    static const long double LOG_E_2 = 0.693147180559945309417232121458176568075500134360255254120L;
    static const long double Log_E_1_05= 0.048790164169432003065374404223164658607973664415582410040L;
    assert(in > 0.0);
    if (0.9 < in && in < 1.1) {
        return log_e_series_at_1(in);
    } else if (in < 1.0) {
        return -log_e(1.0 / in);
    } else if (in < 2) {
        return Log_E_1_05 + log_e(in/1.05);
    } else {
        return LOG_E_2 + log_e(in/2.0);
    }
}

unsigned long factorial(unsigned long k){
    if(k == 0) return 1;
    return k*factorial(k - 1);
}

static long double exp_series_term(long double x, unsigned int k) {
    //todo optimization, avoid recalculating whole factorial every time
    return pow_(x, k) / ((double)factorial(k));
}


/**
 * between -1.0 and 1.0 Mathematica says this is accurate to +/- 10^-83, with 60 terms.
 */
long double exp_series(long double in){
    assert(-1.0 < in && in < 1.0);
    static const unsigned int MAX_LOG_SERIES = 60;
    auto f = std::bind(exp_series_term, in, std::placeholders::_1); // NOLINT(modernize-avoid-bind)
    return sum(f, 0, MAX_LOG_SERIES);
}

/**
 * Implements e^x
 * @param in x
 * @return e^x.
 */
long double exp_(long double in){
    if(in < 0.0){
        return 1.0 / exp_(-in);
    } else {
        if(in < 1.0){
            return exp_series(in);
        }
        long double recurse = exp_(in / 2.0);
        return recurse * recurse;
    }
}


/**
 * Calculates a^b
 */
long double pow_(long double a, long double b){
    if(a > -0.000001 && a < 0.000001){
        a = 0.000001;
    }
    assert(a > 0.0);
    return exp_(log_e(a) * b);
}

long double abs_(long double in){
    if( in < 0) return -in;
    else return in;
}

long double clamp_abs(long double to_clamp, long double clamp){
    if(abs_(to_clamp) > abs_(clamp)){
        return (to_clamp > 0 ? 1 : -1)*clamp;
    }else {
        return to_clamp;
    }
}
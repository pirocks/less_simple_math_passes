#include <cassert>
#include "main.h"
#include "utils.h"

/**
 * A basic summation function. Uses long double, to attempt to avoid rounding errors.
 * @param terms a function which returns the value of the sums's terms given an index
 * @param start A start index
 * @param end A end index
 * @return sum from start to end, inclusive of start and exclusive of end
 */
double sum(const std::function<double(unsigned int)> &terms, unsigned int start, unsigned int end) {
    long double sum = 0.0;
    for (unsigned i = start; i < end; ++i) {
        sum += terms(i);
    }
    return (double) sum;
}

/**
 * Implements factorial of an integer, by taking the log of the factorial, to convert into a summation problem. 
 * Should work in cases where traditional implementations integer overflow, though of course is still very unnecesarily complex
 * @param in 
 * @return 
 */
double complicated_factorial(unsigned int in) {
    return (double) exp_(sum([](unsigned int x) {
        return log_e((double) x);
    }, 1, in + 1));
}

static const int MAX_GAMMA_UPPER_BOUND = 10000;//should be well past double overflow for inputs that could cause a bound larger than this

long double gamma_integrand(long double x, long double n) {
    assert(x < MAX_GAMMA_UPPER_BOUND);
    return pow_(x, n) * exp_(-x);
}


/**
 * Implements the gamma function(shifted by one so that behavior is consistent with factorial), for positive double inputs(if your really lucky it might work for negative inputs too.).
 * @param in 
 * @return 
 */
double very_complicated_factorial(double in) {
//	x^n e^-x
    long double current_total = 0.0;
    long double prev_x = +0.0;
    bool increasing = true;
    long double SUM_INCREMENT_SIZE = 0.1;
    while (increasing) {
        long double current_x = prev_x + SUM_INCREMENT_SIZE;
        long double prev = gamma_integrand(prev_x, in);
        long double current = gamma_integrand(current_x, in);
        const long double diff = SUM_INCREMENT_SIZE * (prev + current) / 2.0;
        const double GAMMA_PERCENT_CHANGE_THRESHOLD = 0.01;
        if (diff / current_total > GAMMA_PERCENT_CHANGE_THRESHOLD) {
            SUM_INCREMENT_SIZE /= 2.0;
        }
        if (diff / current_total < (GAMMA_PERCENT_CHANGE_THRESHOLD/10.0)) {
            SUM_INCREMENT_SIZE *= 2.0;
        }
        current_total += diff;
        increasing = prev < current;
        prev_x = current_x;
    }

    bool decreasing = true;
    while ((prev_x + SUM_INCREMENT_SIZE) < MAX_GAMMA_UPPER_BOUND) {
        long double current_x = prev_x + SUM_INCREMENT_SIZE;
        const double GAMMA_PERCENT_CHANGE_THRESHOLD = 1.0001;
        long double diff = (current_x - prev_x) * (gamma_integrand(prev_x, in) + gamma_integrand(current_x, in)) / 2.0;
        if (diff / current_total > GAMMA_PERCENT_CHANGE_THRESHOLD) {
            SUM_INCREMENT_SIZE /= 2.0;
        }
        if (diff / current_total < (GAMMA_PERCENT_CHANGE_THRESHOLD/10.0)) {
            SUM_INCREMENT_SIZE *= 2.0;
        }
        current_total += diff;
        decreasing = gamma_integrand(prev_x, in) > gamma_integrand(current_x, in);
        assert(decreasing);
        prev_x = current_x;
    }

    return (double) current_total;
}

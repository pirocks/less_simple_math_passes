#ifndef SAMPLE_PROJECTS_MAIN_H
#define SAMPLE_PROJECTS_MAIN_H
#include <functional>
#include <utility>

double sum(const std::function<double(unsigned int)> &terms, unsigned int start, unsigned int end);
double complicated_factorial(unsigned int in);
double very_complicated_factorial(double in);

#endif //SAMPLE_PROJECTS_MAIN_H

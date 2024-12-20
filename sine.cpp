/*


This program will approximate sin(x)
in parallel using OpenMP.


*/

#include "sine.h"
#include <cmath>
#include <omp.h>
using namespace std;

#define NUM_TERMS 100

double parallelSine(double x) {

    double result = 0.0;

    #pragma omp parallel for reduction(+:result)
    for (int i = 0; i < NUM_TERMS; i++) {
        double term = pow(-1, i) * pow(x, 2*i+1) / tgamma(2*i+2);
        result += term;
    }

    return result;

}
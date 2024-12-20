#include "cosine.h"
#include <cmath>

#define NUM_TERMS 100

double parallelCosine(double x) {

    double result = 1;
    double term = 1;
    double xSquared = pow(x, 2);

    #pragma omp parallel for reduction(+:result)
    for (int n = 1; n < NUM_TERMS; n++) {
        term *= -xSquared / (2*n*(2*n-1));
        result += term;
    }

    return result;
}
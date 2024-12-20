#include "tan.h"
#include <string>

double parallelTan(double x) {
    double sin = parallelSine(x);
    double cos = parallelCosine(x);

    if (cos == 0)
        throw std::string("Error: Cannot compute tan when cos(x) = 0");

    return sin/cos;
}
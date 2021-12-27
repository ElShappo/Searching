#include "epsilon.h"

double machineEpsilon(float EPS)
{
    float prev_epsilon;

    while ((1+EPS) != 1)
    {
        prev_epsilon = EPS;
        EPS /=2;
    }
    return EPS;
}

bool areSame(double a, double b)
{
    return fabs(a - b) < machineEpsilon(a);
}

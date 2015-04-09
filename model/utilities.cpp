#include <cmath>
#include "model/utilities.hpp"
#include "model/point.hpp"

bool utilities::secondDegreeEquationSolver(double a, double b, double c,
                                           double * rad1, double * rad2)
{
    double delta = std::pow(b, 2.) - (4. * a * c);
    bool thereIsRadix = (delta >= 0);

    if (thereIsRadix)
    {
        *rad1 = (-b - std::sqrt(delta))/(2. * a);
        *rad2 = (-b + std::sqrt(delta))/(2. * a);
    }

    return thereIsRadix;
}

double utilities::angleAsDegree(const double alpha)
{
    return ((alpha * 180.) / utilities::PI);
}

double utilities::angleAsDegree0to360(const double alpha)
{
    return std::fmod(std::fmod(utilities::angleAsDegree(alpha), 360.) + 360.,
                     360.);
}

bool utilities::equals(const double nb1, const double nb2, const double epsilon)
{
    return (std::abs(nb1 - nb2) < epsilon);
}

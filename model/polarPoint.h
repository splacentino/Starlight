#ifndef POLARCOORDINATE_HPP
#define POLARCOORDINATE_HPP
#include<model/point.h>
#include<ostream>
#include<string>

class PolarPoint
{
    double radius;
    double beta;

public:
    PolarPoint();
    PolarPoint(double, double);
    PolarPoint(Point &);
    PolarPoint(PolarPoint &);
    ~PolarPoint();

    int getRadius() const;
    double getBeta() const;
    Point toCartesian();
    PolarPoint & rotate(double);
    std::string toString() const;

    friend std::ostream & operator<<(std::ostream &, PolarPoint &);
};

#endif // POLARCOORDINATE_HPP

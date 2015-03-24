#ifndef REACTABLE_HPP
#define REACTABLE_HPP
#include "ray.h"

class Reactable
{

public:

    virtual void reactToRay(Ray &) = 0;
    virtual bool includePoint(Point &) = 0;

};

#endif // REACTABLE_HPP
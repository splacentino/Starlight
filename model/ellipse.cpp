#include "ellipse.hpp"

Ellipse::Ellipse(int xRadius, int yRadius) : xRadius{xRadius}, yRadius{yRadius} {}

int Ellipse::getXRadius() const
{
    return this->xRadius;
}

int Ellipse::getYRadius() const
{
    return this->yRadius;
}
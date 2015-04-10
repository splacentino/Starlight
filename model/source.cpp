#include "model/source.hpp"

#include "model/starlightexception.hpp"
#include "model/ray.hpp"
#include "model/point.hpp"
#include "model/geometry/utilities.hpp"

Source::Source() : Rectangle{20, 20, Point{0, 0}}, alpha{10}, waveLength{400}{}

Source::Source(const Point & position, const int edge, const double alpha,
               const int waveLength)
    : Rectangle(edge, edge, position), alpha{alpha}, waveLength{waveLength}
{
    if (waveLength < Ray::WL_MIN || waveLength > Ray::WL_MAX)
        throw StarlightException("Mauvaise longueur d'onde");
}

const Point & Source::getPosition() const
{
    return this->upLeftCorner;
}

double Source::getAngle() const
{
    return this->alpha;
}

int Source::getEdge() const
{
    return this->width;
}

int Source::getWaveLength() const
{
    return this->waveLength;
}

bool Source::isOn() const
{
    return this->on;
}

void Source::setOn(const bool on)
{
    this->on = on;
}

bool Source::operator==(const Source & source) const
{
    return this->on == source.on
            && this->waveLength == source.waveLength
            && utilities::equals(this->alpha, source.alpha)
            && Rectangle::operator ==(source);
}

bool Source::operator!=(const Source & source) const
{
    return !(*this == source);
}

Source & Source::operator =(const Source & source)
{
    this->on = source.on;
    this->alpha = source.alpha;
    this->waveLength = source.waveLength;
    Rectangle::operator =(source);

    return *this;
}

std::ostream & operator<<(std::ostream & out, const Source & source)
{
    out << "Source --- Position : " << source.getPosition()
        << " , Angle : " << source.getAngle()
        << "Frequency : " << source.getWaveLength()
        << " , Edge : " << source.getEdge()
        << " , on : " << source.isOn();

    return out;
}

#ifdef _WINT32
#include <windows.h>
#else
#include <X11/Xlib.h>
#endif

#include <string>
#include "level.hpp"
#include "crystal.hpp"
#include "dest.hpp"
#include "lens.hpp"
#include "mirror.hpp"
#include "ray.hpp"
#include "source.hpp"
#include "wall.hpp"
#include "point.hpp"
#include "nuke.hpp"
#include "starlightexception.hpp"

using namespace std;

Level::Level(const int width, const int height)
{
    if(width <= 0)
        throw new StarlightException("Hauteur doit être strict. positive");

    if(height <= 0)
        throw new StarlightException("Largeur doit être strict. positive");

    this->width = width;
    this->height = height;
    this->walls = { Wall{Point{0, 0}, Point{0, height}},
                    Wall{Point{0, height}, Point{width, height}},
                    Wall{Point{width, height}, Point{width, 0}},
                    Wall{Point{width, 0}, Point{0, 0}} };
}

const Source & Level::getSource() const
{
    return this->source;
}

void Level::setSource(const Source & source)
{
    this->source = source;
}

const Dest & Level::getDestination() const
{
    return this->dest;
}

void Level::setDestination(const Dest & dest)
{
    this->dest = dest;
}

const vector<Wall> & Level::getWalls() const
{
    return this->walls;
}

void Level::addWall(const Wall & wall)
{
    this->walls.push_back(wall);
}

const vector<Mirror> & Level::getMirrors() const
{
    return this->mirrors;
}

void Level::addMirror(const Mirror & mirror)
{
    this->mirrors.push_back(mirror);
}

const vector<Crystal> & Level::getCrystals() const
{
    return this->crystals;
}

void Level::addCrystal(const Crystal & crystal)
{
    this->crystals.push_back(crystal);
}

const vector<Lens> & Level::getLenses() const
{
    return this->lenses;
}

void Level::addLens(const Lens & lens)
{
    this->lenses.push_back(lens);
}

const vector<Ray> & Level::getRays() const
{
    return this->rays;
}

void Level::setRays(const vector<Ray> & rays)
{
    this->rays = rays;
}

const std::vector<Nuke> & Level::getNukes() const
{
    return this->nukes;
}

void Level::addNuke(const Nuke & nuke)
{
    this->nukes.push_back(nuke);
}

void Level::computeRays()
{
    Ray ray(this->source.getPosition(),
            this->source.getPosition(),
            this->source.getWaveLength()
            );

    this->computeRay(ray);
    throw new StarlightException("to do");
}

void Level::computeRay(Ray &)
{
    throw new StarlightException("Largeur doit être strict. positive");
}

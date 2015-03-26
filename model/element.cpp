#include "element.hpp"
#include "level.hpp"


/**
 * @brief Element::setLevel
 * @param level
 */
void Element::setLevel(Level * level)
{
    this->level = level;
}

Level * Element::getLevel() const
{
    return this->level;
}

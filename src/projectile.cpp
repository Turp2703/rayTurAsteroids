#include "projectile.h"

// Constructor
Projectile::Projectile(Vector2 p_pos, float p_radAngle, int p_horLimit, int p_verLimit)
    : m_alive(true), m_position(p_pos), m_radAngle(p_radAngle),
      m_horizontalLimit(p_horLimit), m_verticalLimit(p_verLimit)
{
    /* */
}

// Copy constructor
Projectile::Projectile(const Projectile& other)
    : m_alive(other.m_alive), m_position(other.m_position),
      m_radAngle(other.m_radAngle), m_horizontalLimit(other.m_horizontalLimit),
      m_verticalLimit(other.m_verticalLimit) 
{
    /* */
}
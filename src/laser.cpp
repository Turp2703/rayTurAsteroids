#include "laser.h"

#include "raylib.h"

#include <utility>
#include <cmath>

// Constructor
Laser::Laser(Vector2 p_pos, float p_radAngle, int p_horLimit, int p_verLimit)
    : Projectile(p_pos, p_radAngle, p_horLimit, p_verLimit)
{
    /* */
}

// Copy Constructor
Laser::Laser(const Laser& other)
    : Projectile(other) 
{
    /* */
}

// Move Assignment Operator
Laser& Laser::operator=(Laser&& other) noexcept {
    if (this != &other)
        Projectile::operator=(std::move(other));
    return *this;
}

void Laser::update(){
    // Calculate time
    m_lifeTime = static_cast<float>(GetTime()) - m_startTime;
    m_alive = m_lifeTime < k_maxLifeTime;
    
    // Calculate pos
    Vector2 endPos = {
        static_cast<float>(m_position.x + cos(m_radAngle) * k_speed),
        static_cast<float>(m_position.y + sin(m_radAngle) * k_speed)
    };
    // Teleport
    if      (endPos.x > m_horizontalLimit)  endPos.x -= m_horizontalLimit;
    else if (endPos.x < 0)                  endPos.x += m_horizontalLimit;
    if      (endPos.y > m_verticalLimit)    endPos.y -= m_verticalLimit;
    else if (endPos.y < 0)                  endPos.y += m_verticalLimit;
    // Change pos
    m_position = endPos;
}

void Laser::draw(){
    Vector2 endPos = {
        static_cast<float>(m_position.x + cos(m_radAngle) * k_speed),
        static_cast<float>(m_position.y + sin(m_radAngle) * k_speed)
    };
    DrawLineEx(m_position, endPos, k_size, RED);
}

bool Laser::isAlive(){
    return m_alive;
}
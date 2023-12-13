#include "flame.h"

#include "raylib.h"

#include <utility>
#include <cmath>

// Constructor
Flame::Flame(Vector2 p_pos, float p_radAngle, float p_speed, float p_size, int p_horLimit, int p_verLimit)
    : Projectile(p_pos, p_radAngle, p_horLimit, p_verLimit)
    , m_speed(p_speed), m_size(p_size)
{
    /* */
}

// Copy Constructor
Flame::Flame(const Flame& other)
    : Projectile(other) 
    , m_speed(other.m_speed), m_size(other.m_size)
{
    /* */
}

// Move Assignment Operator
Flame& Flame::operator=(Flame&& other) noexcept {
    if (this != &other){
        Projectile::operator=(std::move(other));
        m_speed = std::exchange(other.m_speed, 0.0f);
        m_size = std::exchange(other.m_size, 0.0f);
    }
    return *this;
}

void Flame::update(){
    // Calculate size
    m_size -= k_sizeLoss;
    m_alive = m_size > 0.0f;
    
    // Calculate pos
    Vector2 endPos = {
        static_cast<float>(m_position.x + cos(m_radAngle) * m_speed),
        static_cast<float>(m_position.y + sin(m_radAngle) * m_speed)
    };
    // Teleport
    if      (endPos.x > m_horizontalLimit)  endPos.x -= m_horizontalLimit;
    else if (endPos.x < 0)                  endPos.x += m_horizontalLimit;
    if      (endPos.y > m_verticalLimit)    endPos.y -= m_verticalLimit;
    else if (endPos.y < 0)                  endPos.y += m_verticalLimit;
    // Change pos
    m_position = endPos;
}

void Flame::draw(){
    DrawCircleV(m_position, m_size, ORANGE);
}

bool Flame::isAlive(){
    return m_alive;
}
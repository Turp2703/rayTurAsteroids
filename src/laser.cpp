#include "laser.h"

#include "raylib.h"

#include <cmath>

Laser::Laser(Vector2 p_pos, float p_radAngle, int p_horLimit, int p_verLimit){
    m_alive = true;
    m_startTime = static_cast<float>(GetTime());
    m_lifeTime = 0.0f;
    m_position = p_pos;
    m_radAngle = p_radAngle;
    m_horizontalLimit = p_horLimit;
    m_verticalLimit   = p_verLimit;
}

Laser& Laser::operator=(const Laser& other){
    if (this != &other)
    {
        m_alive = other.m_alive;
        m_startTime = other.m_startTime;
        m_lifeTime = other.m_lifeTime;
        m_position = other.m_position;
        m_radAngle = other.m_radAngle;
        m_horizontalLimit = other.m_horizontalLimit;
        m_verticalLimit = other.m_verticalLimit;
    }
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
    if      (endPos.x > m_horizontalLimit)  endPos.x -= m_horizontalLimit + k_size.x;
    else if (endPos.x < -(k_size.x * 1.05f))  endPos.x += m_horizontalLimit + k_size.x;
    if      (endPos.y > m_verticalLimit)    endPos.y -= m_verticalLimit   + k_size.y;
    else if (endPos.y < -(k_size.y * 1.05f))  endPos.y += m_verticalLimit   + k_size.y;
    // Change pos
    m_position = endPos;
}

void Laser::draw(){
    DrawRectangleV(m_position, k_size, RED);
}

bool Laser::isAlive(){
    return m_alive;
}
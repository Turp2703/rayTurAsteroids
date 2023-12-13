#include "asteroid.h"

#include <cmath>

Asteroid::Asteroid(int p_screenWidth, int p_screenHeight){
    m_position.x = p_screenWidth  / 2; 
    m_position.y = p_screenHeight / 4; 
    m_size = 10.0f;
    m_horizontalLimit = p_screenWidth  + m_size * 1.05f;
    m_verticalLimit   = p_screenHeight + m_size * 1.05f;
    m_speed = 0.0f;
    m_angle = 120.0f;
    m_radAngle = m_angle * DEG2RAD;
}

void Asteroid::update(){
    // Calculate pos
    m_radAngle = m_angle * DEG2RAD;
    Vector2 endPos = {
        static_cast<float>(m_position.x + cos(m_radAngle) * m_speed),
        static_cast<float>(m_position.y + sin(m_radAngle) * m_speed)
    };
    // Teleport
    if      (endPos.x > m_horizontalLimit)  endPos.x -= m_horizontalLimit + m_size;
    else if (endPos.x < -(m_size * 1.05f))  endPos.x += m_horizontalLimit + m_size;
    if      (endPos.y > m_verticalLimit)    endPos.y -= m_verticalLimit   + m_size;
    else if (endPos.y < -(m_size * 1.05f))  endPos.y += m_verticalLimit   + m_size;
    // Change pos
    m_position = endPos;
}

void Asteroid::draw(){
    DrawCircleV(m_position, m_size, GRAY);
}
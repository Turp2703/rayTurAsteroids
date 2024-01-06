#include "laser.h"

#include "raylib.h"

#include <utility>
#include <cmath>

// Constructor
Laser::Laser(Vector2 p_pos, float p_radAngle, int p_horLimit, int p_verLimit)
    : Projectile(p_pos, p_radAngle, p_horLimit, p_verLimit)
    , m_startTime(static_cast<float>(GetTime())), m_lifeTime(0.0f)
{
    /* */
}

// Copy Constructor
Laser::Laser(const Laser& other)
    : Projectile(other) 
    , m_startTime(other.m_startTime), m_lifeTime(other.m_lifeTime)
{
    /* */
}

// Move Assignment Operator
Laser& Laser::operator=(Laser&& other) noexcept {
    if (this != &other){
        Projectile::operator=(std::move(other));
        m_startTime = std::exchange(other.m_startTime, 0.0f);
        m_lifeTime = std::exchange(other.m_lifeTime, 0.0f);
    }
    return *this;
}

void Laser::update(){
    // Calculate time
    m_lifeTime = static_cast<float>(GetTime()) - m_startTime;
    m_alive = m_lifeTime < k_maxLifeTime;
    
    // Calculate pos
    m_endPos = {
        static_cast<float>(m_position.x + cos(m_radAngle) * k_speed),
        static_cast<float>(m_position.y + sin(m_radAngle) * k_speed)
    };
    // Teleport
    if      (m_endPos.x > m_horizontalLimit)  m_endPos.x -= m_horizontalLimit;
    else if (m_endPos.x < 0)                  m_endPos.x += m_horizontalLimit;
    if      (m_endPos.y > m_verticalLimit)    m_endPos.y -= m_verticalLimit;
    else if (m_endPos.y < 0)                  m_endPos.y += m_verticalLimit;
    // Change pos
    m_position = m_endPos;
}

void Laser::draw(){
    m_endPos = {
        static_cast<float>(m_position.x + cos(m_radAngle) * k_speed),
        static_cast<float>(m_position.y + sin(m_radAngle) * k_speed)
    };
    DrawLineEx(m_position, m_endPos, k_size, RED);
    
    
    //DrawRectangleRec(getHitBox(), BLUE);
}
void Laser::draw(Texture2D &p_texture){
    DrawTexturePro( p_texture
                  , { 0.f, 0.f, (float)p_texture.width, (float)p_texture.height }
                  , { m_position.x, m_position.y, p_texture.width * 2.f, p_texture.height * 2.f }
                  , { (float)p_texture.width, (float)p_texture.height }
                  , m_radAngle * RAD2DEG
                  , WHITE);
}

bool Laser::isAlive(){
    return m_alive;
}

Rectangle Laser::getHitBox(){
    return {m_position.x, m_position.y, std::abs(m_endPos.x - m_position.x) + 1, std::abs(m_endPos.y - m_position.y) + 1};
}

void Laser::destroy(){
    m_alive = false;
}
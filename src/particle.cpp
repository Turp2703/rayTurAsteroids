#include "particle.h"

#include <utility>
#include <algorithm>
#include <cmath>

// Constructors
Particle::Particle(Vector2 p_pos, float p_angle, double p_maxTime)
    : m_position(p_pos), m_angle(p_angle), m_maxTime(p_maxTime)
{
    m_alive = true;
    m_angleIncrement = 0.f;
    m_startTime = GetTime();
    m_speed = GetRandomValue(20, 40) / 10.f;
}
Particle::Particle(Vector2 p_pos, float p_angle, double p_maxTime, float p_angleIncrement, float p_speed)
    : m_position(p_pos), m_angle(p_angle), m_maxTime(p_maxTime), m_angleIncrement(p_angleIncrement)
{
    m_alive = true;
    m_startTime = GetTime();
    m_speed = p_speed;
}

// Copy constructor
Particle::Particle(const Particle& other)
    : m_alive(other.m_alive), m_position(other.m_position), m_angle(other.m_angle)
    , m_maxTime(other.m_maxTime), m_angleIncrement(other.m_angleIncrement)
    , m_speed(other.m_speed), m_startTime(other.m_startTime)
{
    /* */
}

// Move Assignment Operator
Particle& Particle::operator=(Particle&& other) noexcept {
    if (this != &other){
        m_alive = std::exchange(other.m_alive, false);
        m_position = std::exchange(other.m_position, {0.f, 0.f});
        m_angle = std::exchange(other.m_angle, 0.0f);
        m_angleIncrement = std::exchange(other.m_angleIncrement , 0.0f);
        m_speed = std::exchange(other.m_speed, 0.0f);
        m_startTime = std::exchange(other.m_startTime, 0.0);
        m_maxTime = std::exchange(other.m_maxTime, 0.0);
    }
    return *this;
}

void Particle::update(){
    // Calculate life
    m_alive = GetTime() - m_startTime < m_maxTime;
    
    // Calculate movement
    m_angle = (int)(m_angle + m_angleIncrement) % 360;
    Vector2 endPos = {
        static_cast<float>(m_position.x + cos(m_angle * DEG2RAD) * -m_speed),
        static_cast<float>(m_position.y + sin(m_angle * DEG2RAD) * m_speed)
    };
    m_position = endPos;
}

void Particle::draw(Texture2D &p_particleTexture, Color p_color, bool p_endGlow){
    DrawTexturePro( p_particleTexture
                  , { 0.f, 0.f, (float)p_particleTexture.width, (float)p_particleTexture.height }
                  , { m_position.x, m_position.y, (float)p_particleTexture.width, (float)p_particleTexture.height }
                  , { p_particleTexture.width / 2.f, p_particleTexture.height / 2.f }
                  , GetRandomValue(1, 90)
                  , { p_color.r, p_color.g, p_color.b, mapTimeToAlpha(GetTime() - m_startTime, m_maxTime, p_endGlow) });
}
unsigned char Particle::mapTimeToAlpha(double p_current, double p_max, bool p_endGlow){
    if(p_endGlow)
        return static_cast<unsigned char>((static_cast<double>(p_current - 1) / (p_max - 1)) * 254);
    
    p_current = std::max(0.0, std::min(p_max, p_current));
    double normalizedValue = p_current / p_max;
    return 255 - static_cast<unsigned char>(normalizedValue * 254);
}

bool Particle::isAlive(){
    return m_alive;
}
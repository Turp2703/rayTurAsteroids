#include "shockwave.h"

#include "raylib.h"

#include <utility>
#include <cmath>

// Constructor
Shockwave::Shockwave(Vector2 p_pos, int p_horLimit, int p_verLimit)
    : Projectile(p_pos, 0.0f, p_horLimit, p_verLimit), m_startTime(GetTime())
{
    /* */
}

// Copy Constructor
Shockwave::Shockwave(const Shockwave& other)
    : Projectile(other), m_startTime(other.m_startTime)
{
    /* */
}

// Move Assignment Operator
Shockwave& Shockwave::operator=(Shockwave&& other) noexcept {
    if (this != &other){
        Projectile::operator=(std::move(other));
        m_startTime = std::exchange(other.m_startTime, 0.0f);
    }
    return *this;
}

void Shockwave::update(){
    // Calculate life
    m_alive = GetTime() - m_startTime < k_lifeTime;
}

void Shockwave::draw(){
    DrawCircleV(m_position, k_size, SKYBLUE);
}

bool Shockwave::isAlive(){
    return m_alive;
}
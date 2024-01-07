#include "shockwave.h"

#include "raylib.h"

#include <iostream>
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
void Shockwave::update(std::vector<Particle> &p_particles){
    // Particles
    for(int i = 0; i < 8; i++){
        p_particles.push_back(Particle(m_position
                            , (float)GetRandomValue(30, 60) * i
                            , 0.4f
                            , (float)GetRandomValue(10, 15)
                            , GetRandomValue(45, 90) / 10.f));
    }
    
    // Calculate life
    m_alive = GetTime() - m_startTime < k_lifeTime;
}

void Shockwave::draw(){
    // DrawCircleV(m_position, k_size, SKYBLUE);
    DrawCircleLines(m_position.x, m_position.y, k_size, GetRandomValue(0,1) ? SKYBLUE : BLUE);
    // DrawCircleV(m_position, k_size, RED);
    // DrawText(std::to_string(p_texture.width).c_str(), 10, 10, 20, WHITE);
}

bool Shockwave::isAlive(){
    return m_alive;
}

Vector2 Shockwave::getPos(){
    return m_position;
}

float Shockwave::getRadius(){
    return k_size;
}

void Shockwave::destroy(){
    m_alive = false;
}
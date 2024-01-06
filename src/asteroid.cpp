#include "asteroid.h"

#include "raymath.h"

#include <utility>
#include <cmath>
#include <iostream>

// Constructors
Asteroid::Asteroid(int p_screenWidth, int p_screenHeight){
    m_position.x = p_screenWidth  / 2; 
    m_position.y = p_screenHeight / 4; 
    m_size = 25.0f;
    m_horizontalLimit = p_screenWidth  + m_size * 1.05f;
    m_verticalLimit   = p_screenHeight + m_size * 1.05f;
    m_speed = 1.0f;
    m_angle = 120.0f;
    m_radAngle = m_angle * DEG2RAD;
    m_hitBox = {m_position.x - m_size / 2, m_position.y - m_size / 2, m_size, m_size}; // X, Y, W, H
    m_alive = true;
    m_metal = false;
    m_heat = 0;
    m_shield = false;
    m_shieldActive = false;
    m_shieldLossTime = GetTime();
    m_shouldParticleDestroyed = false;
}
Asteroid::Asteroid(int p_screenWidth, int p_screenHeight, Vector2 p_position, float p_size, float p_speed, float p_angle, bool p_metal, bool p_shield)
    : m_position(p_position), m_size(p_size), m_speed(p_speed), m_angle(p_angle), m_metal(p_metal), m_shield(p_shield)
{
    m_horizontalLimit = p_screenWidth  + m_size * 1.05f;
    m_verticalLimit   = p_screenHeight + m_size * 1.05f;
    m_radAngle = m_angle * DEG2RAD;
    m_hitBox = {m_position.x - m_size / 2, m_position.y - m_size / 2, m_size, m_size}; // X, Y, W, H
    m_alive = true;
    m_heat = 0;
    m_shieldActive = m_shield;
    m_shieldLossTime = GetTime();
    m_shouldParticleDestroyed = false;
}

// Copy Constructor
Asteroid::Asteroid(const Asteroid& other)
    : m_position(other.m_position), m_size(other.m_size), m_horizontalLimit(other.m_horizontalLimit)
    , m_verticalLimit(other.m_verticalLimit), m_speed(other.m_speed), m_angle(other.m_angle)
    , m_radAngle(other.m_radAngle), m_hitBox(other.m_hitBox), m_alive(other.m_alive)
    , m_metal(other.m_metal), m_heat(other.m_heat), m_shield(other.m_shield)
    , m_shieldActive(other.m_shieldActive), m_shieldLossTime(other.m_shieldLossTime)
    , m_shouldParticleDestroyed(other.m_shouldParticleDestroyed)
{
    /* */
}

// Move Assignment Operator
Asteroid& Asteroid::operator=(Asteroid&& other) noexcept {
    if (this != &other){
        m_position = std::exchange(other.m_position, Vector2Zero());
        m_size = std::exchange(other.m_size, 0.0f);
        m_horizontalLimit = std::exchange(other.m_horizontalLimit, 0);
        m_verticalLimit   = std::exchange(other.m_verticalLimit, 0);
        m_speed = std::exchange(other.m_speed, 0.0f);
        m_angle = std::exchange(other.m_angle, 0.0f);
        m_radAngle = std::exchange(other.m_radAngle, 0.0f);
        m_hitBox = std::exchange(other.m_hitBox, {0.0f, 0.0f, 0.0f, 0.0f});
        m_alive = std::exchange(other.m_alive, false);
        m_metal = std::exchange(other.m_metal, false);
        m_heat = std::exchange(other.m_heat, 0);
        m_shield = std::exchange(other.m_shield, false);
        m_shieldActive = std::exchange(other.m_shieldActive, false);
        m_shieldLossTime = std::exchange(other.m_shieldLossTime, 0.0);
        m_shouldParticleDestroyed = std::exchange(other.m_shouldParticleDestroyed, false);
    }
    return *this;
}

void Asteroid::update(int& p_score, std::vector<Particle>& p_asteroidParticles){
    // Particles
    if(m_shouldParticleDestroyed){
        for(int i = 0; i < GetRandomValue(4, 8); i++)
            p_asteroidParticles.push_back(Particle(m_position, (float)GetRandomValue(45, 75) * i, m_size / 50));
        m_shouldParticleDestroyed = false;
    }
    m_particles.push_back(Particle(m_position, 360 - m_angle + GetRandomValue(-5, 5), 0.3));
    for (auto it = m_particles.begin(); it != m_particles.end();){
        if (!it->isAlive()){
            it = m_particles.erase(it);
        }
        else {
            it->update();
            it++;
        }
    }

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
    // Move HitBox
    m_hitBox = {m_position.x - m_size * 0.8f, m_position.y - m_size  * 0.8f, m_size * 1.6f, m_size * 1.6f};
    
    // Heat
    if(m_metal){
        if (m_heat == k_maxHeat){
            m_heat = 0;
            p_score += 5;
            m_metal = false;
                                // METAL PARTICLE
        }
        else if(m_heat - k_heatDecrease >= 0){
            m_heat -= k_heatDecrease;
        }
    }
    
    // Recharge shield
    if(m_shield && !m_shieldActive && GetTime() - m_shieldLossTime >= k_shieldCooldown){
        enableShieldActive();
    }
}

void Asteroid::draw(){
    if(m_shield && m_shieldActive)
        DrawCircleV(m_position, m_size + 8, SKYBLUE);
    if(m_metal)
        DrawCircleV(m_position, m_size + 4, {240, (unsigned char)(240 - m_heat/10), (unsigned char)(240 - m_heat/10), 255});
    DrawCircleV(m_position, m_size + 1, DARKGRAY);
    DrawCircleV(m_position, m_size, GRAY);
    
    // DrawRectangleRec(m_hitBox, RED);
    // DrawText(std::to_string(m_heat).c_str(), 10, 30, 20, WHITE);
}
void Asteroid::draw(Texture2D &p_asteroid, Texture2D &p_metal, Texture2D &p_shield){
    float mult, div;
    if(m_size > 35.f){ // Size 3
        mult = 2.5f;
        div = 0.8f;
    }
    else if(m_size < 25.f){ // Size 1
        mult = 0.75f;
        div = 3.f;
    }
    else{ // Size 2
        mult = 1.25f;
        div = 1.3f;
    }
    
    DrawTexturePro( p_asteroid
                  , { 0.f, 0.f, (float)p_asteroid.width, (float)p_asteroid.height }
                  , { m_position.x, m_position.y, p_asteroid.width * mult, p_asteroid.height * mult}
                  , { (float)p_asteroid.width / div, (float)p_asteroid.height / div }
                  , m_angle
                  , WHITE);
                  
    if(m_metal)
        DrawTexturePro( p_metal
                      , { 0.f, 0.f, (float)p_metal.width, (float)p_metal.height }
                      , { m_position.x, m_position.y, p_metal.width * mult, p_metal.height * mult}
                      , { (float)p_metal.width / div, (float)p_metal.height / div }
                      , m_angle
                      , {240, (unsigned char)(240 - m_heat/7.5f), (unsigned char)(240 - m_heat/7.5f), 255});
        
    if(m_shieldActive)
        DrawTexturePro( p_shield
                      , { 0.f, 0.f, (float)p_shield.width, (float)p_shield.height }
                      , { m_position.x, m_position.y, p_shield.width * mult, p_shield.height * mult}
                      , { (float)p_shield.width / div, (float)p_shield.height / div }
                      , m_angle
                      , WHITE);
    
    // DrawRectangleRec(m_hitBox, RED);
}
void Asteroid::drawEffects(Texture2D &p_particleTexture){
    Color particleColor = GRAY;
    if(m_shieldActive) particleColor = SKYBLUE;
    else if(m_metal) particleColor = {240, (unsigned char)(240 - m_heat/10), (unsigned char)(240 - m_heat/10), 255};
    for(auto& particle : m_particles)
        particle.draw(p_particleTexture, particleColor, true);
}

Rectangle Asteroid::getHitBox(){
    return m_hitBox;
}

void Asteroid::destroy(int& p_score){
    m_alive = false;
    p_score += 20;
    m_shouldParticleDestroyed = true;
}

bool Asteroid::isAlive(){
    return m_alive;
}

bool Asteroid::hasMetal(){
    return m_metal;
}
void Asteroid::toggleMetal(){
    m_metal = !m_metal;
}
void Asteroid::addHeat(){
    if(m_heat < k_maxHeat)
        m_heat += k_heatIncrease;
}

bool Asteroid::hasShield(){
    return m_shieldActive;
}
void Asteroid::toggleShield(){
    m_shield = !m_shield;
}
void Asteroid::enableShieldActive(){
    m_shieldActive = true;
}
void Asteroid::disableShieldActive(){
    m_shieldLossTime = GetTime();
    m_shieldActive = false;
}
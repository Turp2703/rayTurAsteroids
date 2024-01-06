#include "portal.h"

#include "raylib.h"

#include <utility>
#include <iostream>

// Constructor
Portal::Portal(Vector2 p_position, int p_groupCount, int p_groupSize, float p_angle, float p_angleIncrement, double p_interval, int p_screenWidth, int p_screenHeight, float p_size, float p_speed, bool p_metals, bool p_shields)
    : m_position(p_position), m_groupCount(p_groupCount)
    , m_groupSize(p_groupSize), m_angle(p_angle), m_angleIncrement(p_angleIncrement)
    , m_interval(p_interval), m_screenWidth(p_screenWidth), m_screenHeight(p_screenHeight)
    , m_size(p_size), m_speed(p_speed), m_metals(p_metals), m_shields(p_shields)
{
    if(m_groupSize < 1) m_groupSize = 1;
    m_previousTime = 0;
    m_alive = true;
    m_startTime = GetTime();
    m_active = false;
}

// Copy Constructor
Portal::Portal(const Portal& other)
    : m_position(other.m_position), m_groupCount(other.m_groupCount), m_groupSize(other.m_groupSize)
    , m_angle(other.m_angle), m_angleIncrement(other.m_angleIncrement), m_previousTime(other.m_previousTime)
    , m_interval(other.m_interval), m_screenWidth(other.m_screenWidth), m_screenHeight(other.m_screenHeight)
    , m_size(other.m_size), m_speed(other.m_speed), m_metals(other.m_metals), m_shields(other.m_shields)
    , m_alive(other.m_alive), m_startTime(other.m_startTime), m_active(other.m_active)
{
    /* */
}

// Move Assignment Operator
Portal& Portal::operator=(Portal&& other) noexcept {
    if (this != &other) {
        // Exchange values and move resources
        m_position = std::move(other.m_position);
        m_groupCount = std::exchange(other.m_groupCount, 0);
        m_groupSize = std::exchange(other.m_groupSize, 0);
        m_angle = std::exchange(other.m_angle, 0.0f);
        m_angleIncrement = std::exchange(other.m_angleIncrement, 0.0f);
        m_previousTime = std::exchange(other.m_previousTime, 0.0);
        m_interval = std::exchange(other.m_interval, 0.0);
        m_screenWidth = std::exchange(other.m_screenWidth, 0);
        m_screenHeight = std::exchange(other.m_screenHeight, 0);
        m_size = std::exchange(other.m_size, 0.0f);
        m_speed = std::exchange(other.m_speed, 0.0f);
        m_metals = std::exchange(other.m_metals, false);
        m_shields = std::exchange(other.m_shields, false);
        m_alive = std::exchange(other.m_alive, false);
        m_startTime = std::exchange(other.m_startTime, 0.0);
        m_active = std::exchange(other.m_active, false);
    }
    return *this;
}

void Portal::update(std::vector<Asteroid>& p_asteroids){
    Vector2 center = {m_position.x + k_size.x / 2, m_position.y + k_size.y / 2};
    
    // Particles
    for(int i = 0; i < 6; i++){
        m_particles.push_back(Particle(center, (float)GetRandomValue(45, 75) * i, GetRandomValue(5, 20) / 100.f, GetRandomValue(2, 10) / 10.f, GetRandomValue(30, 60) / 10.f));
    }
    for (auto it = m_particles.begin(); it != m_particles.end();){
        if (!it->isAlive()){
            it = m_particles.erase(it);
        }
        else {
            it->update();
            it++;
        }
    }
    
    double currentTime = GetTime();
    if(m_active){
        // Asteroids
        if(currentTime - m_previousTime >= m_interval){
            float extraAngle = 360 / m_groupSize;
            for(int i = 0; i < m_groupSize; i++){
                Asteroid ast(m_screenWidth, m_screenHeight, center, m_size, m_speed, m_angle + i * extraAngle, m_metals,    m_shields);
                p_asteroids.push_back(ast);
            }
        
            m_angle = (int)(m_angle + m_angleIncrement) % 360;
            m_groupCount--;
            m_previousTime = currentTime;
            m_alive = m_groupCount > 0;
        }
    }
    else{
        m_active = currentTime - m_startTime > k_warmUpTime;
    }
}

void Portal::draw(){
    DrawRectangleV(m_position, k_size, DARKPURPLE);
    
    // DrawText(std::to_string(m_previousTime).c_str(), 10, 30, 20, WHITE);
    // DrawText(std::to_string(GetTime()).c_str(), 10, 50, 20, WHITE);
}
void Portal::draw(Texture2D p_texture){
    DrawTextureEx(p_texture, m_position, 0.f, 2.f, WHITE);
}
void Portal::drawEffects(Texture2D p_particleTexture){
    for(auto& particle : m_particles)
        particle.draw(p_particleTexture, PURPLE, false);
}

bool Portal::isAlive(){
    return m_alive;
}
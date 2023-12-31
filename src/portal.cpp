#include "portal.h"

#include "raylib.h"

#include <utility>
#include <iostream>

// Constructor
Portal::Portal(std::vector<Asteroid>& p_asteroids, Vector2 p_position, int p_groupCount, int p_groupSize, float p_angle, float p_angleIncrement, double p_interval, int p_screenWidth, int p_screenHeight, bool p_metals, bool p_shields)
    : m_asteroids(p_asteroids), m_position(p_position), m_groupCount(p_groupCount)
    , m_groupSize(p_groupSize), m_angle(p_angle), m_angleIncrement(p_angleIncrement)
    , m_interval(p_interval), m_screenWidth(p_screenWidth), m_screenHeight(p_screenHeight)
    , m_metals(p_metals), m_shields(p_shields)
{
    if(m_groupSize < 1) m_groupSize = 1;
    m_previousTime = 0;
    m_alive = true;
}

// Copy Constructor
Portal::Portal(const Portal& other)
    : m_asteroids(other.m_asteroids)
    , m_position(other.m_position), m_groupCount(other.m_groupCount), m_groupSize(other.m_groupSize)
    , m_angle(other.m_angle), m_angleIncrement(other.m_angleIncrement), m_previousTime(other.m_previousTime)
    , m_interval(other.m_interval), m_screenWidth(other.m_screenWidth), m_screenHeight(other.m_screenHeight)
    , m_metals(other.m_metals), m_shields(other.m_shields), m_alive(other.m_alive)
{
    /* */
}

// Move Assignment Operator
Portal& Portal::operator=(Portal&& other) noexcept {
    if (this != &other) {
        // Exchange values and move resources
        m_asteroids = std::move(other.m_asteroids);
        m_position = std::move(other.m_position);
        m_groupCount = std::exchange(other.m_groupCount, 0);
        m_groupSize = std::exchange(other.m_groupSize, 0);
        m_angle = std::exchange(other.m_angle, 0.0f);
        m_angleIncrement = std::exchange(other.m_angleIncrement, 0.0f);
        m_previousTime = std::exchange(other.m_previousTime, 0.0);
        m_interval = std::exchange(other.m_interval, 0.0);
        m_screenWidth = std::exchange(other.m_screenWidth, 0);
        m_screenHeight = std::exchange(other.m_screenHeight, 0);
        m_metals = std::exchange(other.m_metals, false);
        m_shields = std::exchange(other.m_shields, false);
        m_alive = std::exchange(other.m_alive, false);
    }
    return *this;
}

void Portal::update(){
    double currentTime = GetTime();
    if(currentTime - m_previousTime >= m_interval){
        Vector2 center = {m_position.x + k_size.x / 2, m_position.y + k_size.y / 2};
        
        float extraAngle = 360 / m_groupSize;
        for(int i = 0; i < m_groupSize; i++){
            Asteroid ast(m_screenWidth, m_screenHeight, center, 5.f, 1.f, m_angle + i * extraAngle, m_metals, m_shields);
            m_asteroids.push_back(ast);
        }
        
        m_angle = (int)(m_angle + m_angleIncrement) % 360;
        m_groupCount--;
        m_previousTime = currentTime;
        m_alive = m_groupCount > 0;
    }
}

void Portal::draw(){
    DrawRectangleV(m_position, k_size, DARKPURPLE);
    
    DrawText(std::to_string(m_previousTime).c_str(), 10, 30, 20, WHITE);
    DrawText(std::to_string(GetTime()).c_str(), 10, 50, 20, WHITE);
}

bool Portal::isAlive(){
    return m_alive;
}
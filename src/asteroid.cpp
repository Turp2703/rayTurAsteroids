#include "asteroid.h"

#include "raymath.h"

#include <utility>
#include <cmath>
#include <iostream>

// Constructor
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
}

// Copy Constructor
Asteroid::Asteroid(const Asteroid& other)
    : m_position(other.m_position), m_size(other.m_size), m_horizontalLimit(other.m_horizontalLimit)
    , m_verticalLimit(other.m_verticalLimit), m_speed(other.m_speed), m_angle(other.m_angle)
    , m_radAngle(other.m_radAngle), m_hitBox(other.m_hitBox), m_alive(other.m_alive)
    , m_metal(other.m_metal), m_heat(other.m_heat), m_shield(other.m_shield)
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
    }
    return *this;
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
    // Move HitBox
    m_hitBox = {m_position.x - m_size * 0.8f, m_position.y - m_size  * 0.8f, m_size * 1.6f, m_size * 1.6f};
    
    // Heat
    if(m_metal){
        if (m_heat == k_maxHeat){
            m_heat = 0;
            m_metal = false;
        }
        else if(m_heat - k_heatDecrease >= 0){
            m_heat -= k_heatDecrease;
        }
    }
    
    // Recharge shield
}

void Asteroid::draw(){
    if(m_shield)
        DrawCircleV(m_position, m_size + 8, SKYBLUE);
    if(m_metal)
        DrawCircleV(m_position, m_size + 4, {240, (unsigned char)(240 - m_heat/10), (unsigned char)(240 - m_heat/10), 255});
    DrawCircleV(m_position, m_size, GRAY);
    
    // DrawRectangleRec(m_hitBox, RED);
    // DrawText(std::to_string(m_heat).c_str(), 10, 30, 20, WHITE);
}

Rectangle Asteroid::getHitBox(){
    return m_hitBox;
}

void Asteroid::destroy(){
    m_alive = false;
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
    return m_shield;
}
void Asteroid::toggleShield(){
    m_shield = !m_shield;
}
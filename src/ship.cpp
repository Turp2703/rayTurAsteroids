#include "ship.h"
#include "globals.h"

#include "raylib.h"
#include "raymath.h"

#include <iostream>
#include <cmath>

Ship::Ship(int p_xPos, int p_yPos, float p_size)
    : m_size(p_size){
    m_position.x = (float)p_xPos; 
    m_position.y = (float)p_yPos; 
    m_speed = 0.0f;
    m_acceleration = 0.0f;
    m_angle = 0.0f;
    m_radAngle = 0.0f;
}

void Ship::update(){
    // Change angle
        // bool aDown = IsKeyDown(KEY_LEFT), dDown = IsKeyDown(KEY_RIGHT);
    bool aDown = IsKeyDown(KEY_A), dDown = IsKeyDown(KEY_D);
    if     ( aDown && !dDown)
        m_angle -= 3.0f;
    else if(!aDown && dDown) 
        m_angle += 3.0f;
    m_angle = (int)m_angle % 360; // Map to 0-359 range
    
    // Change acceleration
        // bool wDown = IsKeyDown(KEY_UP), sDown = IsKeyDown(KEY_DOWN);
    bool wDown = IsKeyDown(KEY_W), sDown = IsKeyDown(KEY_S);
    if     ( wDown && !sDown)
        m_acceleration = k_acceleration;
    else if(!wDown &&  sDown) 
        m_acceleration = -k_acceleration;
    else
        m_acceleration = 0.0f;
    // Change speed
    if(m_acceleration != 0){
        float newSpeed = m_speed + m_acceleration;
        if(newSpeed < k_maxSpeed && newSpeed > -k_maxSpeed)
            m_speed = newSpeed;
    }
    else{
        // Friction
        if(m_speed > 0)
            m_speed -= k_acceleration * k_friction;
        else if(m_speed < 0)
            m_speed += k_acceleration * k_friction;
        // float correction
        if(m_speed > -0.2f && m_speed < 0.2f) 
            m_speed = 0.0f;
    }
    // Calculate pos
    m_radAngle = m_angle * DEG2RAD;
    Vector2 endPos = {m_position.x + cos(m_radAngle) * m_speed, m_position.y + sin(m_radAngle) * m_speed};
    // Teleport
    if      (endPos.x > k_screenWidth + m_size * 1.1f)
        endPos.x -= k_screenWidth  + m_size * 2 * 1.1f;
    else if (endPos.x < -(m_size * 1.1f))
        endPos.x += k_screenWidth  + m_size * 2 * 1.1f;
    if      (endPos.y > k_screenHeight  + m_size * 1.1f)
        endPos.y -= k_screenHeight + m_size * 2 * 1.1f;
    else if (endPos.y < -(m_size * 1.1f))
        endPos.y += k_screenHeight + m_size * 2 * 1.1f;
    // Change pos
    m_position = endPos;
}

void Ship::draw(){
    // vector P over center C rotation = C + rotate(P - C)
    Vector2 p1 = {m_position.x + cos(m_radAngle) * m_size * 1.5f, m_position.y + sin(m_radAngle) * m_size * 1.5f};
    Vector2 p2 = Vector2Add(m_position, Vector2Rotate(Vector2Subtract(p1, m_position), 5*PI/6));
    Vector2 p3 = Vector2Add(m_position, Vector2Rotate(Vector2Subtract(p1, m_position), 7*PI/6));
    DrawTriangleLines(p1, p2, p3, WHITE);
    DrawCircleV(p1, 3.0f, WHITE);
    
    // float length = 30.0f;
    // float radAngle = m_angle * DEG2RAD;
    // Vector2 endPos = {m_position.x + cos(radAngle) * length, m_position.y + sin(radAngle) * length};
    // DrawLineEx(m_position, endPos, 3.0f, GREEN);
    // DrawCircleV(m_position, 3.0f, GREEN);
    // DrawText(std::to_string(m_angle).c_str(), 10, 10, 20, WHITE);
}
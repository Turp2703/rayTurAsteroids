#include "ship.h"

#include "laserManager.h"

#include "raylib.h"
#include "raymath.h"

#include <iostream>
#include <cmath>

Ship::Ship(int p_screenWidth, int p_screenHeight
         , LaserManager& p_laserManager, FlameManager& p_flameManager, ShockwaveManager& p_shockwaveManager)
    : m_laserManager(p_laserManager), m_flameManager(p_flameManager), m_shockwaveManager(p_shockwaveManager){
    m_alive = true;
    m_position.x = p_screenWidth  / 2; 
    m_position.y = p_screenHeight / 2; 
    m_size = 10.0f;
    m_horizontalLimit = p_screenWidth  + m_size * 1.05f;
    m_verticalLimit   = p_screenHeight + m_size * 1.05f;
    m_speed = 0.0f;
    m_acceleration = 0.0f;
    m_angle = 0.0f;
    m_radAngle = 0.0f;
    m_hitBox = {m_position.x, m_position.y, m_size}; // X Y W H
}


void Ship::update(){
    
    // WASD Keys
        // bool aDown = IsKeyDown(KEY_LEFT), dDown = IsKeyDown(KEY_RIGHT);
        // bool wDown = IsKeyDown(KEY_UP), sDown = IsKeyDown(KEY_DOWN);
    bool aDown = IsKeyDown(KEY_A), dDown = IsKeyDown(KEY_D), wDown = IsKeyDown(KEY_W), sDown = IsKeyDown(KEY_S);
    
    // Change angle
    if     ( aDown && !dDown){
        if(sDown)
            m_angle += 3.0f;
        else
            m_angle -= 3.0f;
    }
    else if(!aDown && dDown){
        if(sDown)
            m_angle -= 3.0f;
        else
            m_angle += 3.0f;
    }
    m_angle = (int)m_angle % 360; // Map to 0-359 range
    
    // Change acceleration
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
    Vector2 endPos = { static_cast<float>(m_position.x + cos(m_radAngle) * m_speed) ,
                       static_cast<float>(m_position.y + sin(m_radAngle) * m_speed) };
    // Teleport
    if      (endPos.x > m_horizontalLimit)  endPos.x -= m_horizontalLimit + m_size;
    else if (endPos.x < -(m_size * 1.05f))  endPos.x += m_horizontalLimit + m_size;
    if      (endPos.y > m_verticalLimit)    endPos.y -= m_verticalLimit   + m_size;
    else if (endPos.y < -(m_size * 1.05f))  endPos.y += m_verticalLimit   + m_size;
    // Change pos
    m_position = endPos;
    // Move HitBox
    m_hitBox = {m_position.x, m_position.y, m_size};
    
    // Attacks
    if(IsKeyPressed(KEY_J))
        m_laserManager.spawnLaser(m_position, m_radAngle, m_horizontalLimit, m_verticalLimit);
    if(IsKeyDown(KEY_K))
        m_flameManager.spawnFlame(m_position, m_radAngle, m_horizontalLimit, m_verticalLimit);
    if(IsKeyPressed(KEY_L))
        m_shockwaveManager.spawnShockwave(m_position, m_horizontalLimit, m_verticalLimit);
}

void Ship::draw(){
    // Draw Ship
    // vector P over center C rotation = C + rotate(P - C)
    Vector2 p1 = {m_position.x + cos(m_radAngle) * m_size * 1.5f, m_position.y + sin(m_radAngle) * m_size * 1.5f};
    Vector2 p2 = Vector2Add(m_position, Vector2Rotate(Vector2Subtract(p1, m_position), 5*PI/6));
    Vector2 p3 = Vector2Add(m_position, Vector2Rotate(Vector2Subtract(p1, m_position), 7*PI/6));
    DrawTriangleLines(p1, p2, p3, WHITE);
    DrawCircleV(p1, 3.0f, WHITE);
    
    // DrawCircle(m_hitBox.x, m_hitBox.y, m_hitBox.z, RED);
    // float length = 30.0f;
    // float radAngle = m_angle * DEG2RAD;
    // Vector2 endPos = {m_position.x + cos(radAngle) * length, m_position.y + sin(radAngle) * length};
    // DrawLineEx(m_position, endPos, 3.0f, GREEN);
    // DrawCircleV(m_position, 3.0f, GREEN);
    // DrawText(std::to_string(m_speed).c_str(), 10, 10, 20, WHITE);
    
    // Alive
    DrawText(std::to_string(m_alive).c_str(), 10, 10, 20, WHITE);
}

Vector3 Ship::getHitBox(){
    return m_hitBox;
}

bool Ship::isAlive(){
    return m_alive;
}

void Ship::kill(){
    m_alive = false;
}

void Ship::checkCollisions(std::vector<Asteroid>& p_asteroids){
    for(auto& asteroid : p_asteroids)
        if(asteroid.isAlive() && CheckCollisionCircleRec({m_hitBox.x, m_hitBox.y}, m_hitBox.z, asteroid.getHitBox()))
            kill();
        // testing only
        else
            m_alive = true;
}
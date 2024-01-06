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
    // Update Particles
    for (auto it = m_fireParticles.begin(); it != m_fireParticles.end();){
        if (!it->isAlive()){
            it = m_fireParticles.erase(it);
        }
        else {
            it->update();
            it++;
        }
    }
    for (auto it = m_deathParticles.begin(); it != m_deathParticles.end();){
        if (!it->isAlive()){
            it = m_deathParticles.erase(it);
        }
        else {
            it->update();
            it++;
        }
    }
    
    if(m_alive){
        // WASD Keys
            // bool aDown = IsKeyDown(KEY_LEFT), dDown = IsKeyDown(KEY_RIGHT), wDown = IsKeyDown(KEY_UP), sDown = IsKeyDown(KEY_DOWN);
        bool aDown = IsKeyDown(KEY_A), dDown = IsKeyDown(KEY_D), wDown = IsKeyDown(KEY_W), sDown = IsKeyDown(KEY_S);
        
        // Fire Particles
        if(wDown){
            m_fireParticles.push_back(Particle(m_position, 360 - m_angle + GetRandomValue(-15, 15), 0.3));
        }
        
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
        Vector2 origin = {m_position.x + cos(m_radAngle) * m_size*1.5f, m_position.y + sin(m_radAngle) * m_size*1.5f};
        if(IsKeyPressed(KEY_J)){
            m_laserManager.spawnLaser(origin, m_radAngle, m_horizontalLimit, m_verticalLimit);
        }
        if(IsKeyDown(KEY_K)){
            m_flameManager.spawnFlame(origin, m_radAngle, m_horizontalLimit, m_verticalLimit);
            m_flameManager.spawnFlame(origin, m_radAngle, m_horizontalLimit, m_verticalLimit);
        }
        if(IsKeyPressed(KEY_L))
            m_shockwaveManager.spawnShockwave(m_position, m_horizontalLimit, m_verticalLimit);
    }
}

void Ship::draw(){
    // Draw Ship
    // vector P over center C rotation = C + rotate(P - C)
    if(m_alive){
        Vector2 p1 = {m_position.x + cos(m_radAngle) * m_size * 1.5f, m_position.y + sin(m_radAngle) * m_size * 1.5f};
        Vector2 p2 = Vector2Add(m_position, Vector2Rotate(Vector2Subtract(p1, m_position), 5*PI/6));
        Vector2 p3 = Vector2Add(m_position, Vector2Rotate(Vector2Subtract(p1, m_position), 7*PI/6));
        DrawTriangleLines(p1, p2, p3, WHITE);
        DrawCircleV(p1, 3.0f, WHITE);
    }
    else{
        DrawCircle(m_hitBox.x, m_hitBox.y, m_hitBox.z, ORANGE);
    }
}
void Ship::draw(Texture2D p_texture){
    if(m_alive){
        DrawTexturePro( p_texture
                      , { 0.f, 0.f, (float)p_texture.width, (float)p_texture.height }
                      , { m_position.x, m_position.y, (float)p_texture.width, (float)p_texture.height }
                      , { p_texture.width / 2.f, p_texture.height / 2.f }
                      , m_angle
                      , WHITE);
        
        // DrawCircleV({m_position.x+cos(m_radAngle)*m_size*1.5f,m_position.y+sin(m_radAngle)*m_size*1.5f}, 3.0f, WHITE);
        // DrawCircleV(m_position, 3.0f, RED);
        // DrawCircle(m_hitBox.x, m_hitBox.y, m_hitBox.z, RED);
        // DrawText(std::to_string(m_angle).c_str(), 10, 10, 20, WHITE);
    }
}

void Ship::drawEffects(Texture2D p_particleTexture){
    for(auto& particle : m_fireParticles)
        particle.draw(p_particleTexture, ORANGE, false);
    for(auto& particle : m_deathParticles)
        particle.draw(p_particleTexture, WHITE, false);
}

Vector3 Ship::getHitBox(){
    return m_hitBox;
}

bool Ship::isAlive(){
    return m_alive;
}

void Ship::kill(){
    m_alive = false;
    for(int i = 0; i < 12; i++){
        m_deathParticles.push_back(Particle(m_position, 25.f * i, 1.5f, 1.5f, 10.f));
        m_deathParticles.push_back(Particle(m_position, 30.f * i, 1.5f, 2.f , 10.f));
        m_deathParticles.push_back(Particle(m_position, 35.f * i, 1.5f, 2.5f, 10.f));
    }
}

void Ship::checkCollisions(std::vector<Asteroid>& p_asteroids){
    if(m_alive)
        for(auto& asteroid : p_asteroids)
            if(asteroid.isAlive() && CheckCollisionCircleRec({m_hitBox.x, m_hitBox.y}, m_hitBox.z, asteroid.getHitBox()))
                kill();
}

void Ship::restart(){
    m_alive = true;
    m_position.x = GetScreenWidth()  / 2;
    m_position.y = GetScreenHeight() / 2;
    m_speed = 0.0f;
    m_acceleration = 0.0f;
    m_angle = 0.0f;
    m_radAngle = 0.0f;
    m_hitBox = {m_position.x, m_position.y, m_size}; // X Y W H
}
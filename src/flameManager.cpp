#include "flameManager.h"

#include "flame.h"
#include "asteroid.h"

#include "raylib.h"

#include <iostream>

FlameManager::FlameManager(){
    m_charge = k_maxCharge;
    m_recharge = false;
    m_lastTime = GetTime();
}

void FlameManager::update(){
    for (auto it = m_flames.begin(); it != m_flames.end();)
        if (!it->isAlive())
            it = m_flames.erase(it);
        else {
            it->update();
            it++;
        }
    
    m_recharge = GetTime() - m_lastTime >= k_chargeCooldown;
    if(m_recharge && m_charge < k_maxCharge){
        if(k_maxCharge - m_charge >= k_chargeRecover)
            m_charge += k_chargeRecover;
        else
            m_charge += k_maxCharge - m_charge;
    }
}

void FlameManager::draw(){
    for(Flame flame: m_flames)
        flame.draw();
    
    // DrawText(std::to_string(m_charge).c_str(), 10, 10, 20, WHITE);
    // for(unsigned int i = 0; i < m_flames.size(); i++)
        // DrawCircle(10.0f, i*10.0f, 3.0f, GREEN);
}
void FlameManager::draw(Texture2D (&p_texture)[4]){
    for(Flame flame: m_flames)
        flame.draw(p_texture);
}
void FlameManager::drawIndicators(){
    DrawRectangle(GetScreenWidth() - 30, GetScreenHeight() - 45, 20, m_charge * 40 / k_maxCharge , ORANGE);
    DrawRectangleLines(GetScreenWidth() - 30, GetScreenHeight() - 45, 20, 40, YELLOW);
}

void FlameManager::spawnFlame(Vector2 p_pos, float p_radAngle, int p_horLimit, int p_verLimit, Sound &p_sound){
    if(m_charge > 0){
        float rndSpeed = GetRandomValue(k_minSpeed, k_maxSpeed);
        int degAngle = p_radAngle * RAD2DEG;
        float rndAngle = GetRandomValue(degAngle - k_opening, degAngle + k_opening);
        float rndSize = GetRandomValue(k_minSize, k_maxSize);
        m_flames.push_back(Flame(p_pos, rndAngle * DEG2RAD, rndSpeed, rndSize, p_horLimit, p_verLimit));
        m_charge -= k_chargeConsumption;
        m_lastTime = GetTime();
        if(!IsSoundPlaying(p_sound))
            PlaySound(p_sound);
    }
}

void FlameManager::checkCollisions(std::vector<Asteroid>& p_asteroids){
    for(auto& flame : m_flames)
        for(auto& asteroid : p_asteroids)
            if(flame.isAlive() && asteroid.isAlive() && CheckCollisionRecs(asteroid.getHitBox(), flame.getHitBox())){
                if(asteroid.hasMetal() && !asteroid.hasShield())
                    asteroid.addHeat(); // heat asteroid
                //flame.destroy();
            }
}

void FlameManager::restart(){
    m_charge = k_maxCharge;
    m_flames.clear();
}
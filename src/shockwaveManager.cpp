#include "shockwaveManager.h"

#include "shockwave.h"

#include "raylib.h"

#include <iostream>

ShockwaveManager::ShockwaveManager(){
    for(int i = 0; i < k_charges; i++)
        m_charges[i] = k_maxCharge;
}

void ShockwaveManager::update(){
    for (auto it = m_shockwaves.begin(); it != m_shockwaves.end();)
        if (!it->isAlive())
            it = m_shockwaves.erase(it);
        else {
            it->update(m_particles);
            it++;
        }
        
    for(int& charge : m_charges)
        if(charge < k_maxCharge)
            charge += k_chargeRecover;
        
    // Particles
    for (auto it = m_particles.begin(); it != m_particles.end();){
        if (!it->isAlive()){
            it = m_particles.erase(it);
        }
        else {
            it->update();
            it++;
        }
    }
}

void ShockwaveManager::draw(){
    for(Shockwave& shockwave: m_shockwaves)
        shockwave.draw();
    
    // for(unsigned int i = 0; i < m_shockwaves.size(); i++)
        // DrawCircle(10.0f, 10.0f * (i + 1), 3.0f, GREEN);
    // for(unsigned int i = 0; i < k_charges; i++)
        // DrawText(std::to_string(m_charges[i]).c_str(), 30, 20 * (i + 1), 20, WHITE);
}
void ShockwaveManager::draw(Texture2D& p_particleTexture){
    for(Shockwave& shockwave: m_shockwaves)
        shockwave.draw();
    for(auto& particle : m_particles)
        particle.draw(p_particleTexture, GetRandomValue(0,1) ? SKYBLUE : BLUE, false);
}
void ShockwaveManager::drawIndicators(){
    for(int i = 0; i < k_charges; i++){
        DrawRectangle(GetScreenWidth() - 30 * (i + 2), GetScreenHeight() - 45, 20, m_charges[i] * 40 / 10000, SKYBLUE);
        DrawRectangleLines(GetScreenWidth() - 30 * (i + 2), GetScreenHeight() - 45, 20, 40, WHITE);
    }
}

void ShockwaveManager::spawnShockwave(Vector2 p_pos, int p_horLimit, int p_verLimit, Sound &p_sound){
    bool spawned = false;
    for(int i = 0; i < k_charges && !spawned; i++)
        if(m_charges[i] == k_maxCharge){
            m_shockwaves.push_back(Shockwave(p_pos, p_horLimit, p_verLimit));
            m_charges[i] = 0;
            PlaySound(p_sound);
            spawned = true;
        }
}

void ShockwaveManager::checkCollisions(std::vector<Asteroid>& p_asteroids){
    for(auto& shock : m_shockwaves)
        for(auto& asteroid : p_asteroids)
            if(shock.isAlive() && asteroid.isAlive() && CheckCollisionCircleRec(shock.getPos(), shock.getRadius(), asteroid.getHitBox()))
                if(asteroid.hasShield())
                    asteroid.disableShieldActive();
                ///// else asteroid.stun()  ?????
}

void ShockwaveManager::restart(){
    m_shockwaves.clear();
    m_particles.clear();
    for(int i = 0; i < k_charges; i++)
        m_charges[i] = k_maxCharge;
}
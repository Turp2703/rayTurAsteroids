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
            it->update();
            it++;
        }
        
    for(int& charge : m_charges)
        if(charge < k_maxCharge)
            charge += k_chargeRecover;
}

void ShockwaveManager::draw(){
    for(Shockwave shockwave: m_shockwaves)
        shockwave.draw();
    
    for(unsigned int i = 0; i < k_charges; i++){
        DrawRectangle(GetScreenWidth() - 30 * (i + 2), 10, 20, m_charges[i] * 40 / 10000, SKYBLUE);
        DrawRectangleLines(GetScreenWidth() - 30 * (i + 2), 10, 20, 40, WHITE);
    }
    
    // for(unsigned int i = 0; i < m_shockwaves.size(); i++)
        // DrawCircle(10.0f, 10.0f * (i + 1), 3.0f, GREEN);
    // for(unsigned int i = 0; i < k_charges; i++)
        // DrawText(std::to_string(m_charges[i]).c_str(), 30, 20 * (i + 1), 20, WHITE);
}

void ShockwaveManager::spawnShockwave(Vector2 p_pos, int p_horLimit, int p_verLimit){
    
    bool spawned = false;
    for(int i = 0; i < k_charges && !spawned; i++)
        if(m_charges[i] == 10000){
            m_shockwaves.push_back(Shockwave(p_pos, p_horLimit, p_verLimit));
            m_charges[i] = 0;
            spawned = true;
        }
}
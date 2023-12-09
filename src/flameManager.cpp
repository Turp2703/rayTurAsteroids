#include "flameManager.h"

#include "flame.h"

#include "raylib.h"

FlameManager::FlameManager(){
    /* */
}

void FlameManager::update(){
    for (auto it = m_flames.begin(); it != m_flames.end();)
        if (!it->isAlive())
            it = m_flames.erase(it);
        else {
            it->update();
            it++;
        }
}

void FlameManager::draw(){
    for(Flame flame: m_flames)
        flame.draw();
    
    // for(unsigned int i = 0; i < m_flames.size(); i++)
        // DrawCircle(10.0f, i*10.0f, 3.0f, GREEN);
}

void FlameManager::spawnFlame(Vector2 p_pos, float p_radAngle, int p_horLimit, int p_verLimit){
    //////////////////////////////////////////// check time since last
    float rndSpeed = GetRandomValue(k_minSpeed, k_maxSpeed);
    int degAngle = p_radAngle * RAD2DEG;
    float rndAngle = GetRandomValue(degAngle - k_opening, degAngle + k_opening);
    float rndSize = GetRandomValue(k_minSize, k_maxSize);
    m_flames.push_back(Flame(p_pos, rndAngle * DEG2RAD, rndSpeed, rndSize, p_horLimit, p_verLimit));
}
#include "laserManager.h"

#include "laser.h"

LaserManager::LaserManager(){
    /* */
}

void LaserManager::update(){
    for (auto it = m_lasers.begin(); it != m_lasers.end();)
        if (!it->isAlive())
            it = m_lasers.erase(it);
        else {
            it->update();
            it++;
        }
}

void LaserManager::draw(){
    // for(std::vector<Laser>::iterator it = m_lasers.begin(); it != m_lasers.end() ; it++) it->draw();
    for(Laser laser : m_lasers)
        laser.draw();
    
    for(unsigned int i = 0; i < m_lasers.size(); i++)
        DrawCircle(10.0f, i*10.0f, 3.0f, GREEN);
}

void LaserManager::spawnLaser(Vector2 p_pos, float p_radAngle, int p_horLimit, int p_verLimit){
    m_lasers.push_back(Laser(p_pos, p_radAngle, p_horLimit, p_verLimit));
}
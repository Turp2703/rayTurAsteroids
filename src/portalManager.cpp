#include "portalManager.h"

#include <iostream>

PortalManager::PortalManager(int p_screenWidth, int p_screenHeight)
    : m_screenWidth(p_screenWidth), m_screenHeight(p_screenHeight)
{
    /* */
}

void PortalManager::update(std::vector<Asteroid>& p_asteroids){
    for(auto& portal : m_portals)
        portal.update(p_asteroids);
    for (auto it = m_portals.begin(); it != m_portals.end();)
        if (!it->isAlive())
            it = m_portals.erase(it);
        else
            it++;
}

void PortalManager::draw(){
    for(auto& portal : m_portals)
        portal.draw();
        
    // for(unsigned int i = 0; i < m_portals.size(); i++)
        // DrawText(std::to_string(0).c_str(), 10 * i, 30, 20, WHITE);
}

void PortalManager::spawnPortal(Vector2 p_position){
    int groupCount = 10;
    int groupSize = 3;
    float angle = 0.f;
    float angleIncrement = 25.f;
    float interval = 0.5f;
    float size = 25.f;
    float speed = 1.2f;
    bool metal = true;
    bool shield = false;
    Portal p1(p_position, groupCount, groupSize, angle, angleIncrement, interval, m_screenWidth, m_screenHeight, size, speed, metal, shield);
    m_portals.push_back(p1);
}
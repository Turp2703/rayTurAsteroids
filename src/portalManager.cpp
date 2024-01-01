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
    int groupCount = GetRandomValue(2, 10);
    int groupSize = GetRandomValue(1, 8);
    float angle = GetRandomValue(0, 359);
    float angleIncrement = GetRandomValue(0, 90);
    float interval = GetRandomValue(1, 20) / 10.f;
    float size = GetRandomValue(15, 40);
    float speed = GetRandomValue(5, 20) / 10.f;
    bool metal = GetRandomValue(0, 1);
    bool shield = GetRandomValue(0, 1);
    Portal p1(p_position, groupCount, groupSize, angle, angleIncrement, interval, m_screenWidth, m_screenHeight, size, speed, metal, shield);
    m_portals.push_back(p1);
}
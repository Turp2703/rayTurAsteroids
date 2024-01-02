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
        
    if(p_asteroids.empty() && m_portals.empty())
        spawnPortal((Vector2){(float)GetRandomValue(50, m_screenWidth-50),(float)GetRandomValue(50, m_screenHeight-50)});
}

void PortalManager::draw(){
    for(auto& portal : m_portals)
        portal.draw();
        
    // for(unsigned int i = 0; i < m_portals.size(); i++)
        // DrawText(std::to_string(0).c_str(), 10 * i, 30, 20, WHITE);
}

void PortalManager::spawnPortal(Vector2 p_position){
    bool metal = GetRandomValue(0, 1);
    bool shield = metal ? GetRandomValue(0, 1) * GetRandomValue(0, 1) : GetRandomValue(0, 1);
    int groupCount, groupSize;
    if(metal && shield){
        groupSize = GetRandomValue(1, 8);
        groupCount = groupSize < 5 ? GetRandomValue(1, 4) : GetRandomValue(1, 2);
    }
    else if(metal || shield){
        groupSize = GetRandomValue(1, 8);
        groupCount = groupSize < 5 ? GetRandomValue(2, 8) : GetRandomValue(2, 4);
    }
    else{
        groupSize = GetRandomValue(1, 16);
        groupCount = groupSize < 5 ? GetRandomValue(2, 10) : GetRandomValue(2, 4);
    }
    float angle = GetRandomValue(0, 359);
    float angleIncrement = GetRandomValue(0, 1) && GetRandomValue(0, 1) ? 0 : GetRandomValue(0, 90);
    float interval = GetRandomValue(1, 20) / 10.f;
    float size = GetRandomValue(1, 3) * 15.f;
    float speed = GetRandomValue(5, 20) / 10.f;
    
    Portal p1(p_position, groupCount, groupSize, angle, angleIncrement, interval, m_screenWidth, m_screenHeight, size, speed, metal, shield);
    m_portals.push_back(p1);
}

void PortalManager::restart(){
    m_portals.clear();
}
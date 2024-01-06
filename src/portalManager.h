#pragma once

#include "asteroid.h"
#include "portal.h"

#include "raylib.h"

#include <vector>

class PortalManager{
    public:
        PortalManager(int, int);
        void update(std::vector<Asteroid>&, int&);
        void draw();
        void draw(Texture2D);
        void drawEffects(Texture2D);
        void spawnPortal(Vector2);
        void restart();
    private:
        std::vector<Portal> m_portals;
        int m_screenWidth;
        int m_screenHeight;
};
#pragma once

#include <vector>

#include "ship.h"
#include "laserManager.h"
#include "flameManager.h"
#include "shockwaveManager.h"
#include "asteroid.h"

class Game{
    public:
        Game();
        void init(const char*);
        void update();
        void draw();
    private:
        const int k_screenWidth = 800;
        const int k_screenHeight = 600;
        void shutdown();
        Ship player;
        LaserManager laserManager;
        FlameManager flameManager;
        ShockwaveManager shockwaveManager;
        std::vector<Asteroid> asteroids;
        // PortalManager
};
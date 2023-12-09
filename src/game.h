#pragma once

#include <vector>

#include "ship.h"
#include "laserManager.h"
#include "flameManager.h"
#include "asteroid.h"

class Game{
    public:
        Game();
        void init(const char* p_title);
        void update();
        void draw();
    private:
        const int k_screenWidth = 800;
        const int k_screenHeight = 600;
        void shutdown();
        Ship player;
        LaserManager laserManager;
        FlameManager flameManager;
        Asteroid ast1;
};
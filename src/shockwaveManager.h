#pragma once

#include "shockwave.h"

#include "raylib.h"

#include <vector>

class ShockwaveManager{
    public:
        ShockwaveManager();
        void update();
        void draw();
        void spawnShockwave(Vector2, int, int);
        //checkCollisions(std::vector<Asteroid>& asteroids);
    private:
        const int k_charges = 3; // 3
        const int k_maxCharge = 10000; // 10000
        const int k_chargeRecover = 50; // 50
        std::vector<Shockwave> m_shockwaves;
        int m_charges[3];
};
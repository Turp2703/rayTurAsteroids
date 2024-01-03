#pragma once

#include "shockwave.h"
#include "asteroid.h"

#include "raylib.h"

#include <vector>

class ShockwaveManager{
    public:
        ShockwaveManager();
        void update();
        void draw();
        void drawIndicators();
        void spawnShockwave(Vector2, int, int);
        void checkCollisions(std::vector<Asteroid>&);
        void restart();
    private:
        const int k_charges = 3; // 3
        const int k_maxCharge = 10000; // 10000
        const int k_chargeRecover = 25; // 25
        std::vector<Shockwave> m_shockwaves;
        int m_charges[3]; // 3
};
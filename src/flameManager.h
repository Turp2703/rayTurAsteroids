#pragma once

#include "flame.h"
#include "asteroid.h"

#include "raylib.h"

#include <vector>

class FlameManager{
    public:
        FlameManager();
        void update();
        void draw();
        void drawIndicators();
        void spawnFlame(Vector2, float, int, int);
        void checkCollisions(std::vector<Asteroid>&);
    private:
        const int k_minSpeed = 2; // 2
        const int k_maxSpeed = 6; // 6
        const int k_opening = 30; // 30
        const int k_minSize = 8;  // 8
        const int k_maxSize = 16; // 16
        const int k_maxCharge = 10000; // 10000
        const int k_chargeCooldown = 1; // 1
        const int k_chargeRecover = 100; // 100
        const int k_chargeConsumption = 100; // 100
        std::vector<Flame> m_flames;
        int m_charge;
        bool m_recharge;
        double m_lastTime;
};
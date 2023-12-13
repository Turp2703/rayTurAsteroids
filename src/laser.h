#pragma once

#include "projectile.h"

#include "raylib.h"

class Laser : public Projectile{
    public:
        Laser(Vector2, float, int, int);
        Laser(const Laser&);
        Laser& operator=(Laser&&) noexcept;
        void update();
        void draw();
        bool isAlive();
    private:
        const int k_maxLifeTime = 1; // 1
        const int k_speed = 15; // 15
        const int k_size = 3; // 3
        float m_startTime;
        float m_lifeTime;
};
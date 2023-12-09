#pragma once

#include "projectile.h"

#include "raylib.h"

class Laser : public Projectile{
    public:
        Laser(Vector2 p_pos, float p_radAngle, int p_horLimit, int p_verLimit);
        Laser(const Laser& other);
        Laser& operator=(Laser&& other) noexcept;
        void update();
        void draw();
        bool isAlive();
    private:
        const int k_maxLifeTime = 1; // 1
        const int k_speed = 15; // 15
        const int k_size = 3; // 3
};
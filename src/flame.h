#pragma once

#include "projectile.h"

#include "raylib.h"

class Flame : public Projectile{
    public:
        Flame(Vector2 p_pos, float p_radAngle, float p_speed, float p_size, int p_horLimit, int p_verLimit);
        Flame(const Flame& other);
        Flame& operator=(Flame&& other) noexcept;
        void update();
        void draw();
        bool isAlive();
    private:
        const float k_sizeLoss = 0.5f; // 0.5f
        float m_speed;
        float m_size;
};
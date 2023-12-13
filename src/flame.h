#pragma once

#include "projectile.h"

#include "raylib.h"

class Flame : public Projectile{
    public:
        Flame(Vector2, float, float, float, int, int);
        Flame(const Flame&);
        Flame& operator=(Flame&&) noexcept;
        void update();
        void draw();
        bool isAlive();
    private:
        const float k_sizeLoss = 0.5f; // 0.5f
        float m_speed;
        float m_size;
};
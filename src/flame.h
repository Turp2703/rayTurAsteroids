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
        Rectangle getHitBox();
        void destroy();
    private:
        const float k_sizeLoss = 0.4f; // 0.4f
        float m_speed;
        float m_size;
};
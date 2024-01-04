#pragma once

#include "projectile.h"

#include "raylib.h"

class Shockwave : public Projectile{
    public:
        Shockwave(Vector2, int, int);
        Shockwave(const Shockwave&);
        Shockwave& operator=(Shockwave&&) noexcept;
        void update();
        void draw();
        void draw(Texture2D);
        bool isAlive();
        Vector2 getPos();
        float getRadius();
        void destroy();
    private:
        const float k_size = 125.0f; // 125.0f
        const double k_lifeTime = 1.2f; // 1.2f
        double m_startTime;
};
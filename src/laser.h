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
        void draw(Texture2D&);
        bool isAlive();
        Rectangle getHitBox();
        void destroy();
    private:
        const int k_maxLifeTime = 1; // 1
        const int k_speed = 15; // 15
        const int k_size = 3; // 3
        float m_startTime;
        float m_lifeTime;
        Vector2 m_endPos;
};
#pragma once

#include "raylib.h"

class Projectile{
    public:
        Projectile(Vector2 p_pos, float p_radAngle, int p_horLimit, int p_verLimit);
        Projectile(const Projectile& other);
        virtual void update() = 0;
        virtual void draw() = 0;
        virtual bool isAlive() = 0;
    protected:
        bool m_alive;
        float m_startTime;
        float m_lifeTime;
        Vector2 m_position;
        float m_radAngle;
        int m_horizontalLimit;
        int m_verticalLimit;
};
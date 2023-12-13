#pragma once

#include "raylib.h"

class Projectile{
    public:
        Projectile(Vector2, float, int, int);
        Projectile(const Projectile&);
        virtual void update() = 0;
        virtual void draw() = 0;
        virtual bool isAlive() = 0;
    protected:
        bool m_alive;
        Vector2 m_position;
        float m_radAngle; // remove
        int m_horizontalLimit;
        int m_verticalLimit;
};
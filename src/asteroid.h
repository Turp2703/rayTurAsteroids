#pragma once

#include "raylib.h"

class Asteroid{
    public:
        Asteroid(int, int);
        void update();
        void draw();
        Rectangle getHitBox();
        void destroy();
        bool isAlive();
    private:
        Vector2 m_position;
        float m_size;
        int m_horizontalLimit;
        int m_verticalLimit;
        float m_speed;
        float m_angle;
        float m_radAngle;
        Rectangle m_hitBox;
        bool m_alive;
};
#pragma once

#include "raylib.h"

class Ship{
    public:
        Ship(int xpos, int ypos, float size);
    private:
        const int k_maxSpeed = 5; // 5
        const float k_acceleration = 0.2f; // 0.2f
        const float k_friction = 0.75f; // 0.75f
        Vector2 m_position;
        float m_speed;
        float m_acceleration;
        float m_angle;
        float m_radAngle;
        float m_size;
};
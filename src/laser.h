#pragma once

#include "raylib.h"

class Laser{
    public:
        Laser(Vector2 p_pos, float p_angle, int p_horLimit, int p_verLimit);
        Laser& operator=(const Laser& other);
        void update();
        void draw();
        bool isAlive();
    private:
        const int k_maxLifeTime = 1; // 1
        const int k_speed = 15; // 15
        const Vector2 k_size = {3, 10}; // 3,10
        bool m_alive;
        float m_startTime;
        float m_lifeTime;
        Vector2 m_position;
        float m_radAngle;
        int m_horizontalLimit;
        int m_verticalLimit;
};
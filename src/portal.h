#pragma once

#include "asteroid.h"

#include "raylib.h"

#include <vector>

class Portal{
    public:
        Portal(std::vector<Asteroid>&, Vector2, int, int, float, float, double, int, int, bool, bool);
        Portal(const Portal&);
        Portal& operator=(Portal&&) noexcept;
        void update();
        void draw();
        bool isAlive();
    private:
        const Vector2 k_size = { 40.f, 60.f }; // 40, 60
        std::vector<Asteroid>& m_asteroids;
        Vector2 m_position;
        int m_groupCount;
        int m_groupSize;
        float m_angle;
        float m_angleIncrement;
        double m_previousTime;
        double m_interval;
        int m_screenWidth;
        int m_screenHeight;
        // size
        // speed
        bool m_metals;
        bool m_shields;
        bool m_alive;
};
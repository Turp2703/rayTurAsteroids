#pragma once

#include "asteroid.h"
#include "particle.h"

#include "raylib.h"

#include <vector>

class Portal{
    public:
        Portal(Vector2, int, int, float, float, double, int, int, float, float, bool, bool);
        Portal(const Portal&);
        Portal& operator=(Portal&&) noexcept;
        void update(std::vector<Asteroid>&);
        void draw();
        void draw(Texture2D);
        void drawEffects(Texture2D);
        bool isAlive();
    private:
        const Vector2 k_size = { 40.f, 60.f }; // 40, 60
        const double k_warmUpTime = 1.0; // 1.0
        Vector2 m_position;
        int m_groupCount;
        int m_groupSize;
        float m_angle;
        float m_angleIncrement;
        double m_previousTime;
        double m_interval;
        int m_screenWidth;
        int m_screenHeight;
        float m_size;
        float m_speed;
        bool m_metals;
        bool m_shields;
        bool m_alive;
        double m_startTime;
        bool m_active;
        std::vector<Particle> m_particles;
};
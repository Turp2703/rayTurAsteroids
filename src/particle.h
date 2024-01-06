#pragma once

#include "raylib.h"

class Particle{
    public:
        Particle(Vector2, float, double);
        Particle(Vector2, float, double, float, float);
        Particle(const Particle&);
        Particle& operator=(Particle&&) noexcept;
        void update();
        void draw(Texture2D&, Color, bool);
        bool isAlive();
    protected:
        unsigned char mapTimeToAlpha(double, double, bool);
        bool m_alive;
        Vector2 m_position;
        float m_angle;
        double m_maxTime;
        float m_angleIncrement;
        float m_speed;
        double m_startTime;
};
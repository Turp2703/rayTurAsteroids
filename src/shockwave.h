#pragma once

#include "projectile.h"
#include "particle.h"

#include "raylib.h"

#include <vector>

class Shockwave : public Projectile{
    public:
        Shockwave(Vector2, int, int);
        Shockwave(const Shockwave&);
        Shockwave& operator=(Shockwave&&) noexcept;
        void update();
        void update(std::vector<Particle>&);
        void draw();
        bool isAlive();
        Vector2 getPos();
        float getRadius();
        void destroy();
    private:
        const float k_size = 125.0f; // 125.0f
        const double k_lifeTime = 1.2f; // 1.2f
        double m_startTime;
};
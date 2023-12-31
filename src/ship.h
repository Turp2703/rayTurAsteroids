#pragma once

#include "laserManager.h"
#include "flameManager.h"
#include "shockwaveManager.h"
#include "particle.h"

#include "raylib.h"

#include <vector>

class Ship{
    public:
        Ship(int, int, LaserManager&, FlameManager&, ShockwaveManager&);
        void update(Sound&, Sound&, Sound&);
        void draw();
        void draw(Texture2D&);
        void drawEffects(Texture2D&);
        Vector3 getHitBox();
        bool isAlive();
        void kill();
        void checkCollisions(std::vector<Asteroid>&, Sound&);
        void restart();
    private:
        const int k_maxSpeed = 5; // 5
        const float k_acceleration = 0.2f; // 0.2f
        const float k_friction = 0.75f; // 0.75f
        bool m_alive;
        Vector2 m_position;
        float m_size;
        int m_horizontalLimit;
        int m_verticalLimit;
        float m_speed;
        float m_acceleration;
        float m_angle;
        float m_radAngle;
        LaserManager& m_laserManager;
        FlameManager& m_flameManager;
        ShockwaveManager& m_shockwaveManager;
        Vector3 m_hitBox; // Circle, Position-Radius
        std::vector<Particle> m_fireParticles;
        std::vector<Particle> m_deathParticles;
};
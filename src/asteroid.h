#pragma once

#include "raylib.h"

class Asteroid{
    public:
        Asteroid(int, int);
        Asteroid(int, int, Vector2, float, float, float, bool, bool);
        Asteroid(const Asteroid&);
        Asteroid& operator=(Asteroid&&) noexcept;
        void update();
        void draw();
        Rectangle getHitBox();
        void destroy();
        bool isAlive();
        bool hasMetal();
        void toggleMetal();
        void addHeat();
        bool hasShield();
        void toggleShield();
        void enableShieldActive();
        void disableShieldActive();
    private:
        const int k_maxHeat = 1800; // 2400
        const int k_heatIncrease = 9; // 8
        const int k_heatDecrease = 6; // 6
        const int k_shieldCooldown = 10; // 10
        Vector2 m_position;
        float m_size;
        int m_horizontalLimit;
        int m_verticalLimit;
        float m_speed;
        float m_angle;
        float m_radAngle;
        Rectangle m_hitBox;
        bool m_alive;
        bool m_metal;
        int m_heat;
        bool m_shield;
        bool m_shieldActive;
        double m_shieldLossTime;
};
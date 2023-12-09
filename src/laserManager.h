#pragma once

#include "laser.h"

#include <vector>

class LaserManager{
    public:
        LaserManager();
        void update();
        void draw();
        void spawnLaser(Vector2 p_pos, float p_angle, int p_horLimit, int p_verLimit);
        //checkCollisions(std::vector<Asteroid>& asteroids);
    private:
        std::vector<Laser> m_lasers;
};
#pragma once

#include "laser.h"

#include <vector>

class LaserManager{
    public:
        LaserManager();
        void update();
        void draw();
        void spawnLaser(Vector2, float, int, int);
        //checkCollisions(std::vector<Asteroid>& asteroids);
    private:
        std::vector<Laser> m_lasers;
};
#pragma once

#include "laser.h"
#include "asteroid.h"

#include <vector>

class LaserManager{
    public:
        LaserManager();
        void update();
        void draw();
        void spawnLaser(Vector2, float, int, int);
        void checkCollisions(std::vector<Asteroid>&);
    private:
        std::vector<Laser> m_lasers;
};
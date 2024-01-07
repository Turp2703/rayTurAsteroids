#pragma once

#include "laser.h"
#include "asteroid.h"

#include <vector>

class LaserManager{
    public:
        LaserManager();
        void update();
        void draw();
        void draw(Texture2D&);
        void spawnLaser(Vector2, float, int, int, Sound&);
        void checkCollisions(std::vector<Asteroid>&, int&);
        void restart();
    private:
        std::vector<Laser> m_lasers;
};
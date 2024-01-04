#pragma once

#include "laser.h"
#include "asteroid.h"

#include <vector>

class LaserManager{
    public:
        LaserManager();
        void update();
        void draw();
        void draw(Texture2D);
        void spawnLaser(Vector2, float, int, int);
        void checkCollisions(std::vector<Asteroid>&, int&);
        void restart();
    private:
        std::vector<Laser> m_lasers;
        Texture2D* m_textureLaser;
};
#pragma once

#include "flame.h"

#include "raylib.h"

#include <vector>

class FlameManager{
    public:
        FlameManager();
        void update();
        void draw();
        void spawnFlame(Vector2 p_pos, float p_angle, int p_horLimit, int p_verLimit);
        //checkCollisions(std::vector<Asteroid>& asteroids);
    private:
        const int k_minSpeed = 2; //
        const int k_maxSpeed = 6; //
        const int k_opening = 30; //
        const int k_minSize = 8;  //
        const int k_maxSize = 16; //
        std::vector<Flame> m_flames;
};
#pragma once

#include "raylib.h"

class BackgroundManager{
    public:
        BackgroundManager();
        void update();
        void draw(Texture2D(&)[7]);
    private:
        const int k_width = 26;
        const int k_height = 19;
        float m_movement;
        int m_grid[26][19];
};
#pragma once

#include "raylib.h"

class BackgroundManager{
    public:
        BackgroundManager();
        void update();
        void draw(Texture2D[]);
    private:
        const int k_width = 26;
        const int k_height = 19;
        int m_grid[26][19];
};
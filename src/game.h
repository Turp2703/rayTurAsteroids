#pragma once

#include "scene.h"

class Game{
    public:
        Game();
        void init(const char*);
        void update();
        void draw();
        void changeScene(Scene*);
    private:
        const int k_screenWidth = 800;
        const int k_screenHeight = 600;
        void shutdown();
        Scene* currentScene;
};
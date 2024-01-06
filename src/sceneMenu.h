#pragma once

#include "scene.h"

#include "raylib.h"

class SceneMenu : public Scene{
    public:
        SceneMenu(int, int);
        void update(Game*);
        void draw();
        ~SceneMenu();
    private:
        const Rectangle button = { 300, 225, 200, 100 };
        Texture2D texLogo;
        bool mouseOverButton;
        bool transitioning;
        unsigned char alpha;
};
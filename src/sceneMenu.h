#pragma once

#include "scene.h"

class SceneMenu : public Scene{
    public:
        SceneMenu(int, int);
        void update(Game*);
        void draw();
};
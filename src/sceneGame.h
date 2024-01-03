#pragma once

#include "scene.h"
#include "game.h"
#include "ship.h"
#include "laserManager.h"
#include "flameManager.h"
#include "shockwaveManager.h"
#include "asteroid.h"
#include "portalManager.h"

#include <vector>

class SceneGame : public Scene{
    public:
        SceneGame(int, int);
        void update(Game*);
        void draw();
    private:
        Ship player;
        LaserManager laserManager;
        FlameManager flameManager;
        ShockwaveManager shockwaveManager;
        std::vector<Asteroid> asteroids;
        PortalManager portalManager;
        int score;
};
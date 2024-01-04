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
        ~SceneGame();
    private:
        Ship player;
        LaserManager laserManager;
        FlameManager flameManager;
        ShockwaveManager shockwaveManager;
        std::vector<Asteroid> asteroids;
        PortalManager portalManager;
        int score;
        
        Texture2D texShip;
        Texture2D texShipDead;
        Texture2D texLaser;
        Texture2D texShockwave;
        Texture2D texFlames[4];
        Texture2D texPortal;
};
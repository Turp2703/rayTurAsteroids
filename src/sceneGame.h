#pragma once

#include "scene.h"
#include "game.h"
#include "ship.h"
#include "laserManager.h"
#include "flameManager.h"
#include "shockwaveManager.h"
#include "asteroid.h"
#include "portalManager.h"
#include "backgroundManager.h"

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
        BackgroundManager backgroundManager;
        int score;
        
        Texture2D texShip;
        Texture2D texLaser;
        Texture2D texFlames[4];
        Texture2D texPortal;
        Texture2D texAsteroid;
        Texture2D texMetal;
        Texture2D texShield;
        Texture2D texBackground[7];
        Texture2D texParticle;
        
        Sound soundStart;
        Sound soundImpact;
        Sound soundLaser;
        Sound soundFlames;
        Sound soundShockwave;
        Sound soundDeath;
        
        std::vector<Particle> m_asteroidParticles;
};
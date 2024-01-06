#include "sceneGame.h"

#include "sceneMenu.h"

#include <iostream>
#include <string>

SceneGame::SceneGame(int p_screenWidth, int p_screenHeight)
    : Scene(p_screenWidth, p_screenHeight)
    , player(p_screenWidth, p_screenHeight - 50, laserManager, flameManager, shockwaveManager)
    , portalManager(p_screenWidth, p_screenHeight - 50)
{
    score = 0;
    portalManager.spawnPortal((Vector2){(float)GetRandomValue(50, m_screenWidth-50),(float)GetRandomValue(50, m_screenHeight-100)});
    
    // Textures
    texShip = LoadTexture("assets/ship.png");
    texLaser = LoadTexture("assets/laser.png");
    texShockwave = LoadTexture("assets/shockwave.png");
    texPortal = LoadTexture("assets/portal.png");
    texAsteroid = LoadTexture("assets/asteroid.png");
    texMetal = LoadTexture("assets/metal.png");
    texShield = LoadTexture("assets/shield.png");
    texParticle = LoadTexture("assets/particle.png");
    for(int i = 0; i < (int)(sizeof(texFlames) / sizeof (texFlames[0])); i++)
        texFlames[i] = LoadTexture(("assets/flame" + std::to_string(i + 1) + ".png").c_str());
    for(int i = 0; i < (int)(sizeof(texBackground) / sizeof (texBackground[0])); i++)
        texBackground[i] = LoadTexture(("assets/bg" + std::to_string(i + 1) + ".png").c_str());
}

void SceneGame::update(Game* p_game){
    player.update();
    laserManager.update();
    flameManager.update();
    shockwaveManager.update();
    for(auto& asteroid : asteroids)
        asteroid.update(score, m_asteroidParticles);
    for (auto it = asteroids.begin(); it != asteroids.end();)
        if (!it->isAlive())
            it = asteroids.erase(it);
        else
            it++;
    player.checkCollisions(asteroids);
    laserManager.checkCollisions(asteroids, score);
    flameManager.checkCollisions(asteroids);
    shockwaveManager.checkCollisions(asteroids);
    portalManager.update(asteroids, score);
    backgroundManager.update();
    
    // Particles
    for (auto it = m_asteroidParticles.begin(); it != m_asteroidParticles.end();){
        if (!it->isAlive()){
            it = m_asteroidParticles.erase(it);
        }
        else {
            it->update();
            it++;
        }
    }
    
    // GAME OVER
    if(!player.isAlive()){
        if(IsKeyPressed(KEY_R)){
            asteroids.clear();
            player.restart();
            portalManager.restart();
            laserManager.restart();
            flameManager.restart();
            shockwaveManager.restart();
            score = 0;
            portalManager.spawnPortal((Vector2){(float)GetRandomValue(50, m_screenWidth-50),(float)GetRandomValue(50, m_screenHeight-100)});
        }
        else if(IsKeyPressed(KEY_T)){
            p_game->changeScene(new SceneMenu(m_screenWidth, m_screenHeight));
        }
    }
    
    // if(IsKeyPressed(KEY_ONE))
        // p_game->changeScene(new SceneMenu(m_screenWidth, m_screenHeight));
}

void SceneGame::draw(){
    // Background
    backgroundManager.draw(texBackground);
    
    // Effects
    player.drawEffects(texParticle);
    portalManager.drawEffects(texParticle);
    for(auto& particle : m_asteroidParticles)
        particle.draw(texParticle, LIGHTGRAY, true);
    for(auto& asteroid : asteroids)
        asteroid.drawEffects(texParticle);
    
    // Objects
    laserManager.draw(texLaser);
    for(auto& asteroid : asteroids)
        asteroid.draw(texAsteroid, texMetal, texShield);
    flameManager.draw(texFlames);
    shockwaveManager.draw(texShockwave);
    portalManager.draw(texPortal);
    player.draw(texShip);
    
    // UI
    DrawRectangle(-1, m_screenHeight - 50, m_screenWidth + 1, 51, BLACK);
    DrawLine(-1, m_screenHeight - 50, m_screenWidth + 1, m_screenHeight - 50, GREEN);
    flameManager.drawIndicators();
    shockwaveManager.drawIndicators();
    std::string scoreText = "SCORE: " + std::to_string(score);
    DrawText(scoreText.c_str(), 30, m_screenHeight - 40, 35, GREEN);
    
    // Game Over Screen
    if(!player.isAlive()){
        const char *gameOverText = "GAME OVER";
        const char *restartText = "PRESS [R] TO RESTART";
        const char *menuText = "PRESS [T] TO RETURN";
        DrawRectangle(m_screenWidth / 2 - MeasureText(restartText, 20) / 2 - 15, m_screenHeight / 2 - 45, MeasureText(restartText, 20) + 30, 140, GREEN);
        DrawRectangle(m_screenWidth / 2 - MeasureText(restartText, 20) / 2 - 10, m_screenHeight / 2 - 40, MeasureText(restartText, 20) + 20, 130, BLACK);
        DrawText(scoreText.c_str(), m_screenWidth / 2 - MeasureText(scoreText.c_str(), 20) / 2, m_screenHeight / 2 - 30, 20, GREEN);
        DrawText(gameOverText, m_screenWidth / 2 - MeasureText(gameOverText, 20) / 2, m_screenHeight / 2, 20, GREEN);
        DrawText(restartText, m_screenWidth / 2 - MeasureText(restartText, 20) / 2, m_screenHeight / 2 + 30, 20, GREEN);
        DrawText(menuText, m_screenWidth / 2 - MeasureText(menuText, 20) / 2, m_screenHeight / 2 + 60, 20, GREEN);
    }
    
    // DrawFPS(10, 10);
    // for(unsigned int i = 0; i < asteroids.size(); i++)
        // DrawText(std::to_string(0).c_str(), 10 * i, 30, 20, WHITE);
}

SceneGame::~SceneGame(){
    UnloadTexture(texShip);
    UnloadTexture(texLaser);
    UnloadTexture(texShockwave);
    UnloadTexture(texPortal);
    UnloadTexture(texAsteroid);
    UnloadTexture(texMetal);
    UnloadTexture(texShield);
    UnloadTexture(texParticle);
    for(int i = 0; i < (int)(sizeof(texFlames) / sizeof (texFlames[0])); i++)
        UnloadTexture(texFlames[i]);
    for(int i = 0; i < (int)(sizeof(texBackground) / sizeof (texBackground[0])); i++)
        UnloadTexture(texBackground[i]);
}
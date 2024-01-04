#include "sceneGame.h"

#include "sceneMenu.h"

#include <string>

SceneGame::SceneGame(int p_screenWidth, int p_screenHeight)
    : Scene(p_screenWidth, p_screenHeight)
    , player(p_screenWidth, p_screenHeight - 50, laserManager, flameManager, shockwaveManager)
    , portalManager(p_screenWidth, p_screenHeight - 50)
{
    score = 0;
    portalManager.spawnPortal((Vector2){(float)GetRandomValue(50, m_screenWidth-50),(float)GetRandomValue(50, m_screenHeight-100)});
    
    
    TraceLog(LOG_WARNING, GetApplicationDirectory());
    
    
    // Textures
    texShip = LoadTexture("assets/ship.png");
    texShipDead = LoadTexture("assets/shipDead.png");
    texLaser = LoadTexture("assets/laser.png");
    texShockwave = LoadTexture("assets/shockwave.png");
    texFlames[0] = LoadTexture("assets/flame1.png");
    texFlames[1] = LoadTexture("assets/flame2.png");
    texFlames[2] = LoadTexture("assets/flame3.png");
    texFlames[3] = LoadTexture("assets/flame4.png");
    texPortal = LoadTexture("assets/portal.png");
}

void SceneGame::update(Game* p_game){
    player.update();
    laserManager.update();
    flameManager.update();
    shockwaveManager.update();
    for(auto& asteroid : asteroids)
        asteroid.update(score);
    player.checkCollisions(asteroids);
    laserManager.checkCollisions(asteroids, score);
    flameManager.checkCollisions(asteroids);
    shockwaveManager.checkCollisions(asteroids);
    for (auto it = asteroids.begin(); it != asteroids.end();)
        if (!it->isAlive())
            it = asteroids.erase(it);
        else
            it++;
    portalManager.update(asteroids, score);
    
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
            /* */
        }
    }
    
    if(IsKeyPressed(KEY_ONE))
        p_game->changeScene(new SceneMenu(m_screenWidth, m_screenHeight));
    
    // // Asteroid debug
    // if(IsKeyPressed(KEY_P)){
        // asteroids.push_back(Asteroid(m_screenWidth, m_screenHeight));
    // }
    // if(IsKeyPressed(KEY_O)){
        // Asteroid ast = Asteroid(m_screenWidth, m_screenHeight);
        // ast.toggleMetal();
        // asteroids.push_back(ast);
    // }
    // if(IsKeyPressed(KEY_I)){
        // Asteroid ast = Asteroid(m_screenWidth, m_screenHeight);
        // ast.toggleShield();
        // ast.enableShieldActive();
        // asteroids.push_back(ast);
    // }
    // if(IsKeyPressed(KEY_U)){
        // Asteroid ast = Asteroid(m_screenWidth, m_screenHeight);
        // ast.toggleMetal();
        // ast.toggleShield();
        // ast.enableShieldActive();
        // asteroids.push_back(ast);
    // }
    // if(IsKeyDown(KEY_Y)){
        // // Vector2 pos = { (float)GetRandomValue(0, m_screenWidth), (float)GetRandomValue(0, m_screenHeight) };
        // Vector2 pos = { m_screenWidth / 2.f, m_screenHeight / 2.f };
        // float size = GetRandomValue(15, 40);
        // float speed = GetRandomValue(5, 20) / 10.0f;
        // float angle = GetRandomValue(0, 359);
        // bool metal = GetRandomValue(0, 1);
        // bool shield = GetRandomValue(0, 1);
        // Asteroid ast(m_screenWidth, k_screenHeight, pos, size, speed, angle, metal, shield);
        // asteroids.push_back(ast);
    // }
    // // Portal Debug
    // if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        // portalManager.spawnPortal( {(float)GetMouseX(), (float)GetMouseY() });
    // if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        // asteroids.clear();
}

void SceneGame::draw(){
        // Objects
    laserManager.draw(texLaser);
    for(auto& asteroid : asteroids)
        asteroid.draw();
    flameManager.draw(texFlames);
    shockwaveManager.draw(texShockwave);
    portalManager.draw(texPortal);
    player.draw(texShip, texShipDead);
    
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
    UnloadTexture(texShipDead);
    UnloadTexture(texLaser);
    UnloadTexture(texShockwave);
    for(int i = 0; i < 4; i++)
        UnloadTexture(texFlames[i]);
    UnloadTexture(texPortal);
}
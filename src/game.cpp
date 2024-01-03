#include "game.h"

#include "raylib.h"

#include <iostream>
#include <string>

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

Game::Game()
    : player(k_screenWidth, k_screenHeight - 50, laserManager, flameManager, shockwaveManager)
    , portalManager(k_screenWidth, k_screenHeight - 50)
{
    score = 0;
    portalManager.spawnPortal((Vector2){(float)GetRandomValue(50, k_screenWidth-50),(float)GetRandomValue(50, k_screenHeight-100)});
}

void UpdateDrawFrame(void* arg){
    Game* instance = static_cast<Game*>(arg);
    instance->update();
    BeginDrawing();
        instance->draw();
    EndDrawing();
}
void Game::init(const char* p_title){
    InitWindow(k_screenWidth, k_screenHeight, p_title);
    
    #if defined(PLATFORM_WEB)
        emscripten_set_main_loop_arg(&UpdateDrawFrame, this, 0, 1);
    #else
        SetTargetFPS(60);   
        while (!WindowShouldClose()) { UpdateDrawFrame(this); }
    #endif
}

void Game::update(){
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
            portalManager.spawnPortal((Vector2){(float)GetRandomValue(50, k_screenWidth-50),(float)GetRandomValue(50, k_screenHeight-100)});
            
        }
        else if(IsKeyPressed(KEY_T)){
            /* */
        }
    }
    
    // // Asteroid debug
    // if(IsKeyPressed(KEY_P)){
        // asteroids.push_back(Asteroid(k_screenWidth, k_screenHeight));
    // }
    // if(IsKeyPressed(KEY_O)){
        // Asteroid ast = Asteroid(k_screenWidth, k_screenHeight);
        // ast.toggleMetal();
        // asteroids.push_back(ast);
    // }
    // if(IsKeyPressed(KEY_I)){
        // Asteroid ast = Asteroid(k_screenWidth, k_screenHeight);
        // ast.toggleShield();
        // ast.enableShieldActive();
        // asteroids.push_back(ast);
    // }
    // if(IsKeyPressed(KEY_U)){
        // Asteroid ast = Asteroid(k_screenWidth, k_screenHeight);
        // ast.toggleMetal();
        // ast.toggleShield();
        // ast.enableShieldActive();
        // asteroids.push_back(ast);
    // }
    // if(IsKeyDown(KEY_Y)){
        // // Vector2 pos = { (float)GetRandomValue(0, k_screenWidth), (float)GetRandomValue(0, k_screenHeight) };
        // Vector2 pos = { k_screenWidth / 2.f, k_screenHeight / 2.f };
        // float size = GetRandomValue(15, 40);
        // float speed = GetRandomValue(5, 20) / 10.0f;
        // float angle = GetRandomValue(0, 359);
        // bool metal = GetRandomValue(0, 1);
        // bool shield = GetRandomValue(0, 1);
        // Asteroid ast(k_screenWidth, k_screenHeight, pos, size, speed, angle, metal, shield);
        // asteroids.push_back(ast);
    // }
    // // Portal Debug
    // if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        // portalManager.spawnPortal( {(float)GetMouseX(), (float)GetMouseY() });
    // if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        // asteroids.clear();
}

void Game::draw(){
    ClearBackground(BLACK);
    
    // Objects
    laserManager.draw();
    for(auto& asteroid : asteroids)
        asteroid.draw();
    flameManager.draw();
    shockwaveManager.draw();
    portalManager.draw();
    player.draw();
    
    // UI
    DrawRectangle(-1, k_screenHeight - 50, k_screenWidth + 1, 51, BLACK);
    DrawLine(-1, k_screenHeight - 50, k_screenWidth + 1, k_screenHeight - 50, GREEN);
    flameManager.drawIndicators();
    shockwaveManager.drawIndicators();
    std::string scoreText = "SCORE: " + std::to_string(score);
    DrawText(scoreText.c_str(), 30, k_screenHeight - 40, 35, GREEN);
    
    // Game Over Screen
    if(!player.isAlive()){
        const char *gameOverText = "GAME OVER";
        const char *restartText = "PRESS [R] TO RESTART";
        const char *menuText = "PRESS [T] TO RETURN";
        DrawRectangle(k_screenWidth / 2 - MeasureText(restartText, 20) / 2 - 15, k_screenHeight / 2 - 45, MeasureText(restartText, 20) + 30, 140, GREEN);
        DrawRectangle(k_screenWidth / 2 - MeasureText(restartText, 20) / 2 - 10, k_screenHeight / 2 - 40, MeasureText(restartText, 20) + 20, 130, BLACK);
        DrawText(scoreText.c_str(), k_screenWidth / 2 - MeasureText(scoreText.c_str(), 20) / 2, k_screenHeight / 2 - 30, 20, GREEN);
        DrawText(gameOverText, k_screenWidth / 2 - MeasureText(gameOverText, 20) / 2, k_screenHeight / 2, 20, GREEN);
        DrawText(restartText, k_screenWidth / 2 - MeasureText(restartText, 20) / 2, k_screenHeight / 2 + 30, 20, GREEN);
        DrawText(menuText, k_screenWidth / 2 - MeasureText(menuText, 20) / 2, k_screenHeight / 2 + 60, 20, GREEN);
    }
    
    // DrawFPS(10, 10);
    // for(unsigned int i = 0; i < asteroids.size(); i++)
        // DrawText(std::to_string(0).c_str(), 10 * i, 30, 20, WHITE);
}

void Game::shutdown(){
    CloseWindow();
}
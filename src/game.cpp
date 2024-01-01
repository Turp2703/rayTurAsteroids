#include "game.h"

#include "raylib.h"

#include <iostream>

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

Game::Game()
    : player(k_screenWidth, k_screenHeight, laserManager, flameManager, shockwaveManager)
    , portalManager(k_screenWidth, k_screenHeight)
{
    /* */
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
        asteroid.update();
    player.checkCollisions(asteroids);
    laserManager.checkCollisions(asteroids);
    flameManager.checkCollisions(asteroids);
    shockwaveManager.checkCollisions(asteroids);
    for (auto it = asteroids.begin(); it != asteroids.end();)
        if (!it->isAlive())
            it = asteroids.erase(it);
        else
            it++;
    portalManager.update(asteroids);
    
    // Asteroid debug
    if(IsKeyPressed(KEY_P)){
        asteroids.push_back(Asteroid(k_screenWidth, k_screenHeight));
    }
    if(IsKeyPressed(KEY_O)){
        Asteroid ast = Asteroid(k_screenWidth, k_screenHeight);
        ast.toggleMetal();
        asteroids.push_back(ast);
    }
    if(IsKeyPressed(KEY_I)){
        Asteroid ast = Asteroid(k_screenWidth, k_screenHeight);
        ast.toggleShield();
        ast.enableShieldActive();
        asteroids.push_back(ast);
    }
    if(IsKeyPressed(KEY_U)){
        Asteroid ast = Asteroid(k_screenWidth, k_screenHeight);
        ast.toggleMetal();
        ast.toggleShield();
        ast.enableShieldActive();
        asteroids.push_back(ast);
    }
    if(IsKeyDown(KEY_Y)){
        // Vector2 pos = { (float)GetRandomValue(0, k_screenWidth), (float)GetRandomValue(0, k_screenHeight) };
        Vector2 pos = { k_screenWidth / 2.f, k_screenHeight / 2.f };
        float size = GetRandomValue(15, 40);
        float speed = GetRandomValue(5, 20) / 10.0f;
        float angle = GetRandomValue(0, 359);
        bool metal = GetRandomValue(0, 1);
        bool shield = GetRandomValue(0, 1);
        Asteroid ast(k_screenWidth, k_screenHeight, pos, size, speed, angle, metal, shield);
        asteroids.push_back(ast);
    }
    // Portal Debug
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        portalManager.spawnPortal( {(float)GetMouseX(), (float)GetMouseY() });
    }
}

void Game::draw(){
    ClearBackground(BLACK);
    player.draw();
    laserManager.draw();
    flameManager.draw();
    shockwaveManager.draw();
    for(auto& asteroid : asteroids)
        asteroid.draw();
    portalManager.draw();
    
    // DrawFPS(10, 10);
    // for(unsigned int i = 0; i < asteroids.size(); i++)
        // DrawText(std::to_string(0).c_str(), 10 * i, 30, 20, WHITE);
}

void Game::shutdown(){
    CloseWindow();
}
#include "game.h"

#include "raylib.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

Game::Game()
    : player(k_screenWidth, k_screenHeight, laserManager, flameManager, shockwaveManager)
{
    asteroids.push_back(Asteroid(k_screenWidth, k_screenHeight));
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
            it = asteroids.erase(it); // check shield & metal after
        else
            it++;
    
    
    
    if(IsKeyPressed(KEY_P))
        asteroids.push_back(Asteroid(k_screenWidth, k_screenHeight));
    if(IsKeyPressed(KEY_O)){
        Asteroid ast = Asteroid(k_screenWidth, k_screenHeight);
        ast.toggleMetal();
        asteroids.push_back(ast);
    }
    if(IsKeyPressed(KEY_I)){
        Asteroid ast = Asteroid(k_screenWidth, k_screenHeight);
        ast.toggleShield();
        asteroids.push_back(ast);
    }
    if(IsKeyPressed(KEY_U)){
        Asteroid ast = Asteroid(k_screenWidth, k_screenHeight);
        ast.toggleMetal();
        ast.toggleShield();
        asteroids.push_back(ast);
    }
}

void Game::draw(){
    ClearBackground(BLACK);
    // DrawFPS(10, 10);
    player.draw();
    laserManager.draw();
    flameManager.draw();
    shockwaveManager.draw();
    for(auto& asteroid : asteroids)
        asteroid.draw();
}

void Game::shutdown(){
    CloseWindow();
}
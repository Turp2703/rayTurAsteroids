#include "game.h"
#include "globals.h"

#include "raylib.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

Game::Game()
    : player(k_screenWidth / 2, k_screenHeight / 2, 20.0f){
    /**/
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
}

void Game::draw(){
    ClearBackground(BLACK);
    DrawFPS(10, 10);
    player.draw();
}

void Game::shutdown(){
    CloseWindow();
}
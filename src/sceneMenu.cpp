#include "sceneMenu.h"

#include "sceneGame.h"

#include "raylib.h"

#include <iostream>

SceneMenu::SceneMenu(int p_screenWidth, int p_screenHeight)
    : Scene(p_screenWidth, p_screenHeight)
{
    // COSMIC PURSUIT
    texLogo = LoadTexture("assets/logo.png");
    
    mouseOverButton = false;
    transitioning = false;
    alpha = 0;
    
    soundStart = LoadSound("assets/start.wav"); 
}

void SceneMenu::update(Game* p_game){
    // if(IsKeyPressed(KEY_TWO))
        // p_game->changeScene(new SceneGame(m_screenWidth, m_screenHeight));
    mouseOverButton = CheckCollisionPointRec(GetMousePosition(), button);
    if(transitioning){
        if(alpha < 252)
            alpha += 3;
        else
            p_game->changeScene(new SceneGame(m_screenWidth, m_screenHeight));
    }
    else if((mouseOverButton && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) || IsKeyPressed(KEY_ENTER)){
        transitioning = true;
        PlaySound(soundStart);
    }
}

void SceneMenu::draw(){
    // Title
    DrawTexturePro( texLogo
                  , { 0.f, 0.f, (float)texLogo.width, (float)texLogo.height }
                  , { 50.f, 50.f, 700.f, 100.f }
                  , { 0.f, 0.f }
                  , 0.f
                  , WHITE);
    
    // Play button
    if(mouseOverButton){
        DrawRectangleRec(button, LIME);
        DrawText("PLAY", 400 - MeasureText("PLAY", 50) / 2, 250, 50, BLACK);
    }
    else{
        DrawText("PLAY", 400 - MeasureText("PLAY", 50) / 2, 250, 50, GREEN);
    }
    DrawRectangleLinesEx(button, 2.f, GREEN);
    
    // Guide
    DrawRectangleLines(25, 400, 750, 175, GREEN);
    DrawText("Asteroid summoning portals will appear, you must destroy them all using your lasers.", 35, 410, 18, GREEN);
    DrawText("Use the flamethrower to heat metal and the electric shock to remove shields.", 35, 430, 18, GREEN);
    DrawText("Try not to crash into any of them, our you will fail.", 35, 450, 18, GREEN);
    DrawText("[W] to move ship forward", 35, 490, 18, GREEN);
    DrawText("[A] to rotate ship counterclockwise", 35, 510, 18, GREEN);
    DrawText("[S] to move ship backwards", 35, 530, 18, GREEN);
    DrawText("[D] to rotate ship clockwise", 35, 550, 18, GREEN);
    DrawText("[J] to fire lasers", 435, 500, 18, GREEN);
    DrawText("[K] to use flamethrower", 435, 520, 18, GREEN);
    DrawText("[L] to use electric shock", 435, 540, 18, GREEN);
    
    if(transitioning)
        DrawRectangle(0, 0, m_screenWidth, m_screenHeight, { 0, 0, 0, alpha } );
}

SceneMenu::~SceneMenu(){
    UnloadTexture(texLogo);
    UnloadSound(soundStart);
}
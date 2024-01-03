#include "sceneMenu.h"

#include "sceneGame.h"

#include "raylib.h"

SceneMenu::SceneMenu(int p_screenWidth, int p_screenHeight)
    : Scene(p_screenWidth, p_screenHeight)
{
    
}

void SceneMenu::update(Game* p_game){
    if(IsKeyPressed(KEY_TWO))
        p_game->changeScene(new SceneGame(m_screenWidth, m_screenHeight));
}

void SceneMenu::draw(){
    DrawRectangle(20, 30, 40, 50, RED);
}
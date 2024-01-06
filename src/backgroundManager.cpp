#include "backgroundManager.h"

BackgroundManager::BackgroundManager(){
    for(int i = 0; i < k_width; i++){
        for(int j = 0; j < k_height; j++){
            if(GetRandomValue(0, 1) && GetRandomValue(0, 1))
                m_grid[i][j] = 0;
            else
                m_grid[i][j] = GetRandomValue(0,6);
        }
    }
}

void BackgroundManager::update(){
    
}

void BackgroundManager::draw(Texture2D p_texture[7]){
    for(int i = 0; i < k_width; i++){
        for(int j = 0; j < k_height; j++){
            DrawTextureEx(p_texture[m_grid[i][j]], {i*32.f, j*32.f}, 0.f, 2.f, WHITE);
        }
    }
}
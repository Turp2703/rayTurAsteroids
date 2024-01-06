#include "backgroundManager.h"

BackgroundManager::BackgroundManager(){
    for(int i = 0; i < k_width; i++){
        for(int j = 0; j < k_height; j++){
            if(GetRandomValue(0, 1))
                m_grid[i][j] = 0;
            else
                m_grid[i][j] = GetRandomValue(0,6);
        }
    }
    m_movement = 0.f;
}

void BackgroundManager::update(){
    
}

void BackgroundManager::draw(Texture2D p_texture[7]){
    for(int i = 0; i < k_width; i++){
        for(int j = -1; j < k_height - 1; j++){
            DrawTextureEx(p_texture[m_grid[i][j + 1]], {i*32.f, j*32.f + m_movement}, 0.f, 2.f, WHITE);
        }
    }
    
    if(m_movement > 31.f){
        m_movement = 0.f;
        
        // Move rows
        for (int i = k_height - 1; i > 0; i--) {
            for (int j = 0; j < k_width; j++) {
                m_grid[j][i] = m_grid[j][i - 1];
            }
        }
        
        // Place new top row
        for(int i = 0; i < k_width; i++){
            if(GetRandomValue(0, 1))
                m_grid[i][0] = 0;
            else
                m_grid[i][0] = GetRandomValue(0,6);
        }
    }
    else{
        m_movement += 1.f;
    }
}
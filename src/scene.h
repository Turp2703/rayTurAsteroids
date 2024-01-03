#pragma once

class Game;

class Scene{
    public:
        Scene(int, int);
        virtual void update(Game*) = 0;
        virtual void draw() = 0;
        virtual ~Scene() = 0;
    protected:
        int m_screenWidth;
        int m_screenHeight;
};
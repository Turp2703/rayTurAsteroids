#pragma once

class Game{
    public:
        Game();
        void init(const char* p_title);
        void update();
        void draw();
    private:
        void shutdown();
};
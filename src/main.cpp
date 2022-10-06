#pragma once
#include "Game.h"

int main(int argc, char* argv[])
{
    if (Game::GetInstance()->init("Need For A+", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, 0))
    {
        Game::GetInstance()->Prepare();

        while (Game::GetInstance()->running())
        {
            Game::GetInstance()->handleEvents();
            Game::GetInstance()->update();
            Game::GetInstance()->render();
            SDL_Delay(25); // 초당 40프레임
        }
    }
    Game::GetInstance()->clean();
    return 0;
}
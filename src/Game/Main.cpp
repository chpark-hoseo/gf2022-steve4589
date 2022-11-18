#include "Game.h"
#include <State_Play.h>

const int FPS = 60;
const float DELAY_TIME = 1000.0f / FPS;

int main(int argc, char* argv[])
{
    Uint32 frameStart, frameTime;
    if (Game::GetInstance()->init("Need For Grade", 0, 10, SCREEN_WIDTH, SCREEN_HEIGHT, 0))
    {
        frameStart = SDL_GetTicks(); 
        Game::GetInstance()->ChangeState(State_Play::GetInstance()); //StartLogo로 바꾸기

        while (Game::GetInstance()->running())
        {
            Game::GetInstance()->handleEvents();
            Game::GetInstance()->update();
            Game::GetInstance()->render();

            frameTime = SDL_GetTicks() - frameStart;  //0부터 다시 카운트
            if (frameTime < DELAY_TIME) {
                SDL_Delay((int)(DELAY_TIME - frameTime)); //60fps만큼 일정하게 작동
            }
        }
    }
    Game::GetInstance()->quit();

    return 0;
}
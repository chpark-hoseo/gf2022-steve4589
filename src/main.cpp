#pragma once
#include "Game.h"
Game* g_game = 0;

int main(int argc, char* argv[])
{
    g_game = new Game();

    g_game->init("Game Class", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    while (g_game->running()) {
        g_game->handleEvents();
        g_game->update();
        g_game->render();
        SDL_Delay(10); 
    }
    g_game->clean();
    return 0;
}
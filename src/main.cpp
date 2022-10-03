﻿#pragma once
#include "Game.h"

Game* g_game = 0;

int main(int argc, char* argv[])
{
    g_game = new Game();

    if (g_game->init("Need For A+", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, 0))
    {
        g_game->Prepare();

        while (g_game->running())
        {
            g_game->handleEvents();
            g_game->update();
            g_game->render();
        }
        g_game->clean();
    }
    return 0;
}
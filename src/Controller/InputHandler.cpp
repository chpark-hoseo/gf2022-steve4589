#pragma once
#include <InputHandler.h>
#include <Game.h>
InputHandler* InputHandler::s_pInstance = 0;

void InputHandler::update()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
		switch (event.type)
		{
		case SDL_QUIT :
			Game::GetInstance()->quit();
			break;
		case SDL_KEYUP:
			Game::GetInstance()->quit();
			break;
		case SDL_KEYDOWN:
			Game::GetInstance()->quit();
			break;
		}
    }
}
bool InputHandler::isKeyDown(SDL_Scancode key)
{
    if (m_keystates != 0) {
        if (m_keystates[key] == 1) {
            return true;
        }
        else {
            return false;
        }
    }
    return false;
}
/*
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym)
			{
			case SDLK_LEFT:
				break;
			case SDLK_RIGHT:
				break;
			default:
				break;
			}
		}
		switch (event.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			m_bRunning = false;
			break;
		default:
			break;
		}
	}*/
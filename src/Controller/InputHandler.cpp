#pragma once
#include <InputHandler.h>
#include <Game.h>
InputHandler* InputHandler::s_pInstance = 0;

void InputHandler::update()
{
	SDL_Event event;
	//여러 키들을 감지해야 하므로, switch 사용 불가
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) Game::GetInstance()->quit();
		//KeyDown
		if (SDLK_LEFT) m_keystates[SDLK_LEFT];
		if (SDLK_UP) m_keystates[SDLK_UP];
		if (SDLK_DOWN) m_keystates[SDLK_DOWN];
		if (SDLK_RIGHT) m_keystates[SDLK_RIGHT];
		//KeyUp	
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
#pragma once
#include <SDLGameObject.h>
#include <Game.h>
#include <GameState.h>

Game* Game::s_pInstance = 0;

//----------------------------------------------------------------------------
//MainCode
bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		m_pWindow = SDL_CreateWindow(
			title, xpos, ypos, width, height, flags);
		//SDL_SetWindowFullscreen(m_pWindow, SDL_WINDOW_FULLSCREEN);
		if (m_pWindow != 0) {
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if (m_pRenderer != 0) {
				//Start_initialize();
				SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 0, 0);
			}
			else {
				return false; // 랜더러 생성 실패
			}
		}
		else {
			return false; // 윈도우 생성 실패 
		}
	}
	else {
		return false; // SDL 초기화 실패
	}
	m_bRunning = true;

	// SDL TTF
	if (TTF_Init() < 0)
	{
		SDL_Log("TTF_Init Error: %s\n", TTF_GetError());
		return false;
	}
	else
	{
		g_pFont = TTF_OpenFont("./assets/Font/NanumGothic.ttf", 100); //font, fontSize
		if (g_pFont == NULL)
		{
			SDL_Log("TTF_OpenFont Error: %s\n", TTF_GetError());
			return false;
		}
	}
	return true;
}
void Game::clean()
{
	// cleanup the all states
	while (!m_gameStates.empty()) {
		m_gameStates.back()->clean();
		m_gameStates.pop_back();
	}

	//자동으로 꺼지지 않기 때문에
	//풀스크린일때 비디오 모드로 돌리기

	// shutdown SDL
	SDL_Quit();
}

void Game::ChangeState(GameState* state)
{
	// cleanup the current state
	if (!m_gameStates.empty()) {
		m_gameStates.back()->clean();
		m_gameStates.pop_back();
	}
	// store and init the new state
	m_gameStates.push_back(state);
	m_gameStates.back()->Awake();
}

void Game::PushState(GameState* state)
{
	// store and init the new state
	m_gameStates.push_back(state);
	m_gameStates.back()->Awake();
}

void Game::PopState()
{
	// cleanup the current state
	if (!m_gameStates.empty()) {
		m_gameStates.back()->clean();
		m_gameStates.pop_back();
	}
}

void Game::handleEvents()
{
	m_gameStates.back()->handleEvents(this);
}

void Game::update()
{
	m_gameStates.back()->update(this);
}

void Game::render()
{
	m_gameStates.back()->render(this);
}
bool Game::running()
{
	return m_bRunning;
}
/*
void Game::DhrowBorder()
{
	SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
	//SDL_RenderClear(m_pRenderer);

	SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 }; //x, y, w, h
	SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255);
	SDL_RenderFillRect(m_pRenderer, &fillRect); //속이 꽉찬 사각형

	SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
	SDL_SetRenderDrawColor(m_pRenderer, 0, 255, 0, 255);
	SDL_RenderDrawRect(m_pRenderer, &outlineRect); //속이 빈 사각형

	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 255, 255);
	SDL_RenderDrawLine(m_pRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2); //선

	SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 0, 255);
	for (int i = 0; i < SCREEN_HEIGHT; i += 4)
	{
		SDL_RenderDrawPoint(m_pRenderer, SCREEN_WIDTH / 2, i); //점선
	}
}
*/
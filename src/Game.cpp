#pragma once
#include "Game.h"
#include "iostream"
#include "string.h"

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

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		m_pWindow = SDL_CreateWindow(
			title, xpos, ypos, width, height, flags);
		if (m_pWindow != 0) {
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if (m_pRenderer != 0) {
				//Textture 생성
				//Start_initialize();
				SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255);
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
	return true;
}
void Game::update()
{
	//m_curTime = SDL_GetTicks() / 6;
}

void Game::Prepare()
{
	TheTextureManager::GetInstance()->load("need for A+_stage1", "stage1_sprite", m_pRenderer);
	TheTextureManager::GetInstance()->load("need for A+_notes", "notes_sprite", m_pRenderer);
	TheTextureManager::GetInstance()->load("need for A+_selectMenu", "selectMenu_sprite", m_pRenderer);

	//스테이지 시작시 데이터 받아오기 
	/*
	queue<string> getstring = n_noteMgr->GetSpawnQueue();
	//test
	for (int i = 0; i < getstring.size(); i++)
	{
		string getthis = getstring.front();
		getstring.pop();
		cout << getthis << "\n\n";
	}*/
}

void Game::render()
{
	SDL_RenderClear(m_pRenderer);
	// Back(layer == 0)
    TheTextureManager::GetInstance()->draw("stage1_sprite", 0, 0, 1024, 720, m_pRenderer);
	//Sprites (layer == 1 ~ n)
	TheTextureManager::GetInstance()->drawFrame("notes_sprite", 0, 0, 96, 96, 0, 0, m_pRenderer);
	TheTextureManager::GetInstance()->draw("selectMenu_sprite", 535, 250, 0, 0, m_pRenderer);
	//selectMenu_sprite
	//TheTextureManager::GetInstance()->drawFrame("dog1_sprite", 450, 300, 240, 400, 0, 1, m_pRenderer);
	SDL_RenderPresent(m_pRenderer);
}
/*
void Game::MainMove(State state)
{
	int speed = state;
	speed = curFlip == SDL_FLIP_HORIZONTAL ? -speed : speed;

	if (SDL_GetTicks() % 8 == 0)
	{
		sprite1->m_destinationRectangle.x += speed;
		sprite2->m_destinationRectangle.x += speed;
	}
}
void Game::MainAnimation(State state)
{
	switch (state)
	{
	case idle:
		SDL_RenderCopyEx(m_pRenderer, sprite1->texture, &sprite1->m_sourceRectangle, &sprite1->m_destinationRectangle, NULL, NULL, curFlip);
		break;
	case walk:
		SDL_RenderCopyEx(m_pRenderer, sprite2->texture, &sprite2->m_sourceRectangle, &sprite2->m_destinationRectangle, NULL, NULL, curFlip);
		break;
	}
}*/
bool Game::running()
{
	return m_bRunning;
}
void Game::handleEvents()
{
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
	}
}
void Game::clean()
{
	SDL_DestroyWindow(m_pWindow);

	SDL_DestroyRenderer(m_pRenderer);

	SDL_Quit();
}
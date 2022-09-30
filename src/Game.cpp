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
				SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
				if (!TheTextureManager::GetInstance()->load("Assets/animate-alpha.png", "dog_animate", m_pRenderer)) //test
				{
					return false; //싱글턴 생성 실패 
				}
				//Load Texture
				TheTextureManager::GetInstance()->load("Assets/need for A+_stage1.png", "stage1_sprite", m_pRenderer);
				TheTextureManager::GetInstance()->load("Assets/textureManager_test.png", "dog1_sprite", m_pRenderer);
				TheTextureManager::GetInstance()->load("Assets/textureManager_test.png", "dogBack_sprite", m_pRenderer);
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
	m_currentFrame = ((SDL_GetTicks() / 100) % 6);
}

void Game::render()
{
	SDL_RenderClear(m_pRenderer);
	//Back (layer == 0)
	TheTextureManager::GetInstance()->draw("stage1_sprite", 0, 0, 1024, 720, m_pRenderer);
	//Sprites (layer == 1 ~ n)
	//m_textureManager.drawFrame("dog_animate", 100, 100, 128, 82, 0, m_currentFrame, m_pRenderer);
	TheTextureManager::GetInstance()->drawFrame("dogBack_sprite", 350, 120, 240, 400, 0, 0, m_pRenderer);
	TheTextureManager::GetInstance()->drawFrame("dog1_sprite", 450, 300, 240, 400, 0, 1, m_pRenderer);

	SDL_RenderPresent(m_pRenderer);
}
bool Game::running()
{
	return m_bRunning;
}
void Game::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
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

	//TextureManager::GetInstance()->TextureClean();
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}
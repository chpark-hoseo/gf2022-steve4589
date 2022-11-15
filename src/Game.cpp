#pragma once
#include "Game.h"
#include "iostream"
#include "string.h"
#include "GameObject.h"
#include <algorithm>

Game* Game::s_pInstance = 0;

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		m_pWindow = SDL_CreateWindow(
			title, xpos, ypos, width, height, flags);
		if (m_pWindow != 0) {
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if (m_pRenderer != 0) {
				SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
				if (!TheTextureManager::GetInstance()->load("animate-alpha", "dog_animate", m_pRenderer)) //test
				{
					return false; //싱글턴 생성 실패 
				}
				//Load Texture
				TheTextureManager::GetInstance()->load("need for A+_stage1", "stage1_sprite", m_pRenderer);
				TheTextureManager::GetInstance()->load("textureManager_test", "dog1_sprite", m_pRenderer);
				TheTextureManager::GetInstance()->load("textureManager_test", "dogBack_sprite", m_pRenderer);

				m_gameObjects.push_back(new Player(new LoaderParams(100, 100, 128, 82, "dog_animate")));
				m_gameObjects.push_back(new Enemy(new LoaderParams(100, 100, 128, 82, "dog_animate"))); //s
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
	//과제1. for_each 사용해보기 
	for_each(m_gameObjects.begin(), m_gameObjects.end(), [](GameObject*& gameObject) {gameObject->update(); }); //3번째 인자에 람다식을 썼습니다
}

void Game::render()
{
	SDL_RenderClear(m_pRenderer);

	for (int i = 0; i != m_gameObjects.size(); i++) {
		m_gameObjects[i]->draw();
	}

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
	TextureManager::GetInstance()->TextureAllClean(); //텍스쳐 모두 삭제

	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}
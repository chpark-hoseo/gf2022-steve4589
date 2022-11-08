#pragma once
#include "Game.h"
#include "iostream"
#include "string.h"
#include "GameObject.h"
#include <algorithm>

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
					return false; //�̱��� ���� ���� 
				}
				//Load Texture
				TheTextureManager::GetInstance()->load("need for A+_stage1", "stage1_sprite", m_pRenderer);
				TheTextureManager::GetInstance()->load("textureManager_test", "dog1_sprite", m_pRenderer);
				TheTextureManager::GetInstance()->load("textureManager_test", "dogBack_sprite", m_pRenderer);

				m_go->load(100, 100, 128, 82, "dog_animate");
				m_player->load(300, 300, 128, 82, "dog_animate");
				m_Monster_diagonal->load(0, 0, 128, 82, "dog_animate");
				m_Monster_swim->load(0, 300, 128, 82, "dog_animate");
				m_Monster_wave->load(300, 300, 128, 82, "dog_animate");

				m_Monster_swim->GoSwim();
				m_Monster_wave->GoWave();

				m_gameObjects.push_back(m_go);
				m_gameObjects.push_back(m_player);

				m_gameObjects.push_back(m_Monster_diagonal);
				m_gameObjects.push_back(m_Monster_swim);
				m_gameObjects.push_back(m_Monster_wave);
			}
			else {
				return false; // ������ ���� ����
			}
		}
		else {
			return false; // ������ ���� ���� 
		}
	}
	else {
		return false; // SDL �ʱ�ȭ ����
	}
	m_bRunning = true;
	return true;
}
void Game::update()
{
	//����1. for_each ����غ��� 
	for_each(m_gameObjects.begin(), m_gameObjects.end(), [](GameObject*& gameObject) {gameObject->update(); }); //3��° ���ڿ� ���ٽ��� ����ϴ�
}

void Game::render()
{
	SDL_RenderClear(m_pRenderer);

	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw(m_pRenderer);
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
	TextureManager::GetInstance()->TextureAllClean(); //�ؽ��� ��� ����

	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}
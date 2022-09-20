#pragma once
#include "Game.h"
#include "iostream"

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		m_pWindow = SDL_CreateWindow(
			title, xpos, ypos, width, height, flags);
		if (m_pWindow != 0) {
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

			if (m_pRenderer != 0) {
				//Textture ����
				SDL_Surface* pTempSurface = SDL_LoadBMP("Assets/rider.bmp");

				m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);

				SDL_FreeSurface(pTempSurface);
				//���� ���� �ʺ�/���� ����
				SDL_QueryTexture(m_pTexture, NULL, NULL, &m_sourceRectangle.w, &m_sourceRectangle.h);
				//SDL_QueryTexture(SDL_Texture textur, Uint32* format, int* access, int* x, int* y)
				//format -> �ش� format���� ĥ�Ұ��� / access -> ��� �ؽ��ĸ� �ƿ� ĥ�Ұ���?

				m_destinationRectangle.w = m_sourceRectangle.w;
				std::cout << m_sourceRectangle.w << "    " << m_destinationRectangle.w << "\n";
				m_destinationRectangle.h = m_sourceRectangle.h;
				std::cout << m_sourceRectangle.h << "    " << m_destinationRectangle.h << "\n";

				m_destinationRectangle.x = m_sourceRectangle.x = 0;
				m_destinationRectangle.y = m_sourceRectangle.y = 0;
				std::cout << m_sourceRectangle.x << "    " << m_destinationRectangle.y;

				SDL_SetRenderDrawColor(
					m_pRenderer, 255, 255, 255, 255);
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
void Game::update() {}
void Game::render()
{
	SDL_RenderClear(m_pRenderer);
	SDL_RenderCopy(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle);
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
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}
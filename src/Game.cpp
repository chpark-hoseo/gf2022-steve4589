#pragma once
#include "Game.h"
#include "iostream"
#include "string.h"

Sprite* Game::GetSprite(const char* file) //Sprite의 texture를 반환하도록 변경
{
	Sprite* getSprite = new Sprite();

	if (strstr(file, ".bmp") != NULL) {
		getSprite->surface = SDL_LoadBMP(file);
		printf("asdfsd");
	} //Assets/rider.bmp 
	else {
		getSprite->surface = IMG_Load(file);
		printf("와우");
	} //Assets/asdf21.png 

	getSprite->texture = SDL_CreateTextureFromSurface(m_pRenderer, getSprite->surface);
	SDL_FreeSurface(getSprite->surface);

	SDL_QueryTexture(getSprite->texture, NULL, NULL, &m_sourceRectangle.w, &m_sourceRectangle.h);
	//SDL_QueryTexture(SDL_Texture textur, Uint32* format, int* access, int* x, int* y)

	getSprite->m_sourceRectangle.w = m_sourceRectangle.w;
	getSprite->m_sourceRectangle.h = m_sourceRectangle.h;

	getSprite->m_sourceRectangle.x = m_sourceRectangle.x;
	getSprite->m_sourceRectangle.y = m_sourceRectangle.y;

	getSprite->m_destinationRectangle.w = m_sourceRectangle.w;
	getSprite->m_destinationRectangle.h = m_sourceRectangle.h;

	getSprite->m_destinationRectangle.x = m_sourceRectangle.x;
	getSprite->m_destinationRectangle.y = m_sourceRectangle.y;

	return getSprite;
}

void Game::MoveSprite()
{
	//sprite1->m_destinationRectangle.x = sprite1->m_destinationRectangle.x == 0 ? width : 0;
	//SDL_QueryTexture(sprite1->texture, NULL, NULL, &sprite1->m_sourceRectangle.w, &sprite1->m_sourceRectangle.h);

	if ((sprite1->m_destinationRectangle.x > SCREEN_WIDTH - 123) || sprite1->m_destinationRectangle.x < 0) { xInterval = -xInterval;}
	sprite1->m_destinationRectangle.x += xInterval;
	SDL_QueryTexture(sprite1->texture, NULL, NULL, &sprite1->m_sourceRectangle.w, &sprite1->m_sourceRectangle.h);
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
				sprite = GetSprite("Assets/asdf21.png");
				sprite1 = GetSprite("Assets/rider.bmp");

				SDL_SetRenderDrawColor(
					m_pRenderer, 255, 255, 255, 255);
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
	MoveSprite();
}
void Game::render()
{
	SDL_RenderClear(m_pRenderer);

	DhrowBorder();
	SDL_RenderCopy(m_pRenderer, sprite->texture, &sprite->m_sourceRectangle, &sprite->m_destinationRectangle);
	SDL_RenderCopy(m_pRenderer, sprite1->texture, &sprite1->m_sourceRectangle, &sprite1->m_destinationRectangle);
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
	SDL_DestroyTexture(sprite->texture);
	SDL_DestroyTexture(sprite->texture);

	SDL_Quit();
}
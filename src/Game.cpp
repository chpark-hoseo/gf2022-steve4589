#pragma once
#include "Game.h"
#include "iostream"
#include "string.h"

Sprite* Game::GetSprite(const char* file, int x, int y, int w, int h) //Sprite의 texture를 반환하도록 변경
{
	Sprite* getSprite = new Sprite();

	if (strstr(file, ".bmp") != NULL) {
		getSprite->surface = SDL_LoadBMP(file);
	} //Assets/rider.bmp 
	else {
		getSprite->surface = IMG_Load(file);
	} //Assets/asdf21.png 

	SDL_Surface* convert_surface = SDL_ConvertSurfaceFormat(getSprite->surface, SDL_PIXELFORMAT_ARGB8888, 0);
	getSprite->texture = SDL_CreateTextureFromSurface(m_pRenderer, convert_surface);
	SDL_FreeSurface(getSprite->surface);

	SDL_QueryTexture(getSprite->texture, NULL, NULL, &m_sourceRectangle.w, &m_sourceRectangle.h); //SDL_QueryTexture(SDL_Texture textur, Uint32* format, int* access, int* x, int* y)

	if(w != NULL)
	{
		getSprite->m_sourceRectangle.w = w;
		getSprite->m_sourceRectangle.h = h;
	}
	else
	{
		getSprite->m_sourceRectangle.w = m_sourceRectangle.w;
		getSprite->m_sourceRectangle.h = m_sourceRectangle.h;
	}
	getSprite->m_destinationRectangle.w = getSprite->m_sourceRectangle.w;
	getSprite->m_destinationRectangle.h = getSprite->m_sourceRectangle.h;

	if (x != NULL)
	{
		getSprite->m_sourceRectangle.x = x;
		getSprite->m_sourceRectangle.y = y;
	}
	else
	{
		getSprite->m_sourceRectangle.x = m_sourceRectangle.x;
		getSprite->m_sourceRectangle.y = m_sourceRectangle.y;
	}
	getSprite->m_destinationRectangle.x = m_sourceRectangle.x;
	getSprite->m_destinationRectangle.y = m_sourceRectangle.y;

	return getSprite;
}

void Game::MoveSprite()
{
	if ((sprite4->m_destinationRectangle.x > SCREEN_WIDTH - sprite4->m_destinationRectangle.w) || sprite4->m_destinationRectangle.x < 0) { xInterval = -xInterval; }
	curFlip = xInterval == 1 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
	sprite4->m_destinationRectangle.x += xInterval;
}

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
				sprite = GetSprite("Assets/animate.bmp", NULL, NULL, 128, 78);

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
	int calTick = tick;
	tick = 128 * ((SDL_GetTicks() / 100) % 6);
	sprite->m_sourceRectangle.x = tick;
	if (tick != calTick)
	{
		std::cout << sprite->m_sourceRectangle.x << "\n";
		std::cout << sprite->m_sourceRectangle.y << "\n";
		std::cout << sprite->m_sourceRectangle.w << "\n";
		std::cout << sprite->m_sourceRectangle.h << "\n";
		std::cout << "\n\n\n\n\n";
		std::cout << sprite->m_destinationRectangle.x << "\n";
		std::cout << sprite->m_destinationRectangle.y << "\n";
		std::cout << sprite->m_destinationRectangle.w << "\n";
		std::cout << sprite->m_destinationRectangle.h << "\n";
		std::cout << "\n\n\n";
	}
}
void Game::render() //스프라이트, 배경, 애니메이션 등등 따로 나눠서 관리 해보기
{
	SDL_RenderClear(m_pRenderer);
	//DhrowBorder();
	SDL_RenderCopy(m_pRenderer, sprite->texture, &sprite->m_sourceRectangle, &sprite->m_destinationRectangle);

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
	//스프라이트 텍스쳐 해제를 따로담당하는 함수 필요
	SDL_DestroyTexture(sprite->texture);
	SDL_DestroyTexture(sprite1->texture);
	SDL_DestroyTexture(sprite2->texture);
	SDL_DestroyTexture(sprite3->texture);
	SDL_DestroyTexture(sprite4->texture);

	SDL_Quit();
}
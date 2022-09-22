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

	getSprite->texture = SDL_CreateTextureFromSurface(m_pRenderer, getSprite->surface); //텍스쳐 해제 필수
	SDL_FreeSurface(getSprite->surface);

	SDL_QueryTexture(getSprite->texture, NULL, NULL, &m_sourceRectangle.w, &m_destinationRectangle.h); //SDL_QueryTexture(SDL_Texture textur, Uint32* format, int* access, int* x, int* y)

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
	if ((sprite1->m_destinationRectangle.x > SCREEN_WIDTH - sprite1->m_destinationRectangle.w) || sprite1->m_destinationRectangle.x < 0) { xInterval = -xInterval; }
	sprite1->m_destinationRectangle.x += xInterval;

	SDL_QueryTexture(sprite1->texture, NULL, NULL, &sprite1->m_sourceRectangle.w, &sprite1->m_sourceRectangle.h);
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
				sprite = GetSprite("Assets/rider.bmp");
				sprite1 = GetSprite("Assets/rider.bmp");
				sprite2 = GetSprite("Assets/rider.bmp");
				sprite3 = GetSprite("Assets/rider.bmp");
				sprite4 = GetSprite("Assets/rider.bmp");

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
	//MoveSprite();
}
void Game::render() //스프라이트, 배경, 애니메이션 등등 따로 나눠서 관리 해보기
{
	SDL_RenderClear(m_pRenderer);

	//DhrowBorder();
	// 추가 실습 :: 현재 위치에서 일부분만 보이게
	sprite->m_destinationRectangle.x = 10;
	sprite->m_destinationRectangle.y = -20;
	//SDL_RenderCopy(m_pRenderer, sprite->texture, &sprite->m_sourceRectangle, &sprite->m_destinationRectangle);
	//과제 1 :: 
	sprite1->m_destinationRectangle.x = 300;
	sprite1->m_destinationRectangle.y = -230;
	SDL_QueryTexture(sprite1->texture, NULL, NULL, &m_sourceRectangle.w, &m_destinationRectangle.h);
	sprite1->m_destinationRectangle.x = 30;
	sprite1->m_destinationRectangle.y = -50;
	SDL_RenderCopy(m_pRenderer, sprite1->texture, &sprite->m_sourceRectangle, &sprite->m_destinationRectangle);
	//과제 2 ::
	sprite2->m_destinationRectangle.x = 70;
	sprite2->m_destinationRectangle.y = -50;
	//SDL_RenderCopy(m_pRenderer, sprite2->texture, &sprite2->m_sourceRectangle, &sprite2->m_destinationRectangle);
	//과제 3 ::
	//SDL_RenderCopy(m_pRenderer, sprite3->texture, &sprite->m_sourceRectangle, &sprite->m_destinationRectangle);
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
	SDL_DestroyTexture(sprite1->texture);
	SDL_DestroyTexture(sprite2->texture);
	SDL_DestroyTexture(sprite3->texture);
	SDL_DestroyTexture(sprite4->texture);

	SDL_Quit();
}
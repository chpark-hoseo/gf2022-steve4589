#pragma once
#include "Game.h"
#include "iostream"
#include "string.h"

Sprite* Game::GetSprite(const char* file) //Sprite�� texture�� ��ȯ�ϵ��� ����
{
	Sprite* getSprite = new Sprite();

	if (strstr(file, ".bmp") != NULL) {
		getSprite->surface = SDL_LoadBMP(file);
		printf("asdfsd");
	} //Assets/rider.bmp 
	else {
		getSprite->surface = IMG_Load(file);
		printf("�Ϳ�");
	} //Assets/asdf21.png 

	getSprite->texture = SDL_CreateTextureFromSurface(m_pRenderer, getSprite->surface); //�ؽ��� ���� �ʼ�
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

void Game::MoveSprite(int width)
{
	//sprite1->m_destinationRectangle.x = sprite1->m_destinationRectangle.x == 0 ? width : 0;
	//SDL_QueryTexture(sprite1->texture, NULL, NULL, &sprite1->m_sourceRectangle.w, &sprite1->m_sourceRectangle.h);

	if ((sprite1->m_destinationRectangle.x > SCREEN_WIDTH - sprite1->m_destinationRectangle.w) || sprite1->m_destinationRectangle.x < 0) { xInterval = -xInterval;}
	sprite1->m_destinationRectangle.x += xInterval;
	sprite1->m_destinationRectangle.x = sprite1->m_destinationRectangle.x == 0 ? SCREEN_WIDTH : 0;
	SDL_QueryTexture(sprite1->texture, NULL, NULL, &sprite1->m_sourceRectangle.w, &sprite1->m_sourceRectangle.h);
	/*
	int xInterval = 1;
	sprite->m_destinationRectangle.x += xInterval;
	if ((sprite->m_destinationRectangle.x < 0 && xInterval < 0) || sprite->m_destinationRectangle.x > width - 15 && xInterval > 0) {
		xInterval = -xInterval;
		SDL_Delay(30);
	}*/
}

void Game::DhrowBorder()
{
	SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
	//SDL_RenderClear(m_pRenderer);

	SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 }; //x, y, w, h
	SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255);
	SDL_RenderFillRect(m_pRenderer, &fillRect); //���� ���� �簢��

	SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
	SDL_SetRenderDrawColor(m_pRenderer, 0, 255, 0, 255);
	SDL_RenderDrawRect(m_pRenderer, &outlineRect); //���� �� �簢��

	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 255, 255);
	SDL_RenderDrawLine(m_pRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2); //��

	SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 0, 255);
	for (int i = 0; i < SCREEN_HEIGHT; i += 4)
	{
		SDL_RenderDrawPoint(m_pRenderer, SCREEN_WIDTH / 2, i); //���� 
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
				//Textture ����
				sprite = GetSprite("Assets/asdf21.png");
				sprite1 = GetSprite("Assets/rider.bmp");

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
void Game::update()
{
	MoveSprite(640);
}
void Game::render()
{
	SDL_RenderClear(m_pRenderer);

	//DhrowBorder();
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
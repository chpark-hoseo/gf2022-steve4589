#pragma once
#include "Game.h"
#include "iostream"
#include "string.h"

Sprite* Game::GetSprite(const char* file, int x, int y, int w, int h) //Sprite�� texture�� ��ȯ�ϵ��� ����
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

	if (w != NULL)
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
				sprite = GetSprite("Assets/5_test.png", NULL, NULL, 64, 64);
				sprite1 = GetSprite("Assets/5_test.png", NULL, NULL, 64, 64);
				sprite2 = GetSprite("Assets/5_test.png", NULL, NULL, 64, 64);
				sprite3 = GetSprite("Assets/test_didle.png", NULL, NULL, 64, 64);

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
	sprite->m_sourceRectangle.x = 64 * ((SDL_GetTicks() / 100) % 6); //�ܰŸ� ����
	sprite1->m_sourceRectangle.x = 64 * ((SDL_GetTicks() / 150) % 6); //���� �꺸�ϴ� ����
	sprite1->m_destinationRectangle.y = 64;

	sprite2->m_sourceRectangle.x = 64 * ((SDL_GetTicks() / 150) % 6); //walk
	sprite2->m_destinationRectangle.y = 128;
	sprite3->m_sourceRectangle.x = 64 * ((SDL_GetTicks() / 150) % 4); //idle
	sprite3->m_destinationRectangle.y = 128;

	MainMove(curState);
}

void Game::render()
{
	SDL_RenderClear(m_pRenderer);
	//����1, ������ ������ �ִϸ��̼� �ӵ� �ٸ��� �ϱ� 
	SDL_RenderCopy(m_pRenderer, sprite->texture, &sprite->m_sourceRectangle, &sprite->m_destinationRectangle);
	SDL_RenderCopy(m_pRenderer, sprite1->texture, &sprite1->m_sourceRectangle, &sprite1->m_destinationRectangle);
	//����2, github Ŀ�� �ۼ����� ���� ����̺� ��ũ�� ���ø� �˴ϴ�! 
	//����3. �ڱ⸸�� ������� ���� Ǯ��� :: �¿�Ű�� ������ ĳ������ ���⿡ ���� �ִϸ��̼��� �ٲ��, Ű�� ���� ĳ���Ͱ� ����ϴ�.
	MainAnimation(curState);
	SDL_RenderPresent(m_pRenderer);
}
void Game::MainMove(State state)
{
	int speed = state;
	speed = curFlip == SDL_FLIP_HORIZONTAL ? -speed : speed;

	if (SDL_GetTicks() % 8 == 0)
	{
		sprite2->m_destinationRectangle.x += speed;
		sprite3->m_destinationRectangle.x += speed;
	}
}
void Game::MainAnimation(State state)
{
	switch (state)
	{
	case idle:
		SDL_RenderCopyEx(m_pRenderer, sprite3->texture, &sprite3->m_sourceRectangle, &sprite3->m_destinationRectangle, NULL, NULL, curFlip);
		break;
	case walk:
		SDL_RenderCopyEx(m_pRenderer, sprite2->texture, &sprite2->m_sourceRectangle, &sprite2->m_destinationRectangle, NULL, NULL, curFlip);
		break;
	}
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
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym)
			{
			case SDLK_LEFT:
				curState = walk;
				curFlip = SDL_FLIP_HORIZONTAL;
				break;
			case SDLK_RIGHT:
				curState = walk;
				curFlip = SDL_FLIP_NONE;
				break;
			default:
				break;
			}
		}
		else if (event.type == SDL_KEYUP) { curState = idle; }

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
	//��������Ʈ �ؽ��� ������ ���δ���ϴ� �Լ� �ʿ�
	SDL_DestroyTexture(sprite->texture);
	SDL_DestroyTexture(sprite1->texture);
	SDL_DestroyTexture(sprite2->texture);
	SDL_DestroyTexture(sprite3->texture);
	SDL_DestroyTexture(sprite4->texture);

	SDL_Quit();
}
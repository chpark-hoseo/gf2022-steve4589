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

	getSprite->texture = SDL_CreateTextureFromSurface(m_pRenderer, getSprite->surface); //�ؽ��� ���� �ʼ�
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
				sprite = GetSprite("Assets/rider.bmp", NULL, NULL, 40, 40);
				sprite1 = GetSprite("Assets/rider.bmp", NULL, NULL, 40, 40);
				sprite2 = GetSprite("Assets/rider.bmp", 50, 50, 40, 40);
				sprite3 = GetSprite("Assets/rider.bmp", NULL, NULL, SCREEN_WIDTH, SCREEN_HEIGHT);
				sprite4 = GetSprite("Assets/rider.bmp", NULL, NULL, NULL, NULL);

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
	MoveSprite();
}
void Game::render() //��������Ʈ, ���, �ִϸ��̼� ��� ���� ������ ���� �غ���
{
	SDL_RenderClear(m_pRenderer);

	//DhrowBorder();
	// //���� 3 (��ü ȭ��)::
	SDL_RenderCopy(m_pRenderer, sprite3->texture, &sprite3->m_sourceRectangle, &sprite3->m_destinationRectangle);

	// �߰� �ǽ� :: ���� ��ġ���� �Ϻκи� ���̰�
	SDL_RenderCopy(m_pRenderer, sprite->texture, &sprite->m_sourceRectangle, &sprite->m_destinationRectangle);

	//���� 1 :: 
	sprite1->m_destinationRectangle.x = 100;
	sprite1->m_destinationRectangle.y = 100;
	SDL_RenderCopy(m_pRenderer, sprite1->texture, &sprite1->m_sourceRectangle, &sprite1->m_destinationRectangle);

	//���� 2 ::
	sprite2->m_destinationRectangle.x = 60;
	sprite2->m_destinationRectangle.y = 120;
	SDL_RenderCopy(m_pRenderer, sprite2->texture, &sprite2->m_sourceRectangle, &sprite2->m_destinationRectangle);
	//���� 4 :: 
	//SDL_RenderCopyEx :: flip / angle��� ���� (�ٶ󺸴� �������� ���� �ٲٱ�)
	sprite4->m_destinationRectangle.h = 100;
	sprite4->m_destinationRectangle.w = 100;
	SDL_RenderCopyEx(m_pRenderer, sprite4->texture, &sprite4->m_sourceRectangle, &sprite4->m_destinationRectangle, NULL, NULL, curFlip);
	//�ش� �ڵ�� ��ü���� (angle ���)
	/* MoveSprite() ���� ->
	   if ((sprite4->m_destinationRectangle.x > SCREEN_WIDTH - sprite4->m_destinationRectangle.w) || sprite4->m_destinationRectangle.x < 0) 
	   {
	     xInterval = -xInterval; 
	     angle = -angle;
	   }*
	   SDL_RenderCopyEx(m_pRenderer, sprite4->texture, &sprite4->m_sourceRectangle, &sprite4->m_destinationRectangle, angle, NULL, SDL_FLIP_NONE);*/

	//����Ƽ���� ����� ó�� atan�� ���, ������ ������ �����, �ǽð����� ���ֺ��� �ϱ� ���� 
	//4��° ���ڴ� ȸ���� �߽����� ����, NULL�̸� ���� �̹����� �߽����� �������� ȸ�� 
	// �̸� Ȱ���� ö���� ���⳪ ����ŷ���� ���� �� ������ �����ϴ� 

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
	//��������Ʈ �ؽ��� ������ ���δ���ϴ� �Լ� �ʿ�
	SDL_DestroyTexture(sprite->texture);
	SDL_DestroyTexture(sprite1->texture);
	SDL_DestroyTexture(sprite2->texture);
	SDL_DestroyTexture(sprite3->texture);
	SDL_DestroyTexture(sprite4->texture);

	SDL_Quit();
}
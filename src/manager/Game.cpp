#pragma once
#include <Game.h>
#include <SDLGameObject.h>
#include <ObjManager.h>

Game* Game::s_pInstance = 0;

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
				//Start_initialize();
				SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255);
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
	//�÷��� ��ư Ŭ��
	NoteManager::GetInstance()->ReadSpawnNotes(); //�߰� �ʿ�--> 1�������� ��ư => 1�������� ��Ʈ, 2�������� ��ư => 2�������� ��Ʈ 

	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->update();
	}
}

void Game::Prepare()
{
	//������ �� ����
	TextureManager::GetInstance()->load("need for A+_stage1", "stage1_sprite", m_pRenderer);
	TextureManager::GetInstance()->load("need for A+_notes", "notes_sprite", m_pRenderer);
	TextureManager::GetInstance()->load("need for A+_selectMenu", "selectMenu_sprite", m_pRenderer);
	//initial GameObject (��� ���..)
	m_gameObjects = ObjManager::GetInstance()->InitPool(); //���߿� Vector ���빰�� �������ֱ� ������� ���� ObjectPool�� ���빰�� �ʱ�ȭ ���׽��ϴ� 
	std::cout << "ObjectPool => " << m_gameObjects.size() << "�� ����\n\n";

	//GameObject* object = new Note(new LoaderParams(0, 0, 96, 96, 0, 0, "notes_sprite"));
	//m_gameObjects.push_back(new GameObject(new LoaderParams(0, 0, 96, 96, 0, 0, "notes_sprite")));

	//Note
	NoteManager::GetInstance()->ReadLineToTxt("stage1");
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
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym)
			{
			case SDLK_LEFT:
				break;
			case SDLK_RIGHT:
				break;
			default:
				break;
			}
		}
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
	TheTextureManager::GetInstance()->TextureAllClean();
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}
/*
void Game::MainMove(State state)
{
	int speed = state;
	speed = curFlip == SDL_FLIP_HORIZONTAL ? -speed : speed;

	if (SDL_GetTicks() % 8 == 0)
	{
		sprite1->m_destinationRectangle.x += speed;
		sprite2->m_destinationRectangle.x += speed;
	}
}
void Game::MainAnimation(State state)
{
	switch (state)
	{
	case idle:
		SDL_RenderCopyEx(m_pRenderer, sprite1->texture, &sprite1->m_sourceRectangle, &sprite1->m_destinationRectangle, NULL, NULL, curFlip);
		break;
	case walk:
		SDL_RenderCopyEx(m_pRenderer, sprite2->texture, &sprite2->m_sourceRectangle, &sprite2->m_destinationRectangle, NULL, NULL, curFlip);
		break;
	}
}*/
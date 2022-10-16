#pragma once
#include <Game.h>
#include <SDLGameObject.h>

Game* Game::s_pInstance = 0;

//----------------------------------------------------------------------------
//MainCode
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
	//플레이 버튼 클릭
	NoteManager::GetInstance()->ReadSpawnNotes(); //추가 필요--> 1스테이지 버튼 => 1스테이지 시트, 2스테이지 버튼 => 2스테이지 시트 

	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->update();
	}
}

void Game::Prepare()
{
	//가져다 쓸 사진 need for A+_notesPad
	TextureManager::GetInstance()->load("need for A+_stage1", "stage1_sprite", m_pRenderer);

	TextureManager::GetInstance()->load("need for A+_notes", "notes_sprite", m_pRenderer);
	TextureManager::GetInstance()->load("need for A+_notesPad", "notesPad_sprite", m_pRenderer);

	TextureManager::GetInstance()->load("need for A+_selectMenu", "selectMenu_sprite", m_pRenderer);
	//initial GameObject (배경 등등..)
	GameObject* back1 = new SDLGameObject(new LoaderParams(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, "stage1_sprite"));
	GameObject* test = new Note(new LoaderParams(0, 0, 96, 96, 0, 0, "notes_sprite"));
	test->SetActive(true);
	m_gameObjects.push_back(back1);
	m_gameObjects.push_back(test);
	InitPool();
	std::cout << "ObjectSize => " << m_gameObjects.size() << "\n\n";

	//Note
	NoteManager::GetInstance()->ReadLineToTxt("stage1");
}

void Game::render()
{
	SDL_RenderClear(m_pRenderer);

	for (int i = 0; i < m_gameObjects.size(); i++) {
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
	TheInputHandler::Instance()->update();
}
void Game::clean()
{
	TheTextureManager::GetInstance()->TextureAllClean();
	TheInputHandler::Instance()->clean();
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}
//----------------------------------------------------------------------------
//ObjectPool
void Game::InitPool()
{
	Pool* pools[4] = { new Pool("LeftNote", 15), new Pool("UpNote", 15), new Pool("DownNote", 15), new Pool("RightNote", 15) };
	for (Pool* pool : pools) //이중 값을 가져오기 위해 포인터 형식사용
	{
		for (int i = 0; i < pool->m_size; i++)
		{
			CreateObjects(pool->m_name);
		}
	}
}
GameObject* Game::CreateObjects(const char* name)
{
	GameObject* gameObject = NULL;
	if (name == "LeftNote") {
		gameObject = new Note(new LoaderParams(0, 0, 96, 96, 0, 0, "notes_sprite"));
	}
	else if (name == "UpNote") {
		gameObject = new Note(new LoaderParams(0, 0, 96, 96, 0, 1, "notes_sprite"));
	}
	else if (name == "DownNote") {
		gameObject = new Note(new LoaderParams(0, 0, 96, 96, 0, 2, "notes_sprite"));
	}
	else if (name == "RightNote") {
		gameObject = new Note(new LoaderParams(0, 0, 96, 96, 0, 3, "notes_sprite"));
	}
	gameObject->SetName(name);
	gameObject->SetActive(false);

	std::cout << "Ptr" << gameObject << "\n";

	m_gameObjects.emplace_back(gameObject);
	objects[name].emplace_back(gameObject); 

	return gameObject;
}
GameObject* Game::GetObject(Vector2D spawnPos, const char* name)
{
	GameObject* gameObject = objects[name].back();
	gameObject->SetActive(true);
	gameObject->SetPosition(spawnPos);
		
	std::cout << name << " Real Ptr : " << gameObject << "\n";

	objects[name].pop_back();
	return gameObject;
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
*/
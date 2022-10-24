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
	TextureManager::GetInstance()->load("need for A+_noteBoom", "notesBoom_sprite", m_pRenderer); 
	TextureManager::GetInstance()->load("need for A+_noteBoom1", "notesBoom1_sprite", m_pRenderer);

	TextureManager::GetInstance()->load("need for A+_selectMenu", "selectMenu_sprite", m_pRenderer);
	//initial GameObject (배경 등등..)
	m_gameObjects.push_back(back1); 

	m_gameObjects.push_back(notePad);
	m_gameObjects.push_back(notePad1);
	m_gameObjects.push_back(notePad2);
	m_gameObjects.push_back(notePad3);
	//ObjectPool
	InitPool();
	std::cout << "ObjectSize => " << m_gameObjects.size() << "\n\n";
	//Note
	NoteManager::GetInstance()->ReadLineToTxt("stage1");
	//Position
	notePad->SetPosition(Vector2D(1024 * 0.5f - 200, 450));
	notePad1->SetPosition(Vector2D(1024 * 0.5f - 100, 450));
	notePad2->SetPosition(Vector2D(1024 * 0.5f, 450));
	notePad3->SetPosition(Vector2D(1024 * 0.5f + 100, 450));
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
	handleInput();
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
	Pool* pools[7] = { new Pool("LeftNote", 10), new Pool("UpNote", 10), new Pool("DownNote" ,10), new Pool("RightNote", 10) , new Pool("PowerNote", 15), new Pool("WinBoom", 13), new Pool("MissBoom", 13) };
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
		gameObject = new Note(new LoaderParams(0, 0, 96, 96, 0, 0, "notes_sprite"), name);
	}
	else if (name == "UpNote") {
		gameObject = new Note(new LoaderParams(0, 0, 96, 96, 0, 1, "notes_sprite"), name);
	}
	else if (name == "DownNote") {
		gameObject = new Note(new LoaderParams(0, 0, 96, 96, 0, 2, "notes_sprite"), name);
	}
	else if (name == "RightNote") {
		gameObject = new Note(new LoaderParams(0, 0, 96, 96, 0, 3, "notes_sprite"), name);
	}
	else if (name == "PowerNote") {
		gameObject = new PowerNote(new LoaderParams(0, 0, 96, 96, 0, 0, "notes_sprite"));
	}
	else if (name == "WinBoom") {
		gameObject = new NoteBoom(new LoaderParams(0, 0, 128, 128, 0, 0, "notesBoom_sprite"));
	}
	else if (name == "MissBoom") {
		gameObject = new NoteBoom(new LoaderParams(0, 0, 128, 128, 0, 0, "notesBoom1_sprite"));
	}
	gameObject->SetName(name);
	gameObject->SetActive(false); 
	//All Objects
	m_gameObjects.emplace_back(gameObject);
	//ObjectPool, collision Object
	objects[name].emplace_back(gameObject);
	if (gameObject->getTag() == "Note") collisionObjects.emplace_back(gameObject); 

	return gameObject;
}
GameObject* Game::GetObject(Vector2D spawnPos, const char* name)
{
	GameObject* gameObject = objects[name].back();
	gameObject->SetActive(true);
	gameObject->SetPosition(spawnPos);
		
	std::cout << "name ==> " << gameObject->GetName() << "\n\n";
	objects[name].pop_back(); 
	return gameObject;
}
//----------------------------------------------------------------------
//PlayInput
void Game::handleInput()
{
	//Command Pattern - 메인화면, 플레이 
	//SetCommand(NoteInput)
	Input_Note();
}
void Game::Input_Note()
{
	//KeyDown
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)) {
		notePad->IsPressed(true);
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)) {
		notePad1->IsPressed(true);
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN)) {
		notePad2->IsPressed(true);
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)) {
		notePad3->IsPressed(true);
	}
	//KeyUp
	if (!TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)) {
		notePad->PressOut(false);
	}
	if (!TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)) {
		notePad1->PressOut(false);
	}
	if (!TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN)) {
		notePad2->PressOut(false);
	}
	if (!TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)) {
		notePad3->PressOut(false);
	}
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
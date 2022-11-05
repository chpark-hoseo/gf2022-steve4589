#pragma once
#include <SDLGameObject.h>
#include <Game.h>

Game* Game::s_pInstance = 0;

//----------------------------------------------------------------------------
//MainCode
bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		m_pWindow = SDL_CreateWindow(
			title, xpos, ypos, width, height, flags);
		//SDL_SetWindowFullscreen(m_pWindow, SDL_WINDOW_FULLSCREEN);
		if (m_pWindow != 0) {
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if (m_pRenderer != 0) {
				//Start_initialize();
				SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 0, 0);
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
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->update();
	}

	//GameOver;
	if (hp <= 0 && !isGameOver) { GameOver(); }
	//State N
	if (isGameOver == false)
	{
		NoteManager::GetInstance()->ReadSpawnNotes(); //�߰� �ʿ�--> 1�������� ��ư => 1�������� ��Ʈ, 2�������� ��ư => 2�������� ��Ʈ 
	}
}

void Game::Awake()
{
	//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	//�������� ���
	TextureManager::GetInstance()->load("need for A+_stage1", "stage1_sprite", m_pRenderer);
	TextureManager::GetInstance()->load("need for A+_stage1_back_frame", "stage1_back_frame_sprite", m_pRenderer);
	TextureManager::GetInstance()->load("need for A+_stage1_back", "stage1_back_sprite", m_pRenderer);
	//TextureManager::GetInstance()->load("need for A+_stage2", "stage2_sprite", m_pRenderer);
	//TextureManager::GetInstance()->load("need for A+_stage2_back", "stage2back_sprite", m_pRenderer);

	//����ĳ���� 
	TextureManager::GetInstance()->load("need for A+_main", "mainCharacter_sprite", m_pRenderer); //need for A+_main_dead

	//��Ʈ
	TextureManager::GetInstance()->load("need for A+_notes", "notes_sprite", m_pRenderer);
	TextureManager::GetInstance()->load("need for A+_PowerNote", "powerNotes_sprite", m_pRenderer);

	//��Ʈ �е�
	TextureManager::GetInstance()->load("need for A+_notesPad", "notesPad_sprite", m_pRenderer);
	TextureManager::GetInstance()->load("need for A+_PowernotePad", "powerNotesPad_sprite", m_pRenderer);

	//���� �ִϸ��̼�  
	TextureManager::GetInstance()->load("need for A+_noteBoom", "notesBoom_sprite", m_pRenderer);
	TextureManager::GetInstance()->load("need for A+_noteBoom1", "notesBoom1_sprite", m_pRenderer);
	TextureManager::GetInstance()->load("need for A+_PowerNoteStartBoom", "powerNoteStartBoom_sprite", m_pRenderer);
	TextureManager::GetInstance()->load("need for A+_noteBoom_trash", "BoomTrash_sprite", m_pRenderer);
	TextureManager::GetInstance()->load("need for A+_missBoom", "playerMissBoom_sprite", m_pRenderer);

	//��Ʈ ���� �ִϸ��̼�
	TextureManager::GetInstance()->load("need for A+_noteShooter_stage1_idle", "noteShooter_stage1_idle_sprite", m_pRenderer);
	TextureManager::GetInstance()->load("need for A+_noteShooter_stage1_pop", "noteShooter_stage1_pop_sprite", m_pRenderer);
	//TextureManager::GetInstance()->load("need for A+_noteShooter_stage2", "noteShooter_stage2_sprite", m_pRenderer);

	//UI 
	TextureManager::GetInstance()->load("need for A+_selectMenu", "selectMenu_sprite", m_pRenderer); 
	TextureManager::GetInstance()->load("need for A+_fadePanel", "fadePanel_sprite", m_pRenderer);

	//ü�¹� 
	TextureManager::GetInstance()->load("need for A+_healthBarPack", "healthBarPack_sprite", m_pRenderer);
	//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	m_gameObjects.push_back(back_stage_back1);

	m_gameObjects.push_back(backScroll);
	m_gameObjects.push_back(back_stage_back_frame2);
	m_gameObjects.push_back(back_stage_back_frame1);
	m_gameObjects.push_back(back_stage_back_frame);

	m_gameObjects.push_back(back_stage_back2);
	m_gameObjects.push_back(back_stage1);

	m_gameObjects.push_back(notePad);
	m_gameObjects.push_back(notePad1);
	m_gameObjects.push_back(notePad2);
	m_gameObjects.push_back(notePad3);

	m_gameObjects.push_back(powerNotePad1);
	m_gameObjects.push_back(powerNotePad2); 

	m_gameObjects.push_back(NoteShooter1); //SetPos 

	m_gameObjects.push_back(hpBar_Back);
	m_gameObjects.push_back(hpBar);
	m_gameObjects.push_back(energyBar);

	m_gameObjects.push_back(lerpPanel);

	m_gameObjects.push_back(player);
	//ObjectPool
	InitPool();
	std::cout << "ObjectSize => " << m_gameObjects.size() << "\n\n";

	//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	//Setting
	NoteManager::GetInstance()->ReadLineToTxt("stage1");
	//Position
	notePad->SetPosition(Vector2D(1536 * 0.5f - 250, 550));
	notePad1->SetPosition(Vector2D(1536 * 0.5f - 100, 550));
	notePad2->SetPosition(Vector2D(1536 * 0.5f + 50, 550));
	notePad3->SetPosition(Vector2D(1536 * 0.5f + 200, 550));

	powerNotePad1->SetPosition(Vector2D(1536 * 0.5f - 550, 550));
	powerNotePad2->SetPosition(Vector2D(1536 * 0.5f - 400, 400));

	NoteShooter1->SetPosition(Vector2D(1300, 800));

	player->PosTrigger();

	hpBar_Back->SetPosition(Vector2D(640, 750));
	hpBar->SetPosition(Vector2D(640, 750));

	energyBar->SetPosition(Vector2D(830, 750));

	NoteManager::GetInstance()->SetPowerNotePads(powerNotePad1);
	NoteManager::GetInstance()->SetPowerNotePads(powerNotePad2);
	//�ش� ���������� �����Ҷ� �߰� �ϵ��� ����
	NoteManager::GetInstance()->SetNoteShooters(NoteShooter1);
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
	if (isGameOver) return;
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
	Pool* pools[11] = { new Pool("LeftNote", 10), new Pool("UpNote", 10), new Pool("DownNote" ,10), new Pool("RightNote", 10) , new Pool("PowerNote", 10), new Pool("WinBoom", 13), new Pool("MissBoom", 13), new Pool("BoomTrashA", 15), new Pool("BoomTrashF", 15), new Pool("PowerNoteStartBoom", 10), new Pool("PlayerMiss", 10) };
	for (Pool* pool : pools) //���� ���� �������� ���� ������ ���Ļ��
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
		gameObject = new Note(new LoaderParams(0, 0, 144, 144, 0, 0, "notes_sprite"), name);
	}
	else if (name == "UpNote") {
		gameObject = new Note(new LoaderParams(0, 0, 144, 144, 0, 1, "notes_sprite"), name);
	}
	else if (name == "DownNote") {
		gameObject = new Note(new LoaderParams(0, 0, 144, 144, 0, 2, "notes_sprite"), name);
	}
	else if (name == "RightNote") {
		gameObject = new Note(new LoaderParams(0, 0, 144, 144, 0, 3, "notes_sprite"), name);
	}
	else if (name == "PowerNote") {
		gameObject = new PowerNote(new LoaderParams(0, 0, 144, 144, 0, 0, "powerNotes_sprite"));
	}
	else if (name == "WinBoom") {
		gameObject = new NoteBoom(new LoaderParams(0, 0, 192, 192, 0, 0, "notesBoom_sprite"), 5);
	}
	else if (name == "MissBoom") {
		gameObject = new NoteBoom(new LoaderParams(0, 0, 192, 192, 0, 0, "notesBoom1_sprite"), 5);
	}
	else if (name == "BoomTrashA") {
		gameObject = new PowerNote(new LoaderParams(0, 0, 48, 48, 0, 0, "BoomTrash_sprite"));
	}
	else if (name == "BoomTrashF") {
		gameObject = new PowerNote(new LoaderParams(0, 0, 48, 48, 0, 0, "BoomTrash_sprite"));
	}
	else if (name == "PowerNoteStartBoom") {
		gameObject = new NoteBoom(new LoaderParams(0, 0, 144, 144, 0, 0, "powerNoteStartBoom_sprite"), 3);
	}
	else if (name == "PlayerMiss") {
		gameObject = new NoteBoom(new LoaderParams(0, 0, 240, 240, 0, 0, "playerMissBoom_sprite"), 1);
	}
	gameObject->SetName(name);
	gameObject->SetActive(false);
	//All Objects
	m_gameObjects.emplace_back(gameObject);
	allObjects.emplace_back(gameObject);
	//ObjectPool, collision Object
	objects[name].emplace_back(gameObject);
	if (gameObject->getTag() == "Note" || gameObject->getTag() == "PowerNote") collisionObjects.emplace_back(gameObject);

	return gameObject;
}
GameObject* Game::GetObject(Vector2D spawnPos, const char* name)
{
	GameObject* gameObject = objects[name].back();
	gameObject->SetActive(true);
	gameObject->SetPosition(spawnPos);

	objects[name].pop_back();
	return gameObject;
}
//----------------------------------------------------------------------
//PlayInput
void Game::handleInput()
{
	//Command Pattern - ����ȭ��, �÷��� 
	Input_Play();
}
void Game::Input_Play()
{
	//Quit
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
		m_bRunning = false;
	}
	//KeyDown
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)) {
		leftButton->Pressed();
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)) {
		upButton->Pressed();
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN)) {
		downButton->Pressed();
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)) {
		rightButton->Pressed();
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE)) {
		spaceButton->Pressed();
	}
	//KeyUp
	if (!TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)) {
		leftButton->UnPressed();
	}
	if (!TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)) {
		upButton->UnPressed();
	}
	if (!TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN)) {
		downButton->UnPressed();
	}
	if (!TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)) {
		rightButton->UnPressed();
		player->PressOut_Right();
	}
	if (!TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE)) {
		spaceButton->UnPressed();
	}
}
void Game::GameOver() 
{
	OffObjects();
	lerpPanel->SetActive(true);
	player->Dead();
	isGameOver = true;
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
*/
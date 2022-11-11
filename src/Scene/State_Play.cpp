#include <State_Play.h>

State_Play* State_Play::instance = 0;

void State_Play::Awake()
{
	//game->ChangeState( CPlayState::Instance() );
	//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	//스테이지 배경
	TextureManager::GetInstance()->load("need for A+_stage1", "stage1_sprite", m_pRenderer);
	TextureManager::GetInstance()->load("need for A+_stage1_back_frame", "stage1_back_frame_sprite", m_pRenderer);
	TextureManager::GetInstance()->load("need for A+_stage1_back", "stage1_back_sprite", m_pRenderer);
	//TextureManager::GetInstance()->load("need for A+_stage2", "stage2_sprite", m_pRenderer);
	//TextureManager::GetInstance()->load("need for A+_stage2_back", "stage2back_sprite", m_pRenderer);

	//메인캐릭터 
	TextureManager::GetInstance()->load("need for A+_main", "mainCharacter_sprite", m_pRenderer); //need for A+_main_dead

	//노트
	TextureManager::GetInstance()->load("need for A+_notes", "notes_sprite", m_pRenderer);
	TextureManager::GetInstance()->load("need for A+_PowerNote", "powerNotes_sprite", m_pRenderer);

	//노트 패드
	TextureManager::GetInstance()->load("need for A+_notesPad", "notesPad_sprite", m_pRenderer);
	TextureManager::GetInstance()->load("need for A+_PowernotePad", "powerNotesPad_sprite", m_pRenderer);

	//노말 버튼
	TextureManager::GetInstance()->load("need for A+_upDownCok", "nomalButton_sprite", m_pRenderer);

	//폭발 애니메이션  
	TextureManager::GetInstance()->load("need for A+_noteBoom", "notesBoom_sprite", m_pRenderer);
	TextureManager::GetInstance()->load("need for A+_noteBoom1", "notesBoom1_sprite", m_pRenderer);
	TextureManager::GetInstance()->load("need for A+_PowerNoteStartBoom", "powerNoteStartBoom_sprite", m_pRenderer);
	TextureManager::GetInstance()->load("need for A+_noteBoom_trash", "BoomTrash_sprite", m_pRenderer);
	TextureManager::GetInstance()->load("need for A+_missBoom", "playerMissBoom_sprite", m_pRenderer);

	//노트 슈터 애니메이션
	TextureManager::GetInstance()->load("need for A+_noteShooter_stage1_idle", "noteShooter_stage1_idle_sprite", m_pRenderer);
	TextureManager::GetInstance()->load("need for A+_noteShooter_stage1_pop", "noteShooter_stage1_pop_sprite", m_pRenderer);
	//TextureManager::GetInstance()->load("need for A+_noteShooter_stage2", "noteShooter_stage2_sprite", m_pRenderer);

	//UI 
	TextureManager::GetInstance()->load("need for A+_selectMenu_music", "selectMenu_music_sprite", m_pRenderer);
	TextureManager::GetInstance()->load("need for A+_selectMenu", "selectMenu_sprite", m_pRenderer);
	TextureManager::GetInstance()->load("need for A+_fadePanel", "fadePanel_sprite", m_pRenderer); 
	TextureManager::GetInstance()->load("need for A+_upDownCok", "upDownCok_sprite", m_pRenderer); 

	//체력바 
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

	m_gameObjects.push_back(normalButton1);
	m_gameObjects.push_back(normalButton2);

	m_gameObjects.push_back(powerNotePad1);
	m_gameObjects.push_back(powerNotePad2);

	m_gameObjects.push_back(NoteShooter1); 

	m_gameObjects.push_back(hpBar_Back);
	m_gameObjects.push_back(hpBar);
	m_gameObjects.push_back(energyBar);

	m_gameObjects.push_back(gameOverPanel);

	m_gameObjects.push_back(player); 

	m_gameObjects.push_back(musicSelect_music);
	m_gameObjects.push_back(musicSelect); 
	//m_gameObjects.push_back(lerpPanel);
	//ObjectPool
	InitPool();
	std::cout << "ObjectSize => " << m_gameObjects.size() << "\n\n";

	//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	//Setting
	SetCommand(nullCommand, upCommand, downCommand, nullCommand, nullCommand);
	//stageController->StageDataInit();
	//NoteManager::GetInstance()->ReadLineToTxt("stage1");
	//Position
	notePad->SetPosition(Vector2D(1536 * 0.5f - 250, 550));
	notePad1->SetPosition(Vector2D(1536 * 0.5f - 100, 550));
	notePad2->SetPosition(Vector2D(1536 * 0.5f + 50, 550));
	notePad3->SetPosition(Vector2D(1536 * 0.5f + 200, 550));

	powerNotePad1->SetPosition(Vector2D(1536 * 0.5f - 550, 550));
	powerNotePad2->SetPosition(Vector2D(1536 * 0.5f - 400, 400));
	NoteShooter1->SetPosition(Vector2D(1300, 800)); 

	normalButton1->SetPosition(Vector2D(1100, 50));
	normalButton2->SetPosition(Vector2D(1100, 850));

	OnOffStageSetting(false);

	musicSelect->SetPosition(Vector2D(800, 150));
	musicSelect_music->SetPosition(Vector2D(814, 220));

	hpBar_Back->SetPosition(Vector2D(640, 750));
	hpBar->SetPosition(Vector2D(640, 750));
	energyBar->SetPosition(Vector2D(830, 750));

	NoteManager::GetInstance()->SetPowerNotePads(powerNotePad1);
	NoteManager::GetInstance()->SetPowerNotePads(powerNotePad1);
	//해당 스테이지가 시작할때 추가 하도록 변경
	NoteManager::GetInstance()->SetNoteShooters(NoteShooter1);
}
void State_Play::update(Game* game)
{
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->update();
	}
	//GameOver;
	if (hp <= 0 && !isGameOver) { GameOver(); }
	//State N
	if (isGameOver == false || isStageStart == false)
	{
		//NoteManager::GetInstance()->ReadSpawnNotes(); //추가 필요--> 1스테이지 버튼 => 1스테이지 시트, 2스테이지 버튼 => 2스테이지 시트 
	}
}
void State_Play::render(Game* game)
{
	SDL_RenderClear(m_pRenderer);

	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->draw();
	}
	SDL_RenderPresent(m_pRenderer);
}
void State_Play::handleEvents(Game* game)
{
	TheInputHandler::Instance()->update();
	handleInput();
}
void State_Play::clean()
{
	TextureManager::GetInstance()->TextureAllClean();
	TheInputHandler::Instance()->clean();
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}
//----------------------------------------------------------------------------
//ObjectPool
void State_Play::InitPool()
{
	Pool* pools[11] = { new Pool("LeftNote", 10), new Pool("UpNote", 10), new Pool("DownNote" ,10), new Pool("RightNote", 10) , new Pool("PowerNote", 10), new Pool("WinBoom", 13), new Pool("MissBoom", 13), new Pool("BoomTrashA", 15), new Pool("BoomTrashF", 15), new Pool("PowerNoteStartBoom", 10), new Pool("PlayerMiss", 10) };
	for (Pool* pool : pools) //이중 값을 가져오기 위해 포인터 형식사용
	{
		for (int i = 0; i < pool->m_size; i++)
		{
			CreateObjects(pool->m_name);
		}
	}
}
GameObject* State_Play::CreateObjects(const char* name)
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
GameObject* State_Play::GetObject(Vector2D spawnPos, const char* name)
{
	GameObject* gameObject = objects[name].back();
	gameObject->SetActive(true);
	gameObject->SetPosition(spawnPos);

	objects[name].pop_back();
	return gameObject;
}
//----------------------------------------------------------------------
//PlayInput
void State_Play::handleInput()
{
	//Command Pattern - 메인화면, 플레이 
	Input_Play();
}
void State_Play::Input_Play()
{
	//Quit 
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
		//m_bRunning = false; game->Quit();
	}
	if (isKeyStop) return; 
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
	}
	if (!TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE)) {
		spaceButton->UnPressed();
	}
	//KeyDown
	if (isGameOver) return;
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
}
void State_Play::GameOver()
{
	OffObjects();
	gameOverPanel->SetActive(true);
	player->Dead();
	isKeyStop = true;
	isGameOver = true;
}
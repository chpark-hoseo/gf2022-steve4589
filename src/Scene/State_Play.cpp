#include <State_Play.h>
#include <ScoreManager.h>
#include <SoundEffect.h>

State_Play* State_Play::instance = 0;

void State_Play::Awake()
{
	//game->ChangeState( CPlayState::Instance() );
	//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	//�������� ���
	TextureManager::GetInstance()->load("need for A+_stage0", "stage0_sprite", m_pRenderer);
	TextureManager::GetInstance()->load("need for A+_stage0_back_frame", "stage0_back_frame_sprite", m_pRenderer);
	TextureManager::GetInstance()->load("need for A+_stage0_back", "stage0_back_sprite", m_pRenderer);

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

	//��ư
	TextureManager::GetInstance()->load("need for A+_upDownCok", "nomalButton_sprite", m_pRenderer);
	TextureManager::GetInstance()->load("need for A+_spaceButton", "spaceButton_sprite", m_pRenderer);

	//���� �ִϸ��̼�  
	TextureManager::GetInstance()->load("need for A+_noteBoom", "notesBoom_sprite", m_pRenderer);
	TextureManager::GetInstance()->load("need for A+_noteBoom1", "notesBoom1_sprite", m_pRenderer);
	TextureManager::GetInstance()->load("need for A+_PowerNoteStartBoom", "powerNoteStartBoom_sprite", m_pRenderer);
	TextureManager::GetInstance()->load("need for A+_noteBoom_trash", "BoomTrash_sprite", m_pRenderer);
	TextureManager::GetInstance()->load("need for A+_missBoom", "playerMissBoom_sprite", m_pRenderer);

	//��Ʈ ���� �ִϸ��̼�
	TextureManager::GetInstance()->load("need for A+_noteShooter_stage1_idle", "noteShooter_stage1_idle_sprite", m_pRenderer);
	TextureManager::GetInstance()->load("need for A+_noteShooter_stage1_pop", "noteShooter_stage1_pop_sprite", m_pRenderer);

	//UI 
	TextureManager::GetInstance()->load("need for A+_selectMenu_music", "selectMenu_music_sprite", m_pRenderer);
	TextureManager::GetInstance()->load("need for A+_selectMenu", "selectMenu_sprite", m_pRenderer);
	TextureManager::GetInstance()->load("need for A+_fadePanel", "fadePanel_sprite", m_pRenderer);
	TextureManager::GetInstance()->load("need for A+_upDownCok", "upDownCok_sprite", m_pRenderer);
	TextureManager::GetInstance()->load("need for A+_loadingCircle", "loadingCircle_sprite", m_pRenderer);

	TextureManager::GetInstance()->load("need for A+_grade", "grade_sprite", m_pRenderer);
	TextureManager::GetInstance()->load("need for A+_grade_play", "play_grade_sprite", m_pRenderer);

	//ü�¹� 
	TextureManager::GetInstance()->load("need for A+_healthBarPack", "healthBarPack_sprite", m_pRenderer);
	//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	//��ġ ������� �׸��� ������ ������ �ֱ� 
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
	m_gameObjects.push_back(mainScore_grade);
	m_gameObjects.push_back(playScore_grade);

	m_gameObjects.push_back(spaceButton1);
	m_gameObjects.push_back(lerpPanel);
	//ObjectPool
	InitPool();
	std::cout << "ObjectSize => " << m_gameObjects.size() << "\n\n";
	//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	//Setting
	OnOffStageSetting(false);
	ScoreManager::GetInstance()->AddScoreSprite(playScore_grade);
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
	spaceButton1->SetPosition(Vector2D(1150, 595));

	musicSelect->SetPosition(Vector2D(800, 150));
	musicSelect_music->SetPosition(Vector2D(814, 220));

	hpBar_Back->SetPosition(Vector2D(640, 750));
	hpBar->SetPosition(Vector2D(640, 750));
	energyBar->SetPosition(Vector2D(830, 750));

	mainScore_grade->SetPosition(Vector2D(1265, 605));
	playScore_grade->SetPosition(Vector2D(1200, 10));

	NoteManager::GetInstance()->SetPowerNotePads(powerNotePad1);
	NoteManager::GetInstance()->SetPowerNotePads(powerNotePad1);
	//�ش� ���������� �����Ҷ� �߰� �ϵ��� ����
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
	if (isGameOver == false && isStageStart == true)
	{
		if (NoteManager::GetInstance()->ReadSpawnNotes() == true) //true => ����� �̰�� 
		{
			//fade in �ڷ�ƾ�� �Բ� StageEnd()ȣ��, ������ �ð��ִٸ� 
		}
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
	Pool* pools[12] = { new Pool("LeftNote", 10), new Pool("UpNote", 10), new Pool("DownNote" ,10), new Pool("RightNote", 10) , new Pool("PowerNote", 10), new Pool("WinBoom", 13), new Pool("MissBoom", 13), new Pool("BoomTrashA", 15), new Pool("BoomTrashF", 15), new Pool("PowerNoteStartBoom", 10), new Pool("PlayerMiss", 10), new Pool("SoundEffect", 15) };
	for (Pool* pool : pools) //���� ���� �������� ���� ������ ���Ļ��
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
		gameObject = new NoteBoom(new LoaderParams(0, 0, 192, 192, 0, 0, "notesBoom_sprite"), 5, name);
	}
	else if (name == "MissBoom") {
		gameObject = new NoteBoom(new LoaderParams(0, 0, 192, 192, 0, 0, "notesBoom1_sprite"), 5, name);
	}
	else if (name == "BoomTrashA") {
		gameObject = new BoomTrash(new LoaderParams(0, 0, 48, 48, 0, 1, "BoomTrash_sprite"), name);
	}
	else if (name == "BoomTrashF") {
		gameObject = new BoomTrash(new LoaderParams(0, 0, 48, 48, 0, 0, "BoomTrash_sprite"), name);
	}
	else if (name == "PowerNoteStartBoom") {
		gameObject = new NoteBoom(new LoaderParams(0, 0, 144, 144, 0, 0, "powerNoteStartBoom_sprite"), 3, name);
	}
	else if (name == "PlayerMiss") {
		gameObject = new NoteBoom(new LoaderParams(0, 0, 240, 240, 0, 0, "playerMissBoom_sprite"), 1, name);
	}
	else if (name == "SoundEffect") {
		gameObject = new SoundEffect(new LoaderParams(0, 0, 240, 240, 0, 0, "playerMissBoom_sprite"));
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
	//Command Pattern - ����ȭ��, �÷��� 
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
//----------------------------------------------------------------------
//StageManage
void State_Play::StageStart(string stageName)
{
	if (stageName != "")
	{
		OnOffStageSetting(true);

		stageController->ChangeBFX();
		NoteManager::GetInstance()->ReadLineToTxt(stageName);
		SetCommand(left_NoteCommend, up_NoteCommand, down_NoteCommand, right_NoteCommand, space_NoteCommand);

		isStageStart = true;
	}
}
void State_Play::StageEnd()
{
	if (isGameOver == true)
	{
		int grade = ScoreManager::GetInstance()->CaculateGrade();
		stageController->SaveGrade(stageName, grade);
	}
	else { stageController->SaveGrade(stageName, 0); }

	hp = MAX_HP;
	energy = MAX_ENERGY;

	SetCommand(nullCommand, upCommand, downCommand, nullCommand, spaceCommand);
	OnOffStageSetting(false);
	player->DeadOff();
	stageController->ChangeBFX();

	isKeyStop = false;
	isGameOver = false;
}
void State_Play::GameOver() //�ڷ�ƾ���� �����Ұ� 
{
	OffObjects();
	gameOverPanel->SetActive(true);
	playScore_grade->SetActive(false);

	player->Dead();

	Mix_HaltMusic();

	isStageStart = false;
	isKeyStop = true;
	isGameOver = true;

	StageEnd();//�ڷ�ƾ ������ �۵��ϰ� ����
}

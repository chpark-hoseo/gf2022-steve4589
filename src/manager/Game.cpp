#pragma once
#include <Game.h>
#include <SDLGameObject.h>

Game* Game::s_pInstance = 0;

class Pool //������ �ٸ� ���ӿ�����Ʈ�� �����ϱ� ���� ����üó�� ����մϴ�
{
public:
	Pool(const char name[20], SDLGameObject* note, int size) : m_name(name), m_gameObj(note), m_size(size) {}
	const char* m_name;
	SDLGameObject* m_gameObj;
	int m_size;
};

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
	m_gameObjects.push_back(new SDLGameObject(new LoaderParams(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, "stage1_sprite")));
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
	Pool* pools[4] = { new Pool("LeftNote", m_note, 15), new Pool("UpNote", m_note1, 15), new Pool("DownNote", m_note2, 15), new Pool("RightNote", m_note3, 15) };
	for (Pool* pool : pools) //���� ���� �������� ���� ������ ���Ļ��
	{
		for (int i = 0; i < pool->m_size; i++)
		{
			SDLGameObject* gameObject = CreateObjects(pool->m_name, pool->m_gameObj);
			gameObject->SetActive(false); //���� �۵����� �ʰ� ��������ϴ�  
		}
		name_size = (int)objects[pool->m_name].size();
	}
}
SDLGameObject* Game::CreateObjects(const char* name, SDLGameObject* getGameObject)
{
	SDLGameObject* gameObject = getGameObject;

	gameObject->SetName(name);
	
	objects[name].emplace_back(gameObject); //�̸� �� ���� ���ϴ� ������Ʈ�� �����ɴϴ�
	m_gameObjects.emplace_back(gameObject);

	return gameObject;

}
SDLGameObject** Game::GetObject(Vector2D spawnPos, const char* name)
{
	--name_size;

	SDLGameObject** gameObject = &objects[name][name_size];
	(*gameObject)->SetActive(true);
	(*gameObject)->SetPosition(spawnPos);

	std::cout << name << " Name_Size : " << name_size << "\n";
	std::cout << name << " Ptr : " << gameObject << "\n";
	std::cout << name << " Solo Ptr : " << *gameObject << "\n";
	std::cout << name << " Memory Size : " << objects[name].capacity() << "\n";

	//objects[name].pop_back();
	//objects[name].shrink_to_fit(); //�޸� �ʱ�ȭ, ����õ
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
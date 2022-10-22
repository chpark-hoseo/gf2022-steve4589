/*#include <ObjectManager.h>
#include <Note.h>
#include <NoteBoom.h>

ObjectManager* ObjectManager::s_pInstance = NULL;

void ObjectManager::InitPool()
{
	Pool* pools[5] = { new Pool("LeftNote", leftNote, 10), new Pool("UpNote", upNote, 10), new Pool("DownNote", downNote ,10), new Pool("RightNote", rightNote, 10) , new Pool("WinBoom", rightNote, 15) };
	for (Pool* pool : pools) //이중 값을 가져오기 위해 포인터 형식사용
	{
		for (int i = 0; i < pool->m_size; i++)
		{
			CreateObjects(pool->m_name, pool->m_obj);
		}
	}
}
GameObject* ObjectManager::CreateObjects(const char* name, SDLGameObject* getGameObject)
{
	GameObject* gameObject = getGameObject;

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
	else if (name == "WinBoom") {
		gameObject = new NoteBoom(new LoaderParams(0, 0, 128, 128, 0, 0, "notesBoom_sprite"));
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
GameObject* ObjectManager::GetObject(Vector2D spawnPos, const char* name)
{
	GameObject* gameObject = objects[name].back();
	gameObject->SetActive(true);
	gameObject->SetPosition(spawnPos);

	objects[name].pop_back();
	return gameObject;
}*/
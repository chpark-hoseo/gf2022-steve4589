#pragma once
#include <ObjManager.h>
#include <Game.h>

ObjManager* ObjManager::instance = 0;

vector<GameObject*> ObjManager::InitPool()
{
	Pool * pools[4] = { new Pool("LeftNote", m_note, 15), new Pool("UpNote", m_note1, 15), new Pool("DownNote", m_note2, 15), new Pool("RightNote", m_note3, 15) };
	//스폰되는 오브젝트의 총 종류 -> 4 종류
	vector<GameObject*> allObj;
	for (Pool* pool : pools) //이중 값을 가져오기 위해 포인터 형식사용
	{
		for (int i = 0; i < pool->m_size; i++)
		{
			SDLGameObject* gameObject = CreateObjects(pool->m_name, pool->m_gameObj);
			gameObject->SetActive(false); //당장 작동하지 않게 기능을끕니다  

			allObj.push_back(gameObject);
		}
	}
	return allObj; //game의 update, draw에서 돌릴 수 있게 리턴
}
SDLGameObject* ObjManager::CreateObjects(const char* name, SDLGameObject* getGameObject)
{
	SDLGameObject* gameObject = getGameObject;
	//앞으로, name멤버 변수를 통해 원하는 오브젝트를 빼낼 수 있습니다
	gameObject->SetName(name);
	std::cout << gameObject->GetName() << " 스폰" << endl;
	return gameObject;
}

SDLGameObject* ObjManager::GetObject(Vector2D spawnPos, const char name[20])
{
	for (int i = 0; Game::GetInstance()->GetGameObjects().size(); i++)
	{
		if (Game::GetInstance()->GetGameObjects()[i]->GetName() == name && Game::GetInstance()->GetGameObjects()[i]->GetOnOff() == false) //이름이 같고 꺼져있다면 
		{

		}
	}
	SDLGameObject* gameObject = NULL;
	gameObject->SetActive(true);
	return m_note;
}
#pragma once
#include <ObjManager.h>
#include <Game.h>

ObjManager* ObjManager::instance = 0;

vector<GameObject*> ObjManager::InitPool()
{
	Pool * pools[4] = { new Pool("LeftNote", m_note, 15), new Pool("UpNote", m_note1, 15), new Pool("DownNote", m_note2, 15), new Pool("RightNote", m_note3, 15) };
	//�����Ǵ� ������Ʈ�� �� ���� -> 4 ����
	vector<GameObject*> allObj;
	for (Pool* pool : pools) //���� ���� �������� ���� ������ ���Ļ��
	{
		for (int i = 0; i < pool->m_size; i++)
		{
			SDLGameObject* gameObject = CreateObjects(pool->m_name, pool->m_gameObj);
			gameObject->SetActive(false); //���� �۵����� �ʰ� ��������ϴ�  

			allObj.push_back(gameObject);
		}
	}
	return allObj; //game�� update, draw���� ���� �� �ְ� ����
}
SDLGameObject* ObjManager::CreateObjects(const char* name, SDLGameObject* getGameObject)
{
	SDLGameObject* gameObject = getGameObject;
	//������, name��� ������ ���� ���ϴ� ������Ʈ�� ���� �� �ֽ��ϴ�
	gameObject->SetName(name);
	std::cout << gameObject->GetName() << " ����" << endl;
	return gameObject;
}

SDLGameObject* ObjManager::GetObject(Vector2D spawnPos, const char name[20])
{
	for (int i = 0; Game::GetInstance()->GetGameObjects().size(); i++)
	{
		if (Game::GetInstance()->GetGameObjects()[i]->GetName() == name && Game::GetInstance()->GetGameObjects()[i]->GetOnOff() == false) //�̸��� ���� �����ִٸ� 
		{

		}
	}
	SDLGameObject* gameObject = NULL;
	gameObject->SetActive(true);
	return m_note;
}
#pragma once
#include <ObjManager.h>
/*
vector<SDLGameObject*> ObjManager::InitPool()
{
	vector<SDLGameObject*> allObj;
	for (Pool * pool : pools) //이중 포인 값을 가져오기 위해 포인터 형식사용
	{
		for (int i = 0; i < pool->m_size; i++)
		{
			int x = 5;
			int* ptr = &x;
			SDLGameObject obj = pool->m_gameObj;
			SDLGameObject gameObject = CreateObjects(pool->m_name, pool->m_gameObj);
			allObj.push_back(&gameObject);
		}
	}
	return allObj; //game문의 update, draw에서 돌릴 수 있게 리턴
}
SDLGameObject ObjManager::CreateObjects(const char* name, SDLGameObject gameObject)
{
	std::cout << name << " 스폰" << endl;
	SDLGameObject getGameObject = gameObject;

	return gameObject;
}

SDLGameObject* ObjManager::GetObject(Vector2D spawnPos, stinrg name)
{
	return m_note;
}*/
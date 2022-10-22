/*ragma once
#include <SDLGameObject.h>
#include <vector>

class Pool 
{
public:
	Pool(const char name[20], SDLGameObject* obj, int size) : m_name(name), m_obj(obj), m_size(size) {}
	const char* m_name;
	SDLGameObject* m_obj;
	int m_size;
};

class ObjectManager
{
private :
	static ObjectManager* s_pInstance;

	vector<GameObject*> m_gameObjects;
	//object Manage
	vector<GameObject*> collisionObjects; //충돌할 수 있는 오브젝트 
	map<const char*, vector<GameObject* >> objects; //모든 오브젝트
	//Notes
	SDLGameObject* leftNote = new Note(new LoaderParams(0, 0, 96, 96, 0, 0, "notes_sprite"));
	SDLGameObject* upNote = new Note(new LoaderParams(0, 0, 96, 96, 0, 1, "notes_sprite"));
	SDLGameObject* downNote = new Note(new LoaderParams(0, 0, 96, 96, 0, 2, "notes_sprite"));
	SDLGameObject* rightNote = new Note(new LoaderParams(0, 0, 96, 96, 0, 3, "notes_sprite"));
public:
	static ObjectManager* GetInstance() {
		if (s_pInstance == 0) {
			s_pInstance = new ObjectManager();
			return s_pInstance;
		}
		return s_pInstance;
	}
	//
	void InitPool(); //풀에 오브젝트를 집어넣고, game에 내보내는 역할 
	GameObject* CreateObjects(const char* tag, SDLGameObject* getGameObject);
	GameObject* GetObject(Vector2D spawnPos, const char* name);
	void ReturnPool(const char name[20], GameObject* getGameObject) { objects[name].emplace_back(getGameObject); };
};*/
#pragma once
#include <GameObject.h>

//interface
class INoteType {
public:
	virtual Vector2D startPos() = 0;
	virtual void move() = 0; //toPlayer || Fall
	virtual void crashEvent() = 0; //플레이어 / 미 적중시 이펙트 및 보상 / 패널티
	enum Type
	{
		Left = 0,
		Up,
		Down,
		Right,
		Can1,
		Can2
	};
};
class IEffect {
public:
	virtual void effect() = 0;
};

class SDLGameObject : public GameObject {
public:
	SDLGameObject(const LoaderParams* pParams);
	virtual void draw();
	virtual void update() {}
	virtual void clean() {}
	virtual ~SDLGameObject() {}

	void SetActive(bool isOn);
	virtual void OnEnable() {}
protected:
	Vector2D m_position;
	Vector2D m_vector; //m_position에 값을 넘겨주는 역할
	float speed;

	float m_x;
	float m_y;
	int m_width;
	int m_height;
	int m_currentRow;
	int m_currentFrame;

	std::string m_textureID;
};
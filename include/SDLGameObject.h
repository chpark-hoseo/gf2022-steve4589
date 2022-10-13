#pragma once
#include <GameObject.h>
#include <iostream>

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
	virtual void update() { m_position += m_velocity; 
	} //m_velocity += m_acceleration;
	virtual void clean() {}
	virtual ~SDLGameObject() {}

	float GetSpeed() { return speed; }
	void SetSpeed(float getSpeed) { speed = getSpeed; }

	void SetPosition(Vector2D getPos) { m_position = getPos; }

	void SetActive(bool isOn);
	virtual void OnEnable() {}
protected:
	Vector2D m_position;

	Vector2D m_velocity; 
	Vector2D m_acceleration;
	float speed = 0.5;

	float m_x;
	float m_y;
	int m_width;
	int m_height;
	int m_currentRow;
	int m_currentFrame;

	int i = 0;

	std::string m_textureID;
};
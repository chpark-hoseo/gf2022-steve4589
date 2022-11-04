#pragma once
#include <GameObject.h>
#include <iostream>

//interface
class INoteType {
public:
	virtual void move() = 0;
};
class ICLICK
{
public:
	virtual void IsPressed(bool _isPush) = 0;
};
class SDLGameObject : public GameObject {
public:
	SDLGameObject(const LoaderParams* pParams);
	virtual void draw();
	virtual void update()
	{
		m_position += m_velocity;
		m_velocity += m_acceleration;
	}   
	virtual void clean() {}
	virtual ~SDLGameObject() {}

	void SetPosition(Vector2D getPos) { m_position = getPos; }
	const Vector2D GetPosition() { return m_position; }

	float GetSpeed() { return speed; }
	void SetSpeed(float getSpeed) { speed = getSpeed; }

	const char* GetName() { return name; }
	void SetName(const char* getName) { name = getName; }
	//KeyBoard
	virtual void IsPressed(bool isPush) {}

	virtual void OnEnable() {}
protected:
	Vector2D m_position;
	Vector2D m_velocity;
	Vector2D m_acceleration;
	float speed = 0.5;

	std::string m_textureID;
};
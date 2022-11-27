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
	virtual void IsPressed(bool _isPush) = 0;
	virtual void PressIn(bool) = 0;
	virtual void PressOut(bool) = 0;
};

class SDLGameObject : public GameObject {
public:
	explicit SDLGameObject(const LoaderParams* pParams);

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

	const char* GetName() { return name; }
	float GetSpeed() { return speed; }
	string GetSpriteId() { return m_textureID; }

	void SetSpeed(float getSpeed) { speed = getSpeed; }
	void SetSpriteId(string getId) { m_textureID = getId; }
	void SetSpriteRow(int getRow) { m_currentRow = getRow; }
	void SetSpriteFrame(int getFrame) { m_currentFrame = getFrame; }
	void SetName(const char* getName) { name = getName; }
	//KeyBoard
	virtual void IsPressed(bool isPush) {}
protected:
	Vector2D m_position;
	Vector2D m_velocity;
	Vector2D m_acceleration;

	float speed = 0.5;

	std::string m_textureID;
};
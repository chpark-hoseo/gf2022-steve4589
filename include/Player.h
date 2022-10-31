#pragma once
#include <SDLGameObject.h>
#include <Animation.h>
#include <Timer.h>

typedef struct PlayerSetPosData //1 ~ 4 -> �⺻ ��Ʈ, 5, 6 -> ��������Ʈ 
{
	Vector2D mainPos = Vector2D(0.5f + 640, 750);
	Vector2D playerPos = Vector2D(0.5f + 635, 750);

}pSetPosData;

class Player : public SDLGameObject
{
public:
	Player(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean() {}

	void SetState();

	void Pop_Down();

	//Main, Play Pos
	void PosTrigger()
	{
		if (m_position.getY() == pSetPosData.mainPos.getY()) m_position = pSetPosData.playerPos;
		else m_position = pSetPosData.mainPos;
	}

	//Input
	void PressIn_Left();
	void PressIn_Right();
	void PressIn_Up();
	void PressIn_Down();
	void PressIn_Space();

	void PressOut_Left();
	void PressOut_Right();
	void PressOut_Up();
	void PressOut_Down();
	void PressOut_Space();
private:
	Animation* m_animation = new Animation();
	pSetPosData pSetPosData;

	//Animation
	void Idle_Main() {}
	void Idle_Play();
	void LeftPop();
	void RightPop();

	void PopLife();

	bool popLeft = false;
	bool popRight = false;
	bool idle = true;

	bool isPop = false;

	bool turn = false;
	//Input
	bool isPressIn_Left = true;
	bool isPressIn_Right = true;
	bool isPressIn_Up = true;
	bool isPressIn_Down = true;
	bool isPressIn_Space = true;
	
	bool isPressOut_Left = true;
	bool isPressOut_Right = true;
	bool isPressOut_Up = true;
	bool isPressOut_Down = true;
	bool isPressOut_Space = true;
};
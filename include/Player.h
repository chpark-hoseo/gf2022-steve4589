#pragma once
#include <SDLGameObject.h>
#include <Animation.h>
#include <Timer.h>
#include <iostream>

#define Minimum 0.005f
#define POWERX 4
#define POWERY 10

typedef struct PlayerSetPosData //1 ~ 4 -> 기본 루트, 5, 6 -> 에너지루트 
{
	Vector2D mainPos = Vector2D(0.5f + 640, 750);
	Vector2D playerPos = Vector2D(0.5f + 635, 750);

}pSetPosData;

class Player : public SDLGameObject
{
public:
	explicit Player(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean() {}

	void SetState();
	void Pop_Down();

	//Main, Play Pos
	void PosTrigger(bool isMain)
	{
		if (isMain){
			m_position = pSetPosData.playerPos;
		}
		else{
			m_position = pSetPosData.mainPos;
		}
		isidle_Play = isMain;
		Idle_Play();
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

	void Dead();
	void DeadOff() 
	{
		//초깃값
		powerX = POWERX;
		powerY = POWERY;

		isDead = false;
		isKnockBack = false;

		m_animation->StartAnimation();
		m_animation->SetAnimPause(true);
		m_animation->AnimationOnce(false);
	}
	void KnockBack();

	void PanicOn();
	void PanicOff();
private:
	Animation* m_animation = new Animation();
	pSetPosData pSetPosData;

	//Animation
	void Idle_Main() {}
	void Idle_Play();
	void LeftPop();
	void RightPop();

	void PopLife();

	void Gravity(); //어차피 중력은 여기서밖에 안쓰므로 따로 클래스로 빼두진 않았습니다 

	float powerX = 3;
	float powerY = 10;
	float gravityPower = 4;
	bool isGrounded = false;

	bool ispopLeft = false;
	bool ispopRight = false;
	bool isidle = true;
	bool isidle_Play = false;
	bool ismain = false;
	bool isPanic = false; 

	bool isDead = false;
	bool isKnockBack = false;

	bool isPop = false;
	bool turn = false;

	bool isGravity = false;
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
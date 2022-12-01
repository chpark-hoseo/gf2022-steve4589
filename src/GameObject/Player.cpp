#include <Player.h>
#include <InputHandler.h>

Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams) { Idle_Play(); }

void Player::draw()
{
	m_animation->Draw(m_position.getX(), m_position.getY(), m_width, m_height);
}
void Player::update()
{
	if (!onOff) return;

	m_animation->Update();
	SDLGameObject::update();

	if (isDead == true) { Gravity(); }
	else { m_position = pSetPosData.playerPos; } // <== 비효율적

	if (isDead == true || isPanic == true) return;
	SetState();
	if (m_animation->GetAnimationOnce() == false && isPop)
	{
		m_animation->SetAnimPause(true);
		isPop = false;
		isidle = true;
	}
}

void Player::SetState()
{
	if (isidle == true)
	{
		Idle_Play();
	}
	if (ispopLeft == true)
	{
		LeftPop();
	}
	if (ispopRight == true)
	{
		RightPop();
	}
}
void Player::Idle_Play()
{
	isidle = false;
	m_animation->SetProp(m_textureID, 0.005f, isidle_Play, 12);
	m_animation->SetAnimPause(true);
}
void Player::LeftPop()
{
	ispopLeft = false;
	m_animation->SetProp(m_textureID, 0.01f, 2, 3);
	PopLife();
}
void Player::RightPop()
{
	ispopRight = false;
	m_animation->SetProp(m_textureID, 0.01f, 3, 3);
	PopLife();
}
void Player::PopLife()
{
	isPop = true;

	m_animation->SetAnimPause(true);
	m_animation->AnimationOnce(true);
}
void Player::Pop_Down()
{
	m_animation->StartAnimation();

	if (turn == true)
	{
		ispopRight = true;
		turn = false;
	}
	else
	{
		ispopLeft = true;
		turn = true;
	}
}
void Player::PanicOn()
{
	if (isPanic) return;
	isPanic = true;

	//수초후 HealEnergy(50);

	m_animation->SetProp(m_textureID, 0.008f, 5, 3);

	m_animation->StartAnimation();
	//m_animation->AnimationOnce(true); //이거 끝나면 다시 false로 바꾸기 
}
void Player::PanicOff()
{
	if (!isPanic) return;
	isPanic = false;
	m_animation->SetProp(m_textureID, 0.01f, 5, 2);

	m_animation->StartAnimation();
	m_animation->AnimationOnce(false);
}
void Player::Dead()
{
	std::cout << "Dead\n";

	isDead = true;
	isKnockBack = true;
	isPanic = false;

	m_animation->SetProp(m_textureID, 0.008f, 4, 9);

	m_animation->SetAnimPause(true);
	m_animation->AnimationOnce(true);
	m_animation->StartAnimation();
}

void Player::PressIn_Left()
{
	if (!isPressIn_Left) return;
	isPressIn_Left = false;
	isPressOut_Left = true;

	Pop_Down();
}
void Player::PressIn_Right()
{
	if (!isPressIn_Right) return;
	isPressIn_Right = false;
	isPressOut_Right = true;

	Pop_Down();
}
void Player::PressIn_Down()
{
	if (!isPressIn_Down) return;
	isPressIn_Down = false;
	isPressOut_Down = true;

	Pop_Down();
}
void Player::PressIn_Up()
{
	if (!isPressIn_Up) return;
	isPressIn_Up = false;
	isPressOut_Up = true;

	Pop_Down();
}
void Player::PressIn_Space()
{
	if (!isPressIn_Space) return;
	isPressIn_Space = false;
	isPressOut_Space = true;

	Pop_Down();
}

void Player::PressOut_Left()
{
	if (!isPressOut_Left) return;
	isPressOut_Left = false;
	isPressIn_Left = true;
}
void Player::PressOut_Right()
{
	if (!isPressOut_Right) return;
	isPressOut_Right = false;
	isPressIn_Right = true;
}
void Player::PressOut_Down()
{
	if (!isPressOut_Down) return;
	isPressOut_Down = false;
	isPressIn_Down = true;
}
void Player::PressOut_Up()
{
	if (!isPressOut_Up) return;
	isPressOut_Up = false;
	isPressIn_Up = true;
}
void Player::PressOut_Space()
{
	if (!isPressOut_Space) return;
	isPressOut_Space = false;
	isPressIn_Space = true;
}
//Physics
void Player::Gravity()
{
	KnockBack();
	if (m_position.getY() > pSetPosData.playerPos.getY())
	{
		powerX = 0;
		m_velocity.setX(0);
		m_velocity.setY(0);
		m_position.setY(pSetPosData.playerPos.getY());
		return;
	}
	float gravityX = powerX;
	float gravityY = gravityPower - powerY;

	m_velocity.setX(gravityX);
	m_velocity.setY(gravityY);
}
//Minimum => 0.05f
//0.2
//0.10
void Player::KnockBack()
{
	if (powerX > 0) powerX = powerX - (Minimum * 2); 
	else powerX = 0;

	if (powerY > 0) powerY = powerY - (Minimum * 10 * 2); //0.1f * dirPowerY
	else powerY = 0;
}
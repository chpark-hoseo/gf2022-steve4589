#include <Player.h>
#include <Game.h>
#include <InputHandler.h>

Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams) 
{
	Idle_Play();
}

void Player::draw()
{
	m_animation->Draw(m_position.getX(), m_position.getY(), m_width, m_height);
}
void Player::update()
{
	if (!onOff) return;

	m_animation->Update();
	SetState();

	if (m_animation->GetAnimationOnce() == false && isPop)
	{
		m_animation->SetAnimPause(true);
		isPop = false;
		idle = true;
	}
	SDLGameObject::update();
}

void Player::SetState()
{
	if (idle == true)
	{
		Idle_Play();
	}
	if (popLeft == true)
	{
		LeftPop();
	}
	if (popRight == true)
	{
		RightPop();
	}
}
void Player::Idle_Play()
{
	idle = false;
	m_animation->SetProp(m_textureID, 0.005f, 1, 12);

	m_animation->SetAnimPause(true);
}
void Player::LeftPop()
{
	popLeft = false;
	m_animation->SetProp(m_textureID, 0.01f, 2, 3);
	PopLife();
}
void Player::RightPop()
{
	popRight = false;
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
		popRight = true;
		turn = false;
	}
	else
	{
		popLeft = true;
		turn = true;
	}
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

/*void Player::Input_Play() //각 키마다 따로 있어야 될듯..
{
	//KeyDown
	if (((TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT) || TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT) ||
		TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN) || TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP) ||
		TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE)) && isChange == false))
	{
		Pop_Down();
		isChange = true;
	}
}*/
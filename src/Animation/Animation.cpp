#include <Animation.h>
#include <TextureManager.h>
#include <Game.h>

void Animation::Update()
{
	if (!m_animRunning) { return; }

	double curTime = SDL_GetTicks();
	m_currentFrame = (Uint32)((curTime - startTimer) * m_speed) % m_frameCount; 
	if ((m_animationOnce && m_currentFrame == m_frameCount - 1))  //�ִϸ��̼� �ѹ��� �۵�
	{
		m_animRunning = false;
		m_animationOnce = false;
	}
}

void Animation::StartAnimation()
{
	startTimer = SDL_GetTicks();
	m_currentFrame = 0;
}

void Animation::SetAnimPause(bool onOff) { m_animRunning = onOff; }
void Animation::AnimationOnce(bool onOff)
{
	m_animationOnce = onOff;
}

void Animation::Draw(float x, float y, int width, int height)
{
	TextureManager::GetInstance()->drawFrame(m_textureID,
		(int)x, (int)y, width,
		height, m_spriteRow, m_currentFrame,
		SDL_FLIP_NONE);
}
void Animation::Draw(float x, float y, int width, int height, int hp)
{
	TextureManager::GetInstance()->drawFrame(m_textureID,
		(int)x, (int)y, width,
		height, m_spriteRow, m_currentFrame, hp,
		SDL_FLIP_NONE);
}

void Animation::SetProp(std::string textureID, float speed, int spriteRow, int frameCount)
{
	m_speed = speed;
	m_spriteRow = spriteRow;
	m_frameCount = frameCount;
	m_textureID = textureID;
}

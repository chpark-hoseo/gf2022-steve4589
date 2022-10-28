#include <Animation.h>
#include <TextureManager.h>
#include <Game.h>

void Animation::Update()
{
	if (!m_animRunning) return;
	double curTime = SDL_GetTicks();
	m_currentFrame = (Uint32)((curTime - startTimer) * m_speed ) % m_frameCount; //speed
}

void Animation::StartAnimation()
{
	startTimer = SDL_GetTicks();
}
void Animation::SetAnimPause(bool onOff)
{
	m_animRunning = onOff;
}

void Animation::Draw(float x, float y, int width, int height)
{
	TextureManager::GetInstance()->drawFrame(m_textureID,
		(int)x, (int)y, width,
		height, m_spriteRow, m_currentFrame,
		SDL_FLIP_NONE);
}

void Animation::SetProp(std::string textureID, float speed, int spriteRow, int frameCount)
{
	m_speed = speed;
	m_spriteRow = spriteRow;
	m_frameCount = frameCount;
	m_textureID = textureID;
	std::cout << "ID :::::: " << m_textureID << "   SDfasdf\n";
}

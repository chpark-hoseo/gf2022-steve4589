#include <NoteBoom.h>
#include <Game.h> //#include <ObjectManager>

NoteBoom::NoteBoom(const LoaderParams* pParams) : SDLGameObject(pParams) {}

void NoteBoom::draw()
{
	SDLGameObject::draw();
}
void NoteBoom::update()  
{
	if (!onOff) return;
	Animation();
}
void NoteBoom::Animation()
{
	Uint32 curTime = SDL_GetTicks();
	m_currentFrame = (Uint32)((curTime - startTimer) * 0.01) % 6;

	if (m_currentFrame == 5)
	{
		SetActive(false);
	}
}
void NoteBoom::OnDisable()
{
	Game::GetInstance()->ReturnPool("WinBoom", this);
}
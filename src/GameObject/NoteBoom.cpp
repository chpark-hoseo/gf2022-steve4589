#include <NoteBoom.h>
#include <Game.h> //#include <ObjectManager>

NoteBoom::NoteBoom(const LoaderParams* pParams) : SDLGameObject(pParams) {}

void NoteBoom::draw()
{
	if (!onOff) return;
	//m_animation->Draw(m_position.getX(), m_position.getY(), m_width, m_height);
	SDLGameObject::draw();
}
void NoteBoom::update()
{
	if (!onOff) return;
	OnceAnimation();
	//m_animation->Update();
}
void NoteBoom::OnceAnimation()
{
	Uint32 curTime = SDL_GetTicks();
	m_currentFrame = (Uint32)((curTime - startTimer) * 0.01f) % 6; //0.01 => speed

	if (m_currentFrame == 5)
	{
		SetActive(false);
	}
}
void NoteBoom::OnDisable()
{
	Game::GetInstance()->ReturnPool("WinBoom", this);
}
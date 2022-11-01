#include <HealthBar.h>
#include <Game.h>

HealthBar::HealthBar(const LoaderParams* pParams) : SDLGameObject(pParams) 
{
	animation->SetProp(m_textureID, 0.01f, 0, 12);

	animation->StartAnimation();
	animation->SetAnimPause(true);
}

void HealthBar::draw()
{
	if (!onOff) return;
	animation->Draw(m_position.getX(), m_position.getY(), m_width, m_height, Game::GetInstance()->GetHp());
}
void HealthBar::update()
{
	if (!onOff) return;
	animation->Update();
}
void HealthBar::SetMode()
{

}
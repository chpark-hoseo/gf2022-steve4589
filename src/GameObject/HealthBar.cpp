#include <HealthBar.h>
#include <Game.h>

HealthBar::HealthBar(const LoaderParams* pParams, string getTag, int frameCount) : SDLGameObject(pParams) 
{
	tag = getTag;

	animation->SetProp(m_textureID, 0.01f, m_currentRow, frameCount);

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
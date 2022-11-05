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

	int damaged = 0;
	if (tag == "HpBar") damaged = Game::GetInstance()->GetHp();
	else damaged= Game::GetInstance()->GetEnergy();

	animation->Draw(m_position.getX(), m_position.getY(), m_width, m_height, damaged);
}
void HealthBar::update()
{
	if (!onOff) return;
	animation->Update();
}
void HealthBar::SetMode()
{

}
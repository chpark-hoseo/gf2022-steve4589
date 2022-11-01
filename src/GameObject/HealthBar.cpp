#include <HealthBar.h>

HealthBar::HealthBar(const LoaderParams* pParams) : SDLGameObject(pParams) 
{
	animation->SetProp("healthBarPack_sprite", 0.1f, 0, 12);

	animation->StartAnimation();
	animation->SetAnimPause(true);
}

void HealthBar::draw()
{
	if (!onOff) return;
	animation->Draw(m_position.getX(), m_position.getY(), m_width, m_height);
}
void HealthBar::update()
{
	if (!onOff) return;
	animation->Update();
}
void HealthBar::ResiceRect() //원본 상자의 크기 바구기 
{

}

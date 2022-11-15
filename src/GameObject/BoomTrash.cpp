#include <BoomTrash.h>
#include<State_Play.h>

BoomTrash::BoomTrash(const LoaderParams* pParams) : SDLGameObject(pParams) 
{
	tag = "BoomTrash";
}

void BoomTrash::draw()
{
	SDLGameObject::draw();
}
void BoomTrash::update()
{
	if (!onOff) return;
	SDLGameObject::update();
	move();
}
void BoomTrash::move()
{
	m_position.setX(m_position.getX() + dirVec.getX() * speed);
	m_position.setY(m_position.getY() + dirVec.getY() * speed);

	if (1250 < m_position.getX()) { SetActive(false); }
}
void BoomTrash::OnDisable()
{
	State_Play::GetInstance()->ReturnPool(tag.c_str(), this);
}

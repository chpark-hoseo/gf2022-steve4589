#include<PowerNote.h>
#include<Game.h>

PowerNote::PowerNote(const LoaderParams* pParams) : SDLGameObject(pParams) { tag = "PowerNote"; }

void PowerNote::draw()
{
	SDLGameObject::draw();
}
void PowerNote::update()
{
	if (!onOff) return;
	SDLGameObject::update();
	move();
}
void PowerNote::move()
{
	m_position.setX(m_position.getX() + dirVec.getX() * speed);
	m_position.setY(m_position.getY() + dirVec.getY() * speed);
}
void PowerNote::OnDisable()
{
	Game::GetInstance()->ReturnPool(tag.c_str(), this);
}

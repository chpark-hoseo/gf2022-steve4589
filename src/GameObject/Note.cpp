#pragma once
#include <Note.h>
Note::Note(const LoaderParams* pParams) : SDLGameObject(pParams) {}

void Note::draw()
{
	SDLGameObject::draw();
}
Vector2D Note::startPos()
{
	Vector2D pos = Vector2D(1, 0);
	return pos;
}
void Note::update() //¾Æ·¡·Î 
{
	if (!onOff) return;
	move();
	crashEvent();
}
void Note::clean() {}

void Note::move()
{
	//
	//Vector2D vector = Vector2D(1, 0); 
	//std::cout << vector.getX();
	m_position.setY(m_position.getY() + 1);
}
void Note::crashEvent()
{

}
void Note::OnEnable()
{
	//m_position.setX(0);
	m_position.setY(0);
}

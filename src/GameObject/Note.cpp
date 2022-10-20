#pragma once
#include <Note.h>
#include <iostream>
Note::Note(const LoaderParams* pParams) : SDLGameObject(pParams) { tag = "Note"; }

void Note::draw()
{
	SDLGameObject::draw();
}
Vector2D Note::startPos()
{
	Vector2D pos = Vector2D(1, 0);
	return pos;
}
void Note::update() //아래로 
{
	SDLGameObject::update();
	if (!onOff) return; //임시
	move();
	//crashEvent();
}

void Note::move()
{
	m_position.setY(m_position.getY() + speed);
	//m_velocity.setY(m_position.getY() + speed);
}
void Note::crashEvent()
{

}
void Note::OnEnable()
{
	//m_position.setX(0);
	m_position.setY(0);
}

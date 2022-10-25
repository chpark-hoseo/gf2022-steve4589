#pragma once
#include <Note.h>
#include <NoteBoom.h>
#include <iostream>
#include <Game.h>

Note::Note(const LoaderParams* pParams, const char* name) : SDLGameObject(pParams)
{
	tag = "Note";
}

void Note::draw()
{
	SDLGameObject::draw();
}
void Note::update() //�Ʒ��� 
{
	if (!onOff) return;
	move();
	SDLGameObject::update();
}

void Note::move()
{
	m_position.setY(m_position.getY() + speed);
	//m_velocity.setY(m_position.getY() + speed);
}
void Note::OnDisable()
{
	Game::GetInstance()->ReturnPool(tag.c_str(), this);
	m_position.setXY(0, 0);
}

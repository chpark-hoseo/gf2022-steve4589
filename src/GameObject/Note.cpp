#pragma once
#include <Note.h>
#include <NoteBoom.h>
#include <iostream>
#include <Game.h>

Note::Note(const LoaderParams* pParams, const char* name) : SDLGameObject(pParams)
{
	tag = "Note";
	noteName = name;
}

void Note::draw()
{
	SDLGameObject::draw();
}
void Note::update() //¾Æ·¡·Î 
{
	if (!onOff) return;
	SDLGameObject::update();
	move();
}

void Note::move()
{
	m_position.setY(m_position.getY() + speed);
	//m_velocity.setY(m_position.getY() + speed);
}
void Note::OnDisable()
{
	Game::GetInstance()->ReturnPool(noteName, this);
}

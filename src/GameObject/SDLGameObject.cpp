#pragma once
#include <SDLGameObject.h>
#include <Game.h>

SDLGameObject::SDLGameObject(const LoaderParams* pParams)
	: GameObject(pParams), m_position(pParams->getX(), pParams->getY()), m_velocity(pParams->getX(), pParams->getY()), m_acceleration(pParams->getX(), pParams->getY())
{
	m_width = pParams->getWidth();
	m_height = pParams->getHeight();
	m_textureID = pParams->getTextureID();
	m_currentRow = pParams->getCurrentRow();
	m_currentFrame = pParams->getCurrentFrame();
}

void SDLGameObject::draw() {
	if (!onOff) return;
	TextureManager::GetInstance()->drawFrame(m_textureID,
		(int)m_position.getX(), (int)m_position.getY(), m_width,
		m_height, m_currentRow, m_currentFrame,
		SDL_FLIP_NONE);
}
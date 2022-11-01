#pragma once
#include <TextureManager.h>
#include <Game.h>

TextureManager* TextureManager::s_pInstance = 0; //정적변수를 사용할 수 있게 하기 위해서 

bool TextureManager::load(string fileName, string id, SDL_Renderer* pRenderer)
{
	string set_fileName = "Assets/" + fileName + ".png";
	SDL_Surface* pTempSurface = IMG_Load(set_fileName.c_str());
	if (pTempSurface == 0) {
		return false;
	}
	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
	SDL_FreeSurface(pTempSurface);
	if (pTexture != 0) {
		m_textureMap[id] = pTexture;
		return true;
	}
	return false;
}
void TextureManager::TextureClean(string id)
{
	m_textureMap.erase(id);
}
void TextureManager::TextureAllClean()
{
	m_textureMap.clear();
}

void TextureManager::drawFrame(string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	if (width == NULL)
	{
		SDL_QueryTexture(m_textureMap[id], NULL, NULL, &srcRect.w, &srcRect.h);
		destRect.w = srcRect.w;
		destRect.h = srcRect.h;
	}
	else
	{
		srcRect.w = destRect.w = width;
		srcRect.h = destRect.h = height;
	}

	srcRect.x = width * currentFrame;
	srcRect.y = height * currentRow;

	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(Game::GetInstance()->getRenderer(), m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}
void TextureManager::drawFrame(string id, int x, int y, int width, int height, int currentRow, int currentFrame, int percent, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;
	//MAX_HP == 50;
	float m_percent = (2 * percent) * 0.01f;

	srcRect.w = width;
	srcRect.h = m_percent * height;

	destRect.w = width;
	destRect.h = m_percent * height;

	srcRect.x = width * currentFrame;
	srcRect.y = height * currentRow;

	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(Game::GetInstance()->getRenderer(), m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}
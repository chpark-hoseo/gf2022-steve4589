#pragma once
#include <TextureManager.h>
#include <iostream>

TextureManager* TextureManager::s_pInstance = 0; //���������� ����� �� �ְ� �ϱ� ���ؼ� 

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
void TextureManager::TextureClean(string id) //������� �ʴ� �ؽ��ĸ� �����ϴ� �ڵ� �߰��ϱ� 
{
	m_textureMap.erase(id);
}
void TextureManager::TextureAllClean()
{
	m_textureMap.clear();
	/*
	//������ key�� value���� ���� DestoryTexture����
	map<string, SDL_Texture*>::iterator iter;
	for (iter = m_textureMap.begin(); iter != m_textureMap.end(); iter++) //auto --> var
	{
		SDL_DestroyTexture(m_textureMap["d"]->second);
		cout << iter->second << endl;
	}
	//test
	map<string, SDL_Texture*>::iterator iter1;
	for (iter1 = m_textureMap.begin(); iter1 != m_textureMap.end(); iter1++)
	{
		cout << iter1->second << endl;
	}
	m_textureMap.clear();*/
}

void TextureManager::draw(string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
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
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawFrame(string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = width * currentFrame;
	srcRect.y = height * currentRow;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}
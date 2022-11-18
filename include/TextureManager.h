#pragma once
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>
#include <string>
#include <map> 
#include <wchar.h>

using namespace std;

class TextureManager {
public:
	//정적 멤버함수
	static TextureManager* GetInstance() //다이나믹 싱글턴. 전역변수로 초기화하지 않으므로, 메모리를 확보할 수 있다 
	{
		if (s_pInstance == 0)
			s_pInstance = new TextureManager();
		return s_pInstance;
	}
	bool load(string fileName, string id, SDL_Renderer* pRenderer);
	bool loadFont(string fileName, string id, SDL_Renderer* pRenderer);

	void drawFrame(string id, int x, int y, int width, int height,
		int currentRow, int currentFrame,
		SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFrame(string id, int x, int y, int width, int height,
		int currentRow, int currentFrame,
		int percent,
		SDL_RendererFlip flip);
	void drawFont(const wchar_t* pBuff, int x, int y);

	void TextureAllClean();
	void TextureClean(string id);
private:
	TextureManager() {}
	map<string, SDL_Texture*> m_textureMap;
	static TextureManager* s_pInstance; //정적 멤버변수 선언
};
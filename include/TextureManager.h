#pragma once
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>
#include <string>
#include <map> 
/*     map은 각 노드가 key와 value 쌍으로 이루어진 트리입니다.  특히, 중복을 허용하지 않습니다.
따라서 map은 first, second가 있는 pair 객체로 저장되는 데 first- key로 second- value로 저장됩니다. 
C++의 map의 내부 구현은 검색, 삽입, 삭제가 O(logn) 인 레드블랙트리로 구성되어 있습니다.*/
using namespace std;

class TextureManager {
public:
    TextureManager() {}
    ~TextureManager() {}

    bool load(string fileName, string id, SDL_Renderer* pRenderer);

    void draw(string id, int x, int y, int width, int height,
        SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

    void drawFrame(string id, int x, int y, int width, int height,
        int currentRow, int currentFrame,
        SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
    map<string, SDL_Texture*> m_textureMap;
};

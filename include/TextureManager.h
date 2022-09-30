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
    //정적 멤버함수
    static TextureManager* GetInstance() //다이나믹 싱글턴. 전역변수로 초기화하지 않으므로, 메모리를 확보할 수 있다 
    {
        if (s_pInstance == 0)
            s_pInstance = new TextureManager();
        return s_pInstance;
    }

    bool load(string fileName, string id, SDL_Renderer* pRenderer);

    void draw(string id, int x, int y, int width, int height,
        SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

    void drawFrame(string id, int x, int y, int width, int height,
        int currentRow, int currentFrame,
        SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

    void TextureAllClean();
    void TextureClean(string id);

private:
    TextureManager() {} // 생성자 private으로 선언
    map<string, SDL_Texture*> m_textureMap;
    static TextureManager* s_pInstance; //정적 멤버변수 선언
};

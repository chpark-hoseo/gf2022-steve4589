#pragma once
#include <SDL2/SDL_keyboard.h>
#include <NotePad.h>
class InputHandler {
public: 
    ~InputHandler() {}
    static InputHandler* Instance() {
        if (s_pInstance == 0) {
            s_pInstance = new InputHandler();
        }
        return s_pInstance;
    }
    bool isKeyDown(SDL_Scancode key);
    void update();
    void clean() {}
private:
    //InputHandler() {}
    static InputHandler* s_pInstance;
    const Uint8* m_keystates = SDL_GetKeyboardState(NULL); //이전과 달리 배열로 여러키 감지가능
};
typedef InputHandler TheInputHandler;
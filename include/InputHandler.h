#pragma once
#include <SDL2/SDL.h> 
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
    const Uint8* m_keystates;

    /*GameObject* notePad;
      GameObject* notePad1;
      GameObject* notePad2;
      GameObject* notePad2;
    */
};
typedef InputHandler TheInputHandler;
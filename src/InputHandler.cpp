#include <InputHandler.h>
#include <Game.h>

InputHandler* InputHandler::s_pInstance = 0;

void InputHandler::update()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            TheGame::Instance()->quit();
        }
        if (event.type == SDL_KEYUP) {
            m_keystates = SDL_GetKeyboardState(0);
        }
        if (event.type == SDL_KEYDOWN) {
            m_keystates = SDL_GetKeyboardState(0);
        }
        //Mouse Input
        if (event.type == SDL_MOUSEMOTION) {
            m_mousePosition->setX(event.motion.x);
            m_mousePosition->setY(event.motion.y);
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                m_mouseButtonStates[LEFT] = true;
            }
            if (event.button.button == SDL_BUTTON_MIDDLE) {
                m_mouseButtonStates[MIDDLE] = true;
            }
            if (event.button.button == SDL_BUTTON_RIGHT) {
                m_mouseButtonStates[RIGHT] = true;
            }
        }
        else if (event.type == SDL_MOUSEBUTTONUP) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                m_mouseButtonStates[LEFT] = false;
            }
            if (event.button.button == SDL_BUTTON_MIDDLE) {
                m_mouseButtonStates[MIDDLE] = false;
            }
            if (event.button.button == SDL_BUTTON_RIGHT) {
                m_mouseButtonStates[RIGHT] = false;
            }
        }
    }
}
bool InputHandler::isKeyOneDown(SDL_Scancode key) { //case1
    static int push = 0;
    if (m_keystates != 0) {
        if (m_keystates[key] == 1)
        {
            if (push == 2)
            {
                return false; //누르고 있을땐 2가됨
            }  //test
            else
                return ++push; //한번 눌렀을 때 1이되어 한번만 처리가 된다.
        }
        else {
            push = 0;// 떼었을 때
            return false;
        }
    }
    return false;
}
bool InputHandler::isKeyDown(SDL_Scancode key)
{
    if (m_keystates != 0) {
        if (m_keystates[key] == 1) {
            return true;
        }
        else {
            return false;
        }
    }
    return false;
}
//Mouse Input
bool InputHandler::getMouseButtonState(int buttonNumber) 
{
    return m_mouseButtonStates[buttonNumber];
}
Vector2D* InputHandler::getMousePosition() //포지션 push, pop
{
    return m_mousePosition;
}
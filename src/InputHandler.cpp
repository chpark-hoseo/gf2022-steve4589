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
    }
}
bool InputHandler::isKeyOneDown(SDL_Scancode key) { //case1
    static int push = 0;
    if (m_keystates != 0) {
        if (m_keystates[key] == 1)
        {
            if (push == 2)
            {
                std::cout << "�г��� ����, ��Ÿ�� 0�� : ��ģ���� �����մϴ�\n";
                return false; //������ ������ 2����
            }  //test
            else
                return ++push; //�ѹ� ������ �� 1�̵Ǿ� �ѹ��� ó���� �ȴ�.
        }
        else {
            push = 0;// ������ ��
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
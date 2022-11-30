#include <InputHandler.h>
#include <Game.h>

InputHandler* InputHandler::s_pInstance = 0;

void InputHandler::update()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			TheGame::Instance()->quit();
			break;
		//���콺 �Է�
		case SDL_MOUSEMOTION:
			onMouseMove(event);
			break;
		case SDL_MOUSEBUTTONDOWN:
			onMouseButtonDown(event);
			break;
		case SDL_MOUSEBUTTONUP:
			onMouseButtonUp(event);
			break;
		//Ű���� �Է�
		case SDL_KEYDOWN:
			onKeyDown();
			break;
		case SDL_KEYUP:
			onKeyUp();
			break;
		default:
			break;
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
//Mouse Input
bool InputHandler::getMouseButtonState(int buttonNumber)
{
	return m_mouseButtonStates[buttonNumber];
}
Vector2D* InputHandler::getMousePosition() //������ push, pop
{
	return m_mousePosition;
}
void InputHandler::onMouseMove(SDL_Event event)
{
	m_mousePosition->setX(event.motion.x);
	m_mousePosition->setY(event.motion.y);
}

void InputHandler::onMouseButtonDown(SDL_Event event)
{
	if (event.button.button == SDL_BUTTON_LEFT) {
		m_mouseButtonStates[LEFT] = true;
	}
	if (event.button.button == SDL_BUTTON_MIDDLE) {
		m_mouseButtonStates[MIDDLE] = true;
	}
	if (event.button.button == SDL_BUTTON_RIGHT) {
		m_mouseButtonStates[RIGHT] = true;
	}
}//

void InputHandler::onMouseButtonUp(SDL_Event event)
{
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

void InputHandler::onKeyDown()
{
	m_keystates = SDL_GetKeyboardState(0);
}

void InputHandler::onKeyUp()
{
	m_keystates = SDL_GetKeyboardState(0);
}
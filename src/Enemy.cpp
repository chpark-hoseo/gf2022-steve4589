#include <Enemy.h>
#include <InputHandler.h>

Enemy::Enemy(const LoaderParams* pParams) : SDLGameObject(pParams) {}

void Enemy::draw()
{
	SDLGameObject::draw();
}
void Enemy::update()
{
	m_currentFrame = ((SDL_GetTicks() / 100) % 6);
	m_acceleration.setX(1);
	SDLGameObject::update();

	if (TheInputHandler::Instance()->getMouseButtonState(LEFT)) { printf("shoot \n"); }
	Vector2D* vec = TheInputHandler::Instance()->getMousePosition();
	m_velocity = (*vec - m_position) / 100;
	//player의 update 함수 참고 
}
void Enemy::clean() {}

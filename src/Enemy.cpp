#include <Enemy.h>
#include <iostream>

Enemy::Enemy(const LoaderParams* pParams) : SDLGameObject(pParams) {}

void Enemy::draw()
{
	SDLGameObject::draw();
}
void Enemy::update()
{
}
void Enemy::clean() {}

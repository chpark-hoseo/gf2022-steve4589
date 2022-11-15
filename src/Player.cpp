#include <Player.h>

Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams) {}

void Player::draw()
{
	SDLGameObject::draw();
}
void Player::update()
{
}
void Player::clean() {}

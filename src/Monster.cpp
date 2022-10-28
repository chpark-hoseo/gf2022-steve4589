#include <Monster.h>
#include <Game.h>
#include <iostream>

void Monster::load(int x, int y, int width, int height, std::string textureID)
{
    GameObject::load(x, y, width, height, textureID);
}

void Monster::draw(SDL_Renderer* pRenderer)
{
    GameObject::draw(pRenderer);
}
void Monster::update()
{
    move();
}
void Monster::move()
{
    speed = m_x < 1000 ? speed : -speed;
    speed = m_x > 0 ? speed : -speed;

    m_x += speed;
    std::cout << speed;
}


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
    if (m_x < 10) speed = 0;
    m_x += speed;
    std::cout << speed;
}


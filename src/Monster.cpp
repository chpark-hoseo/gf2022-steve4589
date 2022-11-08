#include <Monster.h>
#include <iostream>

void Monster::load(float x, float y, int width, int height, std::string textureID)
{
    GameObject::load(x, y, width, height, textureID);
}

void Monster::draw(SDL_Renderer* pRenderer)
{
    GameObject::draw(pRenderer);
}

void Monster::MungMungSlide()
{
    m_x += 1;
    m_y += 1;
}

void Monster::MungMungSwim()
{
    m_y += sin((float)(3.141592f * 2 / 240) * count);
    m_x += cos((float)(3.141592f * 2 / 240) * count);
    count++;
}
void Monster::MungMungWave()
{
    m_y += sin((float)(3.141592f * 5 / 360) * count);
    count++;
    m_x += 1;
}
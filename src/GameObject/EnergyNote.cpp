#include <EnergyNote.h>

void EnergyNote::load(int x, int y, int width, int height, int currentRow, int currentFrame, std::string textureID)
{
    GameObject::load(x, y, width, height, currentRow, currentFrame, textureID);
}
void EnergyNote::draw(SDL_Renderer* pRenderer)
{
    GameObject::draw(pRenderer);
}
void EnergyNote::update() 
{
    //EnergyNote::move();
    //EnergyNote::crashEvent();
}

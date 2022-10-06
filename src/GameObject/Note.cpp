#include <Note.h>

void Note::load(int x, int y, int width, int height, int currentRow, int currentFrame, std::string textureID)
{
	GameObject::load(x, y, width, height, currentRow, currentFrame, textureID); //base코드 
}
void Note::draw(SDL_Renderer* pRenderer)
{
	//GameObject::draw(pRenderer);
}
void Note::update() //아래로 
{
	move();
}
void Note::clean() {}

void Note::move()
{
	//m_y += 5;
}
void Note::crashEvent()
{

}

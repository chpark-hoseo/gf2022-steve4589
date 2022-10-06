#include <GameObject.h>
#include <TextureManager.h>
#include <Game.h>

void GameObject::load(int x, int y, int width, int height, int currentRow, int currentFrame, std::string textureID)
{
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
	m_textureID = textureID;
	m_currentRow = currentRow;
	m_currentFrame = currentFrame;
}
void GameObject::draw(SDL_Renderer* pRenderer) //���� ������Ʈ �ϳ��ϳ� ���������� draw�� �ʿ��ϸ� ��� �� �̸� ���� 
{
	TextureManager::GetInstance()->drawFrame(m_textureID, m_x, m_y, m_width, m_height, m_currentRow, m_currentFrame, Game::GetInstance()->getRenderer());
}
void GameObject::update()
{
	//m_x += 1;
}
void GameObject::clean() {}
#include <GameObject.h>
#include <SDL2/SDL.h>

void GameObject::load(float x, float y, int width, int height, std::string textureID)
{
    m_x = x;
    m_y = y;
    m_width = width;
    m_height = height;
    m_textureID = textureID;
    m_currentRow = 0;
    m_currentFrame = 0;
}
void GameObject::draw(SDL_Renderer* pRenderer)
{
    TextureManager::GetInstance()
        ->drawFrame(m_textureID,
            m_x, m_y,
            m_width, m_height,
            m_currentRow,
            m_currentFrame,
            pRenderer);
}

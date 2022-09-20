#include "Game.h"

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	//Textture 생성
	SDL_Surface* pTempSurface = SDL_LoadBMP("assets/rider.bmp");
	m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
	SDL_FreeSurface(pTempSurface);
	//원본 상자 너비/높이 설정
	SDL_QueryTexture(m_pTexture, NULL, NULL, &m_sourceRectangle.w, &m_sourceRectangle.h);
	//SDL_QueryTexture(SDL_Texture textur, Uint32* format, int* access, int* x, int* y)
	//format -> 해당 format으로 칠할건지 / access -> 대상 텍스쳐를 아예 칠할건지?

	m_destinationRectangle.w = m_sourceRectangle.w;
	m_destinationRectangle.h = m_sourceRectangle.h;

	m_destinationRectangle.x = m_sourceRectangle.x = 0;
	m_destinationRectangle.y = m_sourceRectangle.y = 0;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		m_pWindow = SDL_CreateWindow(
			title, xpos, ypos, width, height, flags);
		if (m_pWindow != 0) {
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

			if (m_pRenderer != 0) {
				SDL_SetRenderDrawColor(
					m_pRenderer, 255, 255, 255, 255);
			}
			else {
				return false; // 랜더러 생성 실패
			}
		}
		else {
			return false; // 윈도우 생성 실패 
		}
	}
	else {
		return false; // SDL 초기화 실패
	}

	m_bRunning = true;
	return true;
}
void Game::update() {}
void Game::render()
{
	SDL_RenderClear(m_pRenderer);
	SDL_RenderPresent(m_pRenderer);

	SDL_RenderCopy(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle); //텍스쳐에 설정한 사진 올리기 
}
bool Game::running()
{
	return m_bRunning;
}
void Game::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) //작동중 이벤트를 계속 인식하기 위해서라고 생각합니다,  
	{                             //사실 이미 main의 while내에서 작동하기 때문에 여기서 반복할 필요는 없다고 생각되지만, 
		switch (event.type)       //그래도 추측한다면 입력에 더 빨리 반응할 수 있을것 같다고 생각합니다
		{
		case SDL_MOUSEBUTTONDOWN:
			m_bRunning = false;
			break;
		default:
			break;
		}
	}
}
void Game::clean()
{
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}

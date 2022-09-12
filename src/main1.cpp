#include <SDL2/SDL.h>
#include <stdio.h>

SDL_Window* g_pWindow = 0;
SDL_Renderer* g_pRenderer = 0;

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) // SDL_INIT_EVERYTHING --> 모든 하위 시스템 
	{
		g_pWindow = SDL_CreateWindow("Game FrameWork", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_SHOWN);//추가 실습 
		//SDL_WINDOW* SDL_CreateWindow(const Char* title, int x, int y, int w, int y, Uint32 flags);

		if (g_pWindow != 0)
		{
			g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);//?뚮뜑???앹꽦 
			//void SDL_DestroyRenderer(SDL_Renderer * renderer); ?대쫫??Destroy --> ?�遺�遺??댁젣?쒕떎?붾쑜 
		}
	}
	else
	{
		return 1;
	}

	SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 0, 255); //렌데러 색상 값 설정 
	SDL_RenderClear(g_pRenderer); // 화면을 SDL_SetRenderDrawColor값을 토대로 바꿔줌 
	SDL_RenderPresent(g_pRenderer);// 설정한 값을 토대로 계속 업데이트

	SDL_Delay(5000); //5초간 딜레이
	//SDL_GetTicks --> SDL이 시작하고 지금까지 얼마나 됐는지 시간 표시 
	SDL_Quit(); //끝낼때 무조건 적기 

	return 0;
}
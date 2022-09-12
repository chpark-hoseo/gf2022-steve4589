#include <SDL2/SDL.h>
#include <stdio.h>

SDL_Window* g_pWindow = 0;
SDL_Renderer* g_pRenderer = 0;

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) // SDL_INIT_EVERYTHING --> 모든 ?�위?�스??
	{
		g_pWindow = SDL_CreateWindow("Setting up SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);//?�면 ?�성 
		//SDL_WINDOW* SDL_CreateWindow(const Char* title, int x, int y, int w, int y, Uint32 flags);

		if (g_pWindow != 0)
		{
			g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);//?�더???�성 
			//void SDL_DestroyRenderer(SDL_Renderer * renderer); ?�름??Destroy --> ?�부�??�제?�다?�뜻 
		}
	}
	else
	{
		return 1;
	}

	SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 0, 255); //?�도???�상??지?�하???�수
	SDL_RenderClear(g_pRenderer); // ?�면??지?�는 ?�수, SDL_SetRenderDrawColor???�향??받으므�??�당 ?�수가 지?�한 ?�으�?지?�짐 
	SDL_RenderPresent(g_pRenderer);// ?�스쳐�? ?�더�????�태�?계속 ?�데?�트 ?�켜�?

	SDL_Delay(5000); //5�??�안 ?�리 Sleep();?� 기능 비슷 
	//SDL_GetTicks --> SDL??구동?�고 ?�마???�간(ms)???��??��? 보여�?
	SDL_Quit(); //모든 ?�브 ?�스?�이 ?�난??무조�?종료?�야??

	return 0;
}
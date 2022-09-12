#include <SDL2/SDL.h>
#include <stdio.h>

SDL_Window* g_pWindow = 0;
SDL_Renderer* g_pRenderer = 0;

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) // SDL_INIT_EVERYTHING --> ��� ���� �ý��� 
	{
		g_pWindow = SDL_CreateWindow("Game FrameWork", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_SHOWN);//�߰� �ǽ� 
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

	SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 0, 255); //������ ���� �� ���� 
	SDL_RenderClear(g_pRenderer); // ȭ���� SDL_SetRenderDrawColor���� ���� �ٲ��� 
	SDL_RenderPresent(g_pRenderer);// ������ ���� ���� ��� ������Ʈ

	SDL_Delay(5000); //5�ʰ� ������
	//SDL_GetTicks --> SDL�� �����ϰ� ���ݱ��� �󸶳� �ƴ��� �ð� ǥ�� 
	SDL_Quit(); //������ ������ ���� 

	return 0;
}
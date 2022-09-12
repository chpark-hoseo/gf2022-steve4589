#include <SDL2/SDL.h>
#include <stdio.h>

SDL_Window* g_pWindow = 0;
SDL_Renderer* g_pRenderer = 0;

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) // SDL_INIT_EVERYTHING --> λͺ¨λ  ?μ?μ€??
	{
		g_pWindow = SDL_CreateWindow("Setting up SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);//?λ©΄ ?μ± 
		//SDL_WINDOW* SDL_CreateWindow(const Char* title, int x, int y, int w, int y, Uint32 flags);

		if (g_pWindow != 0)
		{
			g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);//?λ???μ± 
			//void SDL_DestroyRenderer(SDL_Renderer * renderer); ?΄λ¦??Destroy --> ?λΆλΆ??΄μ ?λ€?λ» 
		}
	}
	else
	{
		return 1;
	}

	SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 0, 255); //?λ???μ??μ§?ν???¨μ
	SDL_RenderClear(g_pRenderer); // ?λ©΄??μ§?°λ ?¨μ, SDL_SetRenderDrawColor???ν₯??λ°μΌλ―λ‘??΄λΉ ?¨μκ° μ§?ν ?μΌλ‘?μ§?μ§ 
	SDL_RenderPresent(g_pRenderer);// ?μ€μ³κ? ?λλ§????νλ‘?κ³μ ?λ°?΄νΈ ?μΌμ€?

	SDL_Delay(5000); //5μ΄??μ ?λ¦¬ Sleep();? κΈ°λ₯ λΉμ· 
	//SDL_GetTicks --> SDL??κ΅¬λ?κ³  ?Όλ§???κ°(ms)???λ??μ? λ³΄μ¬μ€?
	SDL_Quit(); //λͺ¨λ  ?λΈ ?μ€?μ΄ ?λ??λ¬΄μ‘°κ±?μ’λ£?΄μΌ??

	return 0;
}
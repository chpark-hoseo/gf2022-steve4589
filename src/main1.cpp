#include <SDL2/SDL.h>
#include <stdio.h>

SDL_Window* g_pWindow = 0;
SDL_Renderer* g_pRenderer = 0;

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) // SDL_INIT_EVERYTHING --> ¸ğµç ÇÏÀ§ ½Ã½ºÅÛ 
	{
		g_pWindow = SDL_CreateWindow("Game FrameWork", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_SHOWN);//Ãß°¡ ½Ç½À 
		//SDL_WINDOW* SDL_CreateWindow(const Char* title, int x, int y, int w, int y, Uint32 flags);

		if (g_pWindow != 0)
		{
			g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);//?Œë”???ì„± 
			//void SDL_DestroyRenderer(SDL_Renderer * renderer); ?´ë¦„??Destroy --> ?€ë¶€ë¶??´ì œ?œë‹¤?”ëœ» 
		}
	}
	else
	{
		return 1;
	}

	SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 0, 255); //·»µ¥·¯ »ö»ó °ª ¼³Á¤ 
	SDL_RenderClear(g_pRenderer); // È­¸éÀ» SDL_SetRenderDrawColor°ªÀ» Åä´ë·Î ¹Ù²ãÁÜ 
	SDL_RenderPresent(g_pRenderer);// ¼³Á¤ÇÑ °ªÀ» Åä´ë·Î °è¼Ó ¾÷µ¥ÀÌÆ®

	SDL_Delay(5000); //5ÃÊ°£ µô·¹ÀÌ
	//SDL_GetTicks --> SDLÀÌ ½ÃÀÛÇÏ°í Áö±İ±îÁö ¾ó¸¶³ª µÆ´ÂÁö ½Ã°£ Ç¥½Ã 
	SDL_Quit(); //³¡³¾¶§ ¹«Á¶°Ç Àû±â 

	return 0;
}
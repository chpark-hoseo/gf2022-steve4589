#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

/*
SDL_Window*		g_pWindow = 0;
SDL_Renderer*	g_pRenderer = 0;

SDL_Texture*	g_pTexureImage;
SDL_Rect		g_RectImage;

SDL_Texture*	g_pTexureText;
SDL_Rect 		g_RectText;

TTF_Font*		g_pFont;
Mix_Chunk*		g_pChunk;

bool			g_bRunning = false;
bool			g_bLeftMousePressed = false;

bool init();
void handleInput();
void update();
void render();

if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		g_pWindow = SDL_CreateWindow("Unrealnity", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 900, SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE); //과제 2. 윈도우 생성 다르게 해보기
		//화면 비율 1920, 900, 화면 크기를 최대로, 화면 사이즈를 조절할 수 있게
		if (g_pWindow != 0)
		{
			g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);//)(window* window, int index, Uint32 flags)
			//Renderer flags 모음
			// 0 --> 없음
			//SDL_RENDERER_SOFTWARE ->
			//SDL_RENDERER_ACCELERATED -> 하드웨어를 빠르게 가속 -> 빨리 보여줌
			//SDL_RENDERER_PRESENTVSYNC -> 프레임 속도에 맞춰서 (대부분 1초에 60번)
			//SDL_RENDERER_TARGETTEXTURE -> 텍스쳐 렌더링
		}
	}
	else
	{
		return 1;
	}

	SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 255, 255); //과제1. 화면 파란색으로 바꾸기   (r, g, b, a)
	SDL_RenderClear(g_pRenderer);
	SDL_RenderPresent(g_pRenderer);

	SDL_Delay(10000); //과제3. 10초뒤 프로그램 종료하기
	SDL_Quit();

int main(int argc, char* argv[])
{
	if (!init())
	{
		return 1; // something's wrong
	}

	g_bRunning = true;

	while (g_bRunning)
	{
		handleInput();
		update();
		render();
	}

	Mix_CloseAudio();
	Mix_Quit();
	TTF_CloseFont(g_pFont);
	TTF_Quit();
	SDL_Quit();

	return 0;
}

bool init()
{
	SDL_Surface* pTempSurface;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		SDL_Log("SDL_Init Error: %s\n", SDL_GetError());
		return false;
	}

	g_pWindow = SDL_CreateWindow("HoseoSDL.2022",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		640, 480, SDL_WINDOW_SHOWN);
	if (g_pWindow == NULL)
	{
		SDL_Log("SDL_CreateWindow Error: %s\n", SDL_GetError());
		return false;
	}

	g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);
	if (g_pRenderer == NULL)
	{
		SDL_Log("SDL_CreateRenderer Error: %s\n", SDL_GetError());
		return false;
	}
	else
	{
		// SDL Image
		pTempSurface = IMG_Load("./assets/animate-alpha.png");
		if (pTempSurface == NULL)
		{
			SDL_Log("IMG_Load Error: %s\n", IMG_GetError());
			return false;
		}
		else
		{
			g_pTexureImage = SDL_CreateTextureFromSurface(g_pRenderer, pTempSurface);
			g_RectImage = { 0, 0, 128, 82 };
			SDL_FreeSurface(pTempSurface);
		}
	}

	// SDL TTF
	if (TTF_Init() < 0)
	{
		SDL_Log("TTF_Init Error: %s\n", TTF_GetError());
		return false;
	}
	else
	{
		g_pFont = TTF_OpenFont("./assets/NanumGothic.ttf", 20);
		if (g_pFont == NULL)
		{
			SDL_Log("TTF_OpenFont Error: %s\n", TTF_GetError());
			return false;
		}
		else
		{
			// SDL TTF
#ifdef UNICODE
			pTempSurface = TTF_RenderUNICODE_Shaded(g_pFont, (Uint16*)L"한글 텍스쳐", //TTF_RenderUNICODE_Shaded(TTF_Font* gFont, Uint16* texture, SDL_Color* 꺼진 상태표현?, SDL_Color* 켜진상태 표현?)
				SDL_Color{ 0, 0, 255 }, SDL_Color{ 255, 255, 255 });
#else
			pTempSurface = TTF_RenderUTF8_Shaded(g_pFont, "한글 텍스쳐",
				SDL_Color{ 0, 0, 255 }, SDL_Color{ 255, 255, 255 });
#endif
			if (pTempSurface == NULL)
			{
				SDL_Log("TTF_Render Error: %s\n", TTF_GetError());
				return false;
			}
			else
			{
				g_pTexureText = SDL_CreateTextureFromSurface(g_pRenderer, pTempSurface);
				g_RectText = { 0, 0, pTempSurface->w, pTempSurface->h };
				SDL_FreeSurface(pTempSurface);
			}
		}

	}

	// SDL Mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		SDL_Log("Mix_OpenAudio Error: %s\n", Mix_GetError());
		return false;
	}
	else
	{
		g_pChunk = Mix_LoadWAV("./assets/jump.wav");
		if (g_pChunk == NULL)
		{
			SDL_Log("Mix_LoadWAV Error : %s\n", Mix_GetError());
			return false;
		}
		else
		{
			Mix_Volume(-1, 128);
		}
	}

	return true;
}

void handleInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_bRunning = false;
			break;

		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				g_bLeftMousePressed = true;
			}
			break;

		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				g_bLeftMousePressed = false;
			}
			break;

		}
	}
}

void update()
{
	if (g_bLeftMousePressed)
	{
		// chunk에 담긴 사운드 재생, -1은 가장 가까운 채널, 0은 반복 횟수
		Mix_PlayChannel(-1, g_pChunk, 0);
		printf("왼쪽클릭 눌림 - 사운드 재생\n");
	}
}

void render()
{
	SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 0, 255);
	SDL_RenderClear(g_pRenderer);

	SDL_RenderCopy(g_pRenderer, g_pTexureImage, &g_RectImage, &g_RectImage);
	SDL_RenderCopy(g_pRenderer, g_pTexureText, &g_RectText, &g_RectText);
	filledCircleColor(g_pRenderer, 300, 300, 50, 0xFFFF0000);

	SDL_RenderPresent(g_pRenderer);
}*/
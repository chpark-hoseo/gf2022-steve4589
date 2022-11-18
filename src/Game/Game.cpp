#pragma once
#include <SDLGameObject.h>
#include <Game.h>
#include <GameState.h>

Game* Game::s_pInstance = 0;

//----------------------------------------------------------------------------
//MainCode
bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		m_pWindow = SDL_CreateWindow(
			title, xpos, ypos, width, height, flags);
		//SDL_SetWindowFullscreen(m_pWindow, SDL_WINDOW_FULLSCREEN);
		if (m_pWindow != 0) {
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if (m_pRenderer != 0) {
				//Start_initialize();
				SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 0, 0);
			}
			else {
				return false; // ������ ���� ����
			}
		}
		else {
			return false; // ������ ���� ���� 
		}
	}
	else {
		return false; // SDL �ʱ�ȭ ����
	}
	m_bRunning = true;

	// SDL TTF
	if (TTF_Init() < 0)
	{
		SDL_Log("TTF_Init Error: %s\n", TTF_GetError());
		return false;
	}
	else
	{
		g_pFont = TTF_OpenFont("./assets/Font/small_pixel.ttf", 25); //font, fontSize
		if (g_pFont == NULL)
		{
			SDL_Log("TTF_OpenFont Error: %s\n", TTF_GetError());
			return false;
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
		g_pChunk = Mix_LoadWAV("./assets/BFX/Stage1.mp3");
		Mix_PlayChannel(-1, g_pChunk, 0);
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
void Game::clean()
{
	// cleanup the all states
	while (!m_gameStates.empty()) {
		m_gameStates.back()->clean();
		m_gameStates.pop_back();
	}

	//�ڵ����� ������ �ʱ� ������
	//Ǯ��ũ���϶� ���� ���� ������

	// shutdown SDL
	Mix_CloseAudio();
	Mix_Quit();
	TTF_CloseFont(g_pFont);
	TTF_Quit();
	SDL_Quit();
}

void Game::ChangeState(GameState* state)
{
	// cleanup the current state
	if (!m_gameStates.empty()) {
		m_gameStates.back()->clean();
		m_gameStates.pop_back();
	}
	// store and init the new state
	m_gameStates.push_back(state);
	m_gameStates.back()->Awake();
}

void Game::PushState(GameState* state)
{
	// store and init the new state
	m_gameStates.push_back(state);
	m_gameStates.back()->Awake();
}

void Game::PopState()
{
	// cleanup the current state
	if (!m_gameStates.empty()) {
		m_gameStates.back()->clean();
		m_gameStates.pop_back();
	}
}

void Game::handleEvents()
{
	m_gameStates.back()->handleEvents(this);
}

void Game::update()
{
	m_gameStates.back()->update(this);
}

void Game::render()
{
	m_gameStates.back()->render(this);
}
bool Game::running()
{
	return m_bRunning;
}
//��Ʈ ::
// //SDL_WINDOWPOS_CENTERED --> 
/*
SDL_WINDOW_FULLSCREEN   ��üȭ�� â
SDL_WINDOW_FULLSCREEN_DESKTOP   ����ũž �ػ��� ��ü ȭ�� â
SDL_WINDOW_OPENGL   OpenGL ���ؽ�Ʈ�� ��밡���� â
SDL_WINDOW_VULKAN   Vulkan �� �Բ� ��� ������ â
SDL_WINDOW_HIDDEN   ������ �ʴ� â
SDL_WINDOW_BORDERLESS   ���ڷ��̼��� ���� â
SDL_WINDOW_RESIZABLE   ũ�⸦ ���� ����
SDL_WINDOW_MINIMIZED   �ּ�ȭ â
SDL_WINDOW_MAXIMIZED   �ִ�ȭ â
SDL_WINDOW_INPUT_GRABBED   �Է� ��Ŀ���� ����
SDL_WINDOW_ALLOW_HIGHDPI   �����Ǵ� ��� ���� DPI ��忡�� â (>= SDL 2.0.1)

//SDL_GetTicks --> SDL�� �����ϰ� ���ݱ��� �󸶳� �ƴ��� �ð� ǥ��
//void SDL_DestroyRenderer(SDL_Renderer * renderer); Destroy --> ��κ� �����Ѵٴ� ��
//SDL_WINDOW* SDL_CreateWindow(const Char* title, int x, int y, int w, int y, Uint32 flags);
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
		g_pWindow = SDL_CreateWindow("Unrealnity", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 900, SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE); //���� 2. ������ ���� �ٸ��� �غ���
		//ȭ�� ���� 1920, 900, ȭ�� ũ�⸦ �ִ��, ȭ�� ����� ������ �� �ְ�
		if (g_pWindow != 0)
		{
			g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);//)(window* window, int index, Uint32 flags)
			//Renderer flags ����
			// 0 --> ����
			//SDL_RENDERER_SOFTWARE ->
			//SDL_RENDERER_ACCELERATED -> �ϵ��� ������ ���� -> ���� ������
			//SDL_RENDERER_PRESENTVSYNC -> ������ �ӵ��� ���缭 (��κ� 1�ʿ� 60��)
			//SDL_RENDERER_TARGETTEXTURE -> �ؽ��� ������
		}
	}
	else
	{
		return 1;
	}

	SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 255, 255); //����1. ȭ�� �Ķ������� �ٲٱ�   (r, g, b, a)
	SDL_RenderClear(g_pRenderer);
	SDL_RenderPresent(g_pRenderer);

	SDL_Delay(10000); //����3. 10�ʵ� ���α׷� �����ϱ�
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
			pTempSurface = TTF_RenderUNICODE_Shaded(g_pFont, (Uint16*)L"�ѱ� �ؽ���", //TTF_RenderUNICODE_Shaded(TTF_Font* gFont, Uint16* texture, SDL_Color* ���� ����ǥ��?, SDL_Color* �������� ǥ��?)
				SDL_Color{ 0, 0, 255 }, SDL_Color{ 255, 255, 255 });
#else
			pTempSurface = TTF_RenderUTF8_Shaded(g_pFont, "�ѱ� �ؽ���",
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
		// chunk�� ��� ���� ���, -1�� ���� ����� ä��, 0�� �ݺ� Ƚ��
		Mix_PlayChannel(-1, g_pChunk, 0);
		printf("����Ŭ�� ���� - ���� ���\n");
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
}
/*
void Game::DhrowBorder()
{
	SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
	//SDL_RenderClear(m_pRenderer);

	SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 }; //x, y, w, h
	SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255);
	SDL_RenderFillRect(m_pRenderer, &fillRect); //���� ���� �簢��

	SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
	SDL_SetRenderDrawColor(m_pRenderer, 0, 255, 0, 255);
	SDL_RenderDrawRect(m_pRenderer, &outlineRect); //���� �� �簢��

	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 255, 255);
	SDL_RenderDrawLine(m_pRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2); //��

	SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 0, 255);
	for (int i = 0; i < SCREEN_HEIGHT; i += 4)
	{
		SDL_RenderDrawPoint(m_pRenderer, SCREEN_WIDTH / 2, i); //����
	}
}
*/

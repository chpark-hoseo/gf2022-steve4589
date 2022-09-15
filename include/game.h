#include "SDL2/SDL.h"

class Game
{
public:
	Game() { }
	~Game() { }

	bool init(/* 수정 필요 */);
	void render();
	void update();
	bool running();
	void handleEvents();
	void clean();

private:
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	bool m_bRunning;
};
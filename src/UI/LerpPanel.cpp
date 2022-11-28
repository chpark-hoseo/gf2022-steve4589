#include <LerpPanel.h>
#include <CustomPhysics.h>
#include <TextureManager.h>
#include <Game.h>

LerpPanel::LerpPanel(const LoaderParams* pParams, float getFadeOutTime, float getFadeInTime) : SDLGameObject(pParams), fadeOutTime(getFadeOutTime), fadeInTime(getFadeInTime)
{ 
	LerpTextureLoad();
	tag = "FadeOut";
	timer.WaitTime();

	SetActive(true);
}
void LerpPanel::draw()
{
	if (!onOff) return;
	drawImg();
}

void LerpPanel::update()
{
	if (!onOff) return;
	if (lerp.m_handle.done() == false) { lerp.m_handle.resume(); }
}

void LerpPanel::LerpTextureLoad()
{
	string set_fileName = "Assets/need for A+_fadePanel.png"; //������ ���������� �����ϹǷ� 
	SDL_Surface* pTempSurface = IMG_Load(set_fileName.c_str());

	texture = SDL_CreateTextureFromSurface(Game::GetInstance()->getRenderer(), pTempSurface);

	SDL_FreeSurface(pTempSurface);
}

void LerpPanel::drawImg()
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	SDL_SetTextureAlphaMod(texture, (Uint32)alpha);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

	srcRect.w = 2000;
	srcRect.h = 2000;

	destRect.w = srcRect.w;
	destRect.h = srcRect.h;

	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = srcRect.x;
	destRect.y = srcRect.y;

	SDL_RenderCopyEx(Game::GetInstance()->getRenderer(), texture, &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}
#pragma once
#include <SDLGameObject.h>
#include <SDL2/SDL_mixer.h>

/*template <class T>*/
class SoundEffect : public SDLGameObject //SFX�� �� ���� ������Ʈ���� ȣ���մϴ� (��ø�ؼ� ������ �ϱ� ����)
{
public:
	explicit SoundEffect(const LoaderParams* pParams);
	virtual void draw() {}
	virtual void update() {}
	virtual void clean() {}
	void SoundSFX(string soundName)
	{
		string songData = "./assets/SFX/" + soundName + ".wav";
		const char* SongdataPath = songData.c_str();

		soundEffect = Mix_LoadWAV(SongdataPath);
		if (soundEffect == NULL)
		{
			SDL_Log("SFX is NULL, need initialized SFX, use SoundSFX();  : %s\n", Mix_GetError());
			return;
		}

		Uint32 length = soundEffect->alen; //wav ���� ����
		
		Mix_PlayChannel(-1, soundEffect, 0);
		SetActive(false); //�ٷ� ��Ȱ��ȭ �մϴ�
	}
private:
	virtual void OnDisable();

	Mix_Chunk* soundEffect;
};

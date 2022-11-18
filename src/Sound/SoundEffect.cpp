#include <SoundEffect.h>
#include <State_Play.h>

SoundEffect::SoundEffect(const LoaderParams* pParams) : SDLGameObject(pParams) { tag = "SoundEffect"; }

void SoundEffect::OnDisable()
{
	State_Play::GetInstance()->ReturnPool("SoundEffect", this);
}

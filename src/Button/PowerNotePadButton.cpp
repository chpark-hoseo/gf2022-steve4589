#include <PowerNotePadButton.h>
#include <State_Play.h>
#include <ScoreManager.h>
#include <SoundEffect.h>

void PowerNotePadButton::PressInAct()
{
	int detectNum = 0;
	for (PowerNotePad* powerNotePad : powerNotePads)
	{
		powerNotePad->PressInAct();
		if (powerNotePad->OffNote() == true) { detectNum++; }
	}

	SoundEffect* SFX = dynamic_cast<SoundEffect*>(State_Play::GetInstance()->GetObject(Vector2D(0, 0), "SoundEffect"));
	if (detectNum == 0)
	{
		SFX->SoundSFX("miss");
		State_Play::GetInstance()->GetObject(playerPos, "PlayerMiss");
		State_Play::GetInstance()->DamagedEnergy(17);
		ScoreManager::GetInstance()->MinusScore();
	}
	else 
	{
		SFX->SoundSFX("pop");
		ScoreManager::GetInstance()->AddScore(); 
	}
}
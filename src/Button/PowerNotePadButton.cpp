#include <PowerNotePadButton.h>
#include <State_Play.h>

void PowerNotePadButton::PressInAct()
{
	int detectNum = 0;
	for (PowerNotePad* powerNotePad : powerNotePads)
	{
		powerNotePad->PressInAct();
		if (powerNotePad->OffNote() == true) detectNum++;
	}
	if (detectNum == 0)
	{
		//����Ʈ �߰� �ʿ�
		State_Play::GetInstance()->GetObject(playerPos, "PlayerMiss");
		State_Play::GetInstance()->DamagedEnergy(17);
	}
}
#include <BackScroll.h>
#include <Game.h>

BackScroll::BackScroll(const LoaderParams* pParams, SDLGameObject* backFrame, SDLGameObject* backFrame1, SDLGameObject* backFrame2) : SDLGameObject(pParams)
{
	middle = backFrame->getWidth() / static_cast<float>(3) * -2;

	backFrame->SetPosition(Vector2D(middle, 340));
	backFrame1->SetPosition(Vector2D(middle, 420));
	backFrame2->SetPosition(Vector2D(middle, 300));

	backs.emplace_back(backFrame);
	backs.emplace_back(backFrame1);
	backs.emplace_back(backFrame2);
}

void BackScroll::Scroll()
{
	for (int i = 0; i < backs.size(); i++)
	{
		Vector2D MovePos = backs[i]->GetPosition();
		MovePos.setX(MovePos.getX() + speed[i]);

		if (MovePos.getX() > 0)
		{
			MovePos.setX(middle);
		}
		backs[i]->SetPosition(MovePos);
	}
}
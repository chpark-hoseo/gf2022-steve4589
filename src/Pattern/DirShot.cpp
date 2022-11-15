#include <DirShot.h>
#include <SDLGameObject.h>
#include <State_Play.h>

void DirShot::dirShot(float speed, Vector2D originPos, Vector2D disPos, const char * getTag)
{
	dirShotAct();

	GameObject* gameObject = State_Play::GetInstance()->GetObject(originPos, getTag);

	Vector2D shotPos = gameObject->GetPosition();

	float x = disPos.getX() - shotPos.getX();
	float y = disPos.getY() - shotPos.getY();

	Vector2D setDirVec = Vector2D(x, y);
	setDirVec.normalize();

	gameObject->SetSpeed(speed);
	gameObject->SetDirVec(setDirVec);
}
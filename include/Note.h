#pragma once

class SDLGameObject; //SDLGameObject 정상 영업합니다 
class Alive_SDLGameObject
{
	SDLGameObject * sdlGameObj; 
};
class Note : public SDLGameObject, public INoteType
{
public:
	Note(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();

	Vector2D startPos() override;
	void move() override;
	void crashEvent() override;

	void OnEnable() override;
private:
	Type noteType = Left;
};

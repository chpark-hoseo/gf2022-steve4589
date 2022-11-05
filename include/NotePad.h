#pragma once
#include <Collider2D.h>
#include <cstdarg>

class NotePad : public SDLGameObject, public ICLICK
{
private:
	bool isPressIn = true;
	bool isPressOut = false;

	std::string getTag;

	Collider2D collision = Collider2D(m_position.getX(), m_position.getY(), m_width, m_height);
	GameObject* EntergameObject;
	vector<NotePad*> otherPads; //PowerNotePad

	Vector2D playerPos = Vector2D(635.5f, 750);

	void OffNote();
public:
	NotePad(const LoaderParams* pParams, string thisTag, string noteTag);
	virtual void draw() { SDLGameObject::draw(); }
	virtual void update();
	virtual void clean() {}

	void SetPosition(Vector2D getPos) override;
	void DetectCollider();

	void PressIn(bool);
	void PressOut(bool);
	void IsPressed(bool _isPush) { PressIn(_isPush); }
};
#pragma once
#include <SDLGameObject.h>
#include <Collider2D.h>

//need for A+_notesPad
class NotePad : public SDLGameObject, public ICollision, public ICLICK
{
private:
	bool isPressIn = true;
	bool isPressOut = false;

	Collider2D collision = Collider2D(m_position.getX(), m_position.getY(), m_width, m_height);
	//SpecialNotesPad
public:
	NotePad(const LoaderParams* pParams);
	virtual void draw() { SDLGameObject::draw(); }
	virtual void update();
	virtual void clean() {}

	void SetPosition(Vector2D getPos) override;
	void UpdateCollider() override;

	//Interface
	void PressIn(bool);
	void PressOut(bool);
	void IsPressed(bool _isPush) { PressIn(_isPush); }
};
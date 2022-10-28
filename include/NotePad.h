#pragma once
#include <SDLGameObject.h>
#include <Collider2D.h>

//need for A+_notesPad
class NotePad : public SDLGameObject, public ICLICK
{
private:
	bool isPressIn = true;
	bool isPressOut = false;

	std::string getTag;

	Collider2D collision = Collider2D(m_position.getX(), m_position.getY(), m_width, m_height);

	GameObject* EntergameObject;

	void OffNote();
	//SpecialNotesPad
public:
	NotePad(const LoaderParams* pParams);
	virtual void draw() { SDLGameObject::draw(); }
	virtual void update();
	virtual void clean() {}

	void SetPosition(Vector2D getPos) override;
	void DetectCollider();

	//Interface
	void PressIn(bool);
	void PressOut(bool);
	void IsPressed(bool _isPush) { PressIn(_isPush); }
};
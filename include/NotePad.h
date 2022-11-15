#pragma once
#include <Collider2D.h>
#include <cstdarg>
#include <TemplateButton.h>
#include <DirShot.h>

class NotePad : public SDLGameObject, public TemplateButton, public DirShot
{
private:
	std::string getTag;

	Collider2D collision = Collider2D(m_position.getX(), m_position.getY(), m_width, m_height);
	GameObject* EntergameObject;

	Vector2D playerPos = Vector2D(635.5f, 750);

	void Shot(const char * objectName) { dirShot(3, m_position, Vector2D(1300, 50), objectName); }
	void OffNote();
public:
	NotePad(const LoaderParams* pParams, string thisTag, string noteTag);
	virtual void draw() { SDLGameObject::draw(); }
	virtual void update();
	virtual void clean() {}

	void SetPosition(Vector2D getPos) override;
	void DetectCollider();
	//이것도 따로 빼기
	virtual void IsPressed(bool isPress) { TemplateButton::IsPressed(isPress); }
	//TemplateButton
	virtual void PressInAct();
	virtual void PressOutAct();
};
#pragma once
#include <SDLGameObject.h>
#include <Collider2D.h>

class PowerNotePad : public SDLGameObject
{
private:
	std::string getTag;

	Collider2D collision = Collider2D(m_position.getX(), m_position.getY(), m_width, m_height);
	GameObject* EntergameObject;

	Vector2D playerPos = Vector2D(635.5f, 750);
public:
	PowerNotePad(const LoaderParams* pParams, string thisTag, string noteTag);
	virtual void draw() { SDLGameObject::draw(); }
	virtual void update();
	virtual void clean() {}

	void SetPosition(Vector2D getPos) override;
	void DetectCollider();

	bool OffNote();

	void PressInAct() { m_currentRow = 1; }
	void PressOutAct() { m_currentRow = 0; }
};
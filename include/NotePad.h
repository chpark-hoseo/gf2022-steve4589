#pragma once
#include <SDLGameObject.h>

//need for A+_notesPad
class NotePad : public SDLGameObject //public ICLICK
{
private:
	bool isOnce = false;
	//SpecialNotesPad
public:
	NotePad(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean() {}

	//Make it Interface
	void OncePushed()
	{
		if (isOnce)
		{
			std::cout << "�ѹ� ����", "\n";
			isOnce = false;
		}
	}
	void Pushed(bool isPush) { m_currentRow = isPush; }
	void test()
	{
		std::cout << "������ �ִ���" << "\n";
	}
	void Collision2D()
	{

	}
};
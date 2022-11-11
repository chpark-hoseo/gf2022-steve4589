#pragma once
#include <TemplateButton.h>
#include <PowerNotePad.h>
#include <stdarg.h>

class PowerNotePadButton : public TemplateButton
{
private:
	Vector2D playerPos = Vector2D(635.5f, 750);
	vector<PowerNotePad*> powerNotePads;
public:
	PowerNotePadButton(int num, PowerNotePad* getPad, ...)//getPad를 첫번째 인자로 삼고, 그 다음인자(...)부터 뽑아씀, ...은 반드시 가장 뒤에
	{
		va_list start; //가변인자들을 저장하는 포인터 역할, 뽑아쓸때마다 한칸씩(첫번째 인자의 자료형 만큼?) 뒤로 옮겨짐
		//getPad를 본보기 용으로 건네주기 => 인자 n개넣고 싶으면 구별용으로 1 + n개필요 
		va_start(start, getPad);//ap가 첫번째 인자를 가리키도록 getPad, va_list를 초기화하는 역할
		PowerNotePad* powerPad;
		for (int i = 0; i < num; i++)
		{
			powerPad = va_arg(start, PowerNotePad*);
			powerNotePads.emplace_back(powerPad);
		}
		va_end(start);
	}
	~PowerNotePadButton() { powerNotePads.clear(); }

	virtual void IsPressed(bool _isPush) { PressIn(_isPush); }
	//TemplateButton
	virtual void PressInAct();
	virtual void PressOutAct()
	{
		for (PowerNotePad* powerNotePad : powerNotePads)
		{
			powerNotePad->PressOutAct();
		}
	}
};

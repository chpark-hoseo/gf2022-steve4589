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
	explicit PowerNotePadButton(int num, PowerNotePad* getPad, ...)//getPad�� ù��° ���ڷ� ���, �� ��������(...)���� �̾ƾ�, ...�� �ݵ�� ���� �ڿ�
	{
		va_list start; //�������ڵ��� �����ϴ� ������ ����, �̾ƾ������� ��ĭ��(ù��° ������ �ڷ��� ��ŭ?) �ڷ� �Ű���
		//getPad�� ������ ������ �ǳ��ֱ� => ���� n���ְ� ������ ���������� 1 + n���ʿ� 
		va_start(start, getPad);//ap�� ù��° ���ڸ� ����Ű���� getPad, va_list�� �ʱ�ȭ�ϴ� ����
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

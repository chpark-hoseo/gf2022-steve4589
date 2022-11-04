#pragma once
#include <math.h>

class CustomPhysics
{
public :
	static CustomPhysics* GetInstance() //���̳��� �̱���. ���������� �ʱ�ȭ���� �����Ƿ�, �޸𸮸� Ȯ���� �� �ִ� 
	{
		if (s_pInstance == 0)
			s_pInstance = new CustomPhysics();
		return s_pInstance;
	}

	//��������, �� ���� ����
	//���⼭ ���� ���� ==> Material(�����̳� �׸��� ǥ��?)
	float Lerp(float A, float B, float Alpha)
	{
		//���⼭ Alpha�� ���� 0���� 1������ ��
		//A �� (B��A) * Alpha
		return A * (1 - Alpha) + B * Alpha;
	}
	//�߰� qarp (A, B, C, Alpha)=> �
	//cubic (A, B, C, D, Alpha)=> ������ (�����ĵ�, ����)
private :
		static CustomPhysics* s_pInstance; //���� ������� ����
};
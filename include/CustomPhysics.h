#pragma once
#include <math.h>

class CustomPhysics
{
public :
	static CustomPhysics* GetInstance() //다이나믹 싱글턴. 전역변수로 초기화하지 않으므로, 메모리를 확보할 수 있다 
	{
		if (s_pInstance == 0)
			s_pInstance = new CustomPhysics();
		return s_pInstance;
	}

	//선형보간, 두 값을 섞음
	//여기서 많이 쓰임 ==> Material(질감이나 그림자 표현?)
	float Lerp(float A, float B, float Alpha)
	{
		//여기서 Alpha의 값은 0에서 1까지의 값
		//A ＋ (B－A) * Alpha
		return A * (1 - Alpha) + B * Alpha;
	}
	//추가 qarp (A, B, C, Alpha)=> 곡선
	//cubic (A, B, C, D, Alpha)=> 지렁이 (사인파동, 진동)
private :
		static CustomPhysics* s_pInstance; //정적 멤버변수 선언
};
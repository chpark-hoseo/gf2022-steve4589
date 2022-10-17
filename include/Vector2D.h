#pragma once
#include <math.h> 

class Vector2D {
public:
	Vector2D(float x, float y) : m_x(x), m_y(y) {} 
	//수정 불가 
	float getX() { return m_x; }
	float getY() { return m_y; }
	//수정 가능 
	void setX(float x) { m_x = x; }
	void setY(float y) { m_y = y; }
	void setXY(float x, float y) { m_x = x, m_y = y; }

	//소인수분해
	// sqrt(double x) ==> x의 루트, 제곱근
	// sqrt(12.4) ==>  3.xxxx
	
	//pow(double base, double n) ==> base가 되는 숫자의 n 제곱, 즉 제곱을 구하는 함수 
	//pow(5, 3) -> 10의 2제곱 
	//둘모두 함수 오버로딩에 의해 double외의 다른 자료형 사용 가능
	float length() { return sqrt((float)(m_x * m_x + m_y * m_y)); } //둘다 10, 10이면 200 = 16.xxxxx

	Vector2D operator+(const Vector2D& v2) const;
	Vector2D operator-(const Vector2D& v2) const;
	Vector2D operator*(float scalar);
	Vector2D operator/(float scalar);

	Vector2D& operator*=(float scalar);
	Vector2D& operator/=(float scalar);

	void normalize();
	//friend로 선언된 다른 클래스의 private 및 protected 멤버에 접근가능
	friend Vector2D& operator+=(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator-=(Vector2D& v1, const Vector2D& v2);

private:
	float m_x;
	float m_y;
};


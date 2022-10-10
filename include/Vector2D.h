#pragma once
#include <math.h> 

class Vector2D {
public:
	Vector2D(float x, float y) : m_x(x), m_y(y) {} 
	//���� �Ұ� 
	float getX() { return m_x; }
	float getY() { return m_y; }
	//���� ���� 
	void setX(float x) { m_x = x; }
	void setY(float y) { m_y = y; }

	//���μ�����
	// sqrt(double x) ==> x�� ��Ʈ, ������
	// sqrt(12.4) ==>  3.xxxx
	
	//pow(double base, double n) ==> base�� �Ǵ� ������ n ����, �� ������ ���ϴ� �Լ� 
	//pow(5, 3) -> 10�� 2���� 
	//�Ѹ�� �Լ� �����ε��� ���� double���� �ٸ� �ڷ��� ��� ����
	float length() { return sqrt(m_x * m_x + m_y * m_y); } //�Ѵ� 10, 10�̸� 200 = 16.xxxxx

	Vector2D operator+(const Vector2D& v2) const;
	Vector2D operator-(const Vector2D& v2) const;
	Vector2D operator*(float scalar);
	Vector2D operator/(float scalar);

	Vector2D& operator*=(float scalar);
	Vector2D& operator/=(float scalar);

	void normalize();
	//friend�� ����� �ٸ� Ŭ������ private �� protected ����� ���ٰ���
	friend Vector2D& operator+=(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator-=(Vector2D& v1, const Vector2D& v2);

private:
	float m_x;
	float m_y;
};


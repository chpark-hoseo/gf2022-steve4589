#include <Vector2D.h>
#include <iostream>

Vector2D Vector2D::operator+(const Vector2D& v2) const
{
	return Vector2D(m_x + v2.m_x, m_y + v2.m_y);
}

Vector2D Vector2D::operator-(const Vector2D& v2) const
{
	return Vector2D(m_x - v2.m_x, m_y - v2.m_y);
}

Vector2D Vector2D::operator*(float scalar)
{
	return Vector2D(m_x * scalar, m_y * scalar);
}

Vector2D Vector2D::operator/(float scalar)
{
	return Vector2D(m_x / scalar, m_y / scalar);
}
//�����ϴϱ� �����ڿ� ���� 
Vector2D& Vector2D::operator*=(float scalar)
{
	m_x *= scalar;
	m_y *= scalar;
	return *this;
}
Vector2D& Vector2D::operator/=(float scalar)
{
	m_x /= scalar;
	m_y /= scalar;
	return *this;
}
//�Ű������� ���� ������ ��ȯ�ϱ� ���� ���� �Լ��� ����
//Vectpr2�Լ��� m_x�� m_y������ private�̱� ������ �̿� �����ϱ� ���� ����
//v2���ʹ� Ȥ�ó� ���ϸ� ������ ���� �޶����Ƿ� const����
Vector2D& operator+=(Vector2D& v1, const Vector2D& v2)
{
	v1.m_x += v2.m_x;
	v1.m_y += v2.m_y;
	return v1;
}
Vector2D& operator-=(Vector2D& v1, const Vector2D& v2)
{
	v1.m_x -= v2.m_x;
	v1.m_y -= v2.m_y;
	return v1;
}
//
void Vector2D::normalize()
{
	float l = length();
	if (l > 0) // 0�̸� �ǹ� �����Ƿ� 
	{
		(*this) *= 1 / l; //(*this)���� x, y�� ������ �� �Ҽ��� �κи� ���� 
		//(*this) => �� Ŭ������ �����ڸ� ȣ���ϰ� ����?
	}
}
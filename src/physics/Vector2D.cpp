#pragma once
#include <Vector2D.h>
#include <iostream>
//player.transform.position = new Vector2(1, 0); ==> 
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
//참조하니까 생성자에 대입 
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
//매개변수가 참조 변수라서 반환하기 위해 참조 함수로 선언
//Vectpr2함수의 m_x와 m_y변수는 private이기 때문에 이에 접근하기 위해 참조
//v2벡터는 혹시나 변하면 예상한 값과 달라지므로 const선언
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
	if (l > 0) // 0이면 의미 없으므로 
	{
		(*this) *= 1 / l; //(*this)값에 x, y외 제곱근 중 소수점 부분만 대입 
		//(*this) => 이 클래스의 생성자를 호출하고 대입?
	}
}
#include <Collider2D.h>

bool Collider2D::OnCollision2D()
{
	//�浹 ����
	std::cout << a.x << "  " << a.y << "\n";
	if (CheckAABB(a, *b) == true)
	{
		std::cout << "�� �尡��~" << "\n";
	}
	return true;
}
bool Collider2D::OnCollisionExit2D()
{
	if (isExit) return false;
	isExit = true;
	isEnter = false;
	//�浹 ����
	if (CheckAABB(a, *b) == false)
	{
		std::cout << "naga." << "\n";
	}
	return true;
}
//AAbb ���� => ȸ���� �ٽ� ��������� �ϱ⶧����, ������ ��ü�� ���� 
bool Collider2D::CheckAABB(struct a_AABB m_AABB, const SDL_Rect& d_AABB) //x = 0, y = 0 == x / y�� ���� ���� / ���� 
{
	//x���� �������� ���� �����ڸ�, m_AABB.x + m_AABB.w�� ������ �������̰�, d_AABB.x �� �̹��� �ȿ� ������ �ݶ��̴��� �ɸ���
	//x��, y�� ��� m_AABB�� ��ġ�ٸ� => �浹 ��
	if  //x�� 
		((m_AABB.x + m_AABB.w >= d_AABB.x && d_AABB.x + d_AABB.w >= m_AABB.x) && //d_AABB�� ��������� x�� �ִ� �����ȿ� ������ m_AABB�� �̿� ���ٸ� ==> x���� ��ħ
		//y��
		(m_AABB.y + m_AABB.h >= d_AABB.y && d_AABB.y + d_AABB.w >= m_AABB.y))
	{
		return true; //�浹
	}
	else return false; //�浹x
}
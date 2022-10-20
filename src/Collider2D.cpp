#include <Collider2D.h>
#include <Game.h>

bool Collider2D::OnCollision2D()
{
	vector<GameObject *> colliders = Game::GetInstance()->GetColliders();
	for (int i = 0; i < colliders.size(); i++)
	{
		if (colliders[i]->activeSelf() == false) continue;
		Vector2D getXY = colliders[i]->GetPosition();

		b.x = getXY.getX();
		b.y = getXY.getY();
		b.w = colliders[i]->getWidth();
		b.h = colliders[i]->getHeight();

		std::cout << b.y << "\n\n";
		
		if (CheckAABB(a, b) == true)
		{
			colliders[i]->SetActive(false);
			std::cout << "�浹" << "\n";
		}
	}
	return true;
}
bool Collider2D::OnCollisionExit2D()
{
	if (isExit) return false;
	isExit = true;
	isEnter = false;
	//�浹 ����
	
	if (CheckAABB(a, b) == false)
	{
		std::cout << "�ȳ��� ������" << "\n";
	}
	return true;
}
//AAbb ���� => ȸ���� �ٽ� ��������� �ϱ⶧����, ������ ��ü�� ���� 
bool Collider2D::CheckAABB(a_AABB m_AABB, b_AABB d_AABB) //x = 0, y = 0 == x / y�� ���� ���� / ���� 
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
#include <Game.h>
#include <Collider2D.h>

GameObject* Collider2D::OnCollision2D()
{
	GameObject* enterNote = NULL;

	for (int i = 0; i < colliders.size(); i++)
	{
		if (colliders[i]->activeSelf() == false) continue;
		Vector2D getXY = colliders[i]->GetPosition();

		b.x = getXY.getX();
		b.y = getXY.getY();
		b.w = colliders[i]->getWidth();
		b.h = colliders[i]->getHeight();

		if (CheckAABB(a, b) == true)
		{
			enterNote = colliders[i];
			if (!isEnter)
			{
				note = enterNote; //this->note��(��) nullptr�����ϴ�.
				isEnter = true;
			}
		}
	}
	return enterNote;
}

GameObject* Collider2D::OnCollisionExit2D()
{
	GameObject* exitGameObject = NULL; //��� ������Ʈ��

	if (note == NULL)return exitGameObject;

	Vector2D getXY = note->GetPosition();

	b.x = getXY.getX();
	b.y = getXY.getY();

	if (CheckAABB(a, b) == false)
	{
		exitGameObject = note;
		note = NULL;
		isEnter = false;
	}
	return exitGameObject;
}
void Collider2D::SetPosition(float x, float y, int h, int w)
{
	colliders = Game::GetInstance()->GetColliders();
	a.x = x;
	a.y = y;
	a.w = w;
	a.h = h;
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
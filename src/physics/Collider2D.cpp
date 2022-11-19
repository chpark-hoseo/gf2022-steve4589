#include <State_Play.h>
#include <Collider2D.h>

GameObject* Collider2D::OnCollision2D(std::string tag)
{
	vector<GameObject*> Objects;

	GameObject* enterNote = NULL;

	for (int i = 0; i < colliders.size(); i++)
	{
		if (colliders[i]->activeSelf() == false || colliders[i]->getTag() != tag) continue;
		Vector2D getXY = colliders[i]->GetPosition();

		b.x = getXY.getX();
		b.y = getXY.getY();

		if (CheckAABB(a, b) == true)
		{
			//Exit�� �Ѱ��� vector
			int agree = 0;
			if (collidedObjects.size() == 0)
			{
				collidedObjects.emplace_back(colliders[i]);
			}
			else
			{
				for (int j = 0; j < collidedObjects.size(); j++)
				{
					if (collidedObjects[j] != colliders[i]) { ++agree; }
					else if (collidedObjects[j] == colliders[i]) break; //�̹� �浹�ߴٸ�
				}
				if (agree == collidedObjects.size())
				{
					collidedObjects.insert(collidedObjects.begin(), colliders[i]); //ù��°�� ���� 
				}
			}
		}
	}
	if (collidedObjects.size() != 0) { enterNote = collidedObjects.back(); }
	return enterNote;
}
void Collider2D::EnterNotesPop() { if (collidedObjects.size() != 0) { collidedObjects.erase(collidedObjects.begin()); } }

vector <GameObject*> Collider2D::OnCollisionExit2D(std::string tag)
{
	vector <GameObject*> exitGameObject; //��� ������Ʈ��

	for (int i = 0; i < collidedObjects.size(); i++)
	{
		Vector2D getXY = collidedObjects[i]->GetPosition();

		b.x = getXY.getX();
		b.y = getXY.getY();

		if (collidedObjects[i]->getTag() != tag) continue;

		if (CheckAABB(a, b) == false)
		{
			exitGameObject.emplace_back(collidedObjects[i]);

			collidedObjects.pop_back();
			if (collidedObjects.size() == 0) //�޸� �ʱ�ȭ 
			{
				collidedObjects.shrink_to_fit();
			}
		}
	}
	return exitGameObject;
}
void Collider2D::SetPosition(float x, float y, int h, int w)
{
	colliders = State_Play::GetInstance()->GetColliders();
	b.w = colliders[0]->getWidth(); //������ ����� �� �Ȱ����Ƿ� 
	b.h = colliders[0]->getHeight();
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
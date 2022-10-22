#include <Game.h>
#include <Collider2D.h>

vector<GameObject*> Collider2D::OnCollision2D()
{
	vector<GameObject*> getGameObject; //충돌한 오브젝트들 
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
			getGameObject.emplace_back(colliders[i]);
		}
	}
	return getGameObject;
}

bool Collider2D::OnCollisionExit2D()
{
	if (isExit) return false;
	isExit = true;
	isEnter = false;
	//충돌 감지
	
	if (CheckAABB(a, b) == false)
	{
		std::cout << "다시 만나요" << "\n";
	}
	return true;
}
void Collider2D::SetPosition(float x, float y, int h, int w) 
{
	colliders = Game::GetInstance()->GetColliders(); 
	a.x = x;
	a.y = y;
	a.w = w;
	a.h = h;
}

//AAbb 패턴 => 회전시 다시 갱신해줘야 하기때문에, 정적인 물체에 적합 
bool Collider2D::CheckAABB(a_AABB m_AABB, b_AABB d_AABB) //x = 0, y = 0 == x / y는 가장 왼쪽 / 윗쪽 
{
	//x축을 기준으로 쉽게 말하자면, m_AABB.x + m_AABB.w는 원본의 영역안이고, d_AABB.x 가 이범위 안에 들어오면 콜라이더에 걸린것
	//x축, y축 모두 m_AABB과 겹치다면 => 충돌 중
	if  //x축 
		((m_AABB.x + m_AABB.w >= d_AABB.x && d_AABB.x + d_AABB.w >= m_AABB.x) && //d_AABB의 가장왼쪽이 x의 최대 범위안에 들어오고 m_AABB도 이와 같다면 ==> x축은 겹침
		//y축
		(m_AABB.y + m_AABB.h >= d_AABB.y && d_AABB.y + d_AABB.w >= m_AABB.y)) 
	{
		return true; //충돌
	}
	else return false; //충돌x
}
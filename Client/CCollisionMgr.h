#pragma once

class CCollider;
//id는 int = 4byte여서 32bit밀고 right 합치기 = 나오는건 8byte정수
//#define MAKE_COLID(left, right) (left<<32)|right

//CollisionID : UINT 2개이므로 8바이트 자료형이 된다.
union CollisionID {
	struct {
		UINT LeftID;
		UINT RightID;
	};
	UINT_PTR id;
};
class CCollisionMgr
{
	SINGLE(CCollisionMgr);
private:
	//2byte변수(16bit짜리)이므로 16*16 = 256개 판정 가능(대칭이므로 128개까지 가능)
	WORD				m_matrix[(UINT)LAYER::END];
	//id검사, UINT_PTR : 4+4 = 8byte
	//이전 프레임에 두 충돌체가 충돌했는지 확인
	map<UINT_PTR, bool>	m_mapPrevInfo;

	//bool	m_bShowCollide;
public:
	void LayerCheck(LAYER _left, LAYER _right);

	void Clear()
	{
		for (int i = 0; i < (UINT)LAYER::END; ++i)
		{
			m_matrix[i] = 0;
		}
	}

	//bool	GetShowCollide() { return m_bShowCollide; }
	//void	SetShowCollide(bool _collide) { m_bShowCollide = _collide; }

public:
	void tick();

private:
	void CollisionBtwLayer(LAYER _left, LAYER _right);
	bool CollisionBtwCollider(CCollider* _pLeft, CCollider* _pRight);
};


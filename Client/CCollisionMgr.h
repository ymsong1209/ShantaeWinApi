#pragma once

class CCollider;
//id�� int = 4byte���� 32bit�а� right ��ġ�� = �����°� 8byte����
//#define MAKE_COLID(left, right) (left<<32)|right

//CollisionID : UINT 2���̹Ƿ� 8����Ʈ �ڷ����� �ȴ�.
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
	//2byte����(16bit¥��)�̹Ƿ� 16*16 = 256�� ���� ����(��Ī�̹Ƿ� 128������ ����)
	WORD				m_matrix[(UINT)LAYER::END];
	//id�˻�, UINT_PTR : 4+4 = 8byte
	//���� �����ӿ� �� �浹ü�� �浹�ߴ��� Ȯ��
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


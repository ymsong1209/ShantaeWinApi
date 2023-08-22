#include "pch.h"
#include "CCollisionMgr.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CObj.h"
#include "CCollider.h"

CCollisionMgr::CCollisionMgr()
	: m_matrix{}
	//, m_bShowCollide(true)
{
}
CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::tick()
{
	for (UINT iRow = 0; iRow < (UINT)LAYER::END; ++iRow)
	{
		//����� ��Ī�����̱� ������ ���ݸ� �˻��ϸ� �ȴ�. -> �� iRow���� for�� ����
		for (UINT iCol = iRow; iCol < (UINT)LAYER::END; ++iCol)
		{
			if (!(m_matrix[iRow] & (1 << iCol)))
				continue;

			// iRow ���̾�� iCol ���̾�� ���� �浹�˻縦 �����Ѵ�.
			CollisionBtwLayer((LAYER)iRow, (LAYER)iCol);
		}
	}

	//if (IsTap(KEY::TAB)) {
	//	m_bShowCollide = !m_bShowCollide;
	//	//m_bRender = !m_bRender;
	//}
}

void CCollisionMgr::CollisionBtwLayer(LAYER _left, LAYER _right)
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

	const vector<CObj*>& vecLeft = pCurLevel->GetLayer(_left);
	const vector<CObj*>& vecRight = pCurLevel->GetLayer(_right);

	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		// �浹ü�� ���� ���
		if (nullptr == vecLeft[i]->GetCollider())
			continue;
		size_t j = 0;
		//Left, right ���� ���̾��� ���, ���� �˻縦 ���ϱ� ����
		if (_left == _right) { j = i; }

		for (; j < vecRight.size(); ++j)
		{
			// �浹ü�� �����ϰ� ���� �ʰų�, �浹�� �����ų �� ����� ������ ������Ʈ�� ���
			if (nullptr == vecRight[j]->GetCollider() || vecLeft[i] == vecRight[j])
				continue;

			//�� �浹ü�� ���̵� ����
			CollisionID ID = {};
			ID.LeftID = vecLeft[i]->GetCollider()->GetID();
			ID.RightID = vecRight[j]->GetCollider()->GetID();
			//���� ������ �浹 Ȯ��
			map<UINT_PTR, bool>::iterator iter = m_mapPrevInfo.find(ID.id);
			if (iter == m_mapPrevInfo.end()) {
				m_mapPrevInfo.insert(make_pair(ID.id, false));
				iter = m_mapPrevInfo.find(ID.id);
			}
			bool bDead = vecLeft[i]->IsDead() || vecRight[j]->IsDead();
			//���� �����ִ�.
			if (CollisionBtwCollider(vecLeft[i]->GetCollider(), vecRight[j]->GetCollider()))
			{
				//�������� ���� �־���.
				if (iter->second) {
					if(bDead) {
						vecLeft[i]->GetCollider()->EndOverlap(vecRight[j]->GetCollider());
						vecRight[j]->GetCollider()->EndOverlap(vecLeft[i]->GetCollider());
					}
					else {
						vecLeft[i]->GetCollider()->OnOverlap(vecRight[j]->GetCollider());
						vecRight[j]->GetCollider()->OnOverlap(vecLeft[i]->GetCollider());
					}
					
				}
				//������ �浹�� ���� ����. = �����浹
				else {
					//���� �ϳ��� Dead���¸� �浹�� ������ ������ �Ѵ�.
					if (!bDead) {
						vecLeft[i]->GetCollider()->BeginOverlap(vecRight[j]->GetCollider());
						vecRight[j]->GetCollider()->BeginOverlap(vecLeft[i]->GetCollider());
						iter->second = true;
					}
					
				}
			}
			//���� ������ �ִ�.
			else
			{
				//�������� ���� �־���. = ���ʷ� ������.
				if (iter->second) {
					vecLeft[i]->GetCollider()->EndOverlap(vecRight[j]->GetCollider());
					vecRight[j]->GetCollider()->EndOverlap(vecLeft[i]->GetCollider());
					iter->second = false;
				}
				
				
			}
		}
	}
}

bool CCollisionMgr::CollisionBtwCollider(CCollider* _pLeft, CCollider* _pRight)
{
	Vec2 vLeftPos = _pLeft->GetFinalPos();
	Vec2 vLeftScale = _pLeft->GetScale();

	Vec2 vRightPos = _pRight->GetFinalPos();
	Vec2 vRightScale = _pRight->GetScale();

	if (fabsf(vLeftPos.x - vRightPos.x) > (vLeftScale.x / 2.f + vRightScale.x / 2.f))
		return false;

	if (fabsf(vLeftPos.y - vRightPos.y) > (vLeftScale.y / 2.f + vRightScale.y / 2.f))
		return false;

	return true;
}

void CCollisionMgr::LayerCheck(LAYER _left, LAYER _right)
{
	UINT iRow = (UINT)_left;
	UINT iCol = (UINT)_right;

	if (iRow > iCol)
	{
		UINT iTemp = iCol;
		iCol = iRow;
		iRow = iTemp;
	}

	m_matrix[iRow] |= (1 << iCol);
}
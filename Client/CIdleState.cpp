#include "pch.h"
#include "CIdleState.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CPlayer.h"

#include "CMonster.h"
#include "CRigidbody.h"

CIdleState::CIdleState()
{
}

CIdleState::~CIdleState()
{
}

void CIdleState::finaltick()
{
	// ���� ���� ������Ʈ�� ���� ������ �ƴ� ���
	CMonster* pMon = dynamic_cast<CMonster*>(GetOwnerObj());
	assert(pMon);

	// Player �� �˾Ƴ���.
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(pCurLevel->GetLayer(LAYER::PLAYER)[0]);

	assert(pPlayer);
	pMon->idle();
	//Idle���� �ȱ�
	pMon->walk();

	// Player �� Monster �� �Ÿ����� ���
	float fDetectRange = pMon->GetMonInfo().m_fDetectRange;

	//������ ��� X��ǥ�� ����, �ٶ󺸴� ���⸸ ����
	if (pMon->GetRigidbody()->GetGravityUse() == true) {
		// Player �� Ž������ �̳��� ������ �������·� ��ȯ
		// ���Ͱ� ������ �ٶ󺸰� ������
		Vec2 vDir = pMon->GetPos() - pPlayer->GetPos();
		if (pMon->GetMonInfo().m_bIsLeft == true) {
			if (pPlayer->GetPos().x < pMon->GetPos().x) {
				if (abs(vDir.x) < fDetectRange && abs(vDir.y) < 20.f)
				{
					ChangeState(L"Trace");
				}
			}
		}
		//���Ͱ� �������� �ٶ󺸰� �������
		else if(pMon->GetMonInfo().m_bIsLeft == false) {
			if (pMon->GetPos().x < pPlayer->GetPos().x) {
				if (abs(vDir.x) < fDetectRange && abs(vDir.y) < 20.f)
				{
					ChangeState(L"Trace");
				}
			}
		}
		
	}

	//������ ��� ������ ����
	if (pMon->GetRigidbody()->GetGravityUse() == false) {
		// Player �� Ž������ �̳��� ������ �������·� ��ȯ
		Vec2 vDir = pMon->GetPos() - pPlayer->GetPos();
		if (vDir.Length() < fDetectRange)
		{
			ChangeState(L"Trace");
		}
	}

	
}

void CIdleState::Enter()
{
	CMonster* pMon = dynamic_cast<CMonster*>(GetOwnerObj());
	pMon->idle_enter();
}

void CIdleState::Exit()
{
	CMonster* pMon = dynamic_cast<CMonster*>(GetOwnerObj());
	pMon->idle_exit();
}
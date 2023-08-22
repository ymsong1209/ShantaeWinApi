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
	// 상태 소유 오브젝트가 몬스터 종류가 아닌 경우
	CMonster* pMon = dynamic_cast<CMonster*>(GetOwnerObj());
	assert(pMon);

	// Player 를 알아낸다.
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(pCurLevel->GetLayer(LAYER::PLAYER)[0]);

	assert(pPlayer);
	pMon->idle();
	//Idle에서 걷기
	pMon->walk();

	// Player 와 Monster 의 거리값을 계산
	float fDetectRange = pMon->GetMonInfo().m_fDetectRange;

	//지상일 경우 X좌표만 조사, 바라보는 방향만 조사
	if (pMon->GetRigidbody()->GetGravityUse() == true) {
		// Player 가 탐지범위 이내에 들어오면 추적상태로 전환
		// 몬스터가 왼쪽을 바라보고 있을때
		Vec2 vDir = pMon->GetPos() - pPlayer->GetPos();
		if (pMon->GetMonInfo().m_bIsLeft == true) {
			if (pPlayer->GetPos().x < pMon->GetPos().x) {
				if (abs(vDir.x) < fDetectRange && abs(vDir.y) < 20.f)
				{
					ChangeState(L"Trace");
				}
			}
		}
		//몬스터가 오른쪽을 바라보고 있을경우
		else if(pMon->GetMonInfo().m_bIsLeft == false) {
			if (pMon->GetPos().x < pPlayer->GetPos().x) {
				if (abs(vDir.x) < fDetectRange && abs(vDir.y) < 20.f)
				{
					ChangeState(L"Trace");
				}
			}
		}
		
	}

	//공중일 경우 전방향 조사
	if (pMon->GetRigidbody()->GetGravityUse() == false) {
		// Player 가 탐지범위 이내에 들어오면 추적상태로 전환
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
#include "pch.h"
#include "CTraceState.h"

#include "CTimeMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CPlayer.h"

#include "CMonster.h"
#include "CRigidbody.h"
CTraceState::CTraceState()
{
}

CTraceState::~CTraceState()
{
}


void CTraceState::finaltick()
{
	// 상태 소유 오브젝트가 몬스터 종류가 아닌 경우
	CMonster* pMon = dynamic_cast<CMonster*>(GetOwnerObj());
	assert(pMon);

	// Player 를 알아낸다.
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(pCurLevel->GetLayer(LAYER::PLAYER)[0]);

	assert(pPlayer);

	//Monster가 공중몹일경우
	if (!pMon->GetRigidbody()->GetGravityUse()) {
		Vec2 vMonPos = pMon->GetPos();
		Vec2 vPlayerPos = pPlayer->GetPos();

		Vec2 vMonToPlayer = vPlayerPos - vMonPos;
		vMonToPlayer.Normalize();

		float fSpeed = pMon->GetMonInfo().m_fSpeed;

		vMonPos += vMonToPlayer * DT * fSpeed;

		pMon->SetPos(vMonPos);
		
	}
	//Monster가 지상몹일경우
	else {
		Vec2 vMonPos = pMon->GetPos();
		Vec2 vPlayerPos = pPlayer->GetPos();

		Vec2 vMonToPlayer = vPlayerPos - vMonPos;
		vMonToPlayer.Normalize();

		float fSpeed = pMon->GetMonInfo().m_fSpeed;

		vMonPos += vMonToPlayer * DT * fSpeed;

		pMon->SetPos(Vec2(vMonPos.x, pMon->GetPos().y));
	}


	pMon->trace_changeAnim();
	// Player 와 Monster 의 거리값을 계산
	float fDetectRange = pMon->GetMonInfo().m_fDetectRange;
	// Player 가 탐지범위에서 벗어나면 Idle로 전환
	Vec2 vDir = pMon->GetPos() - pPlayer->GetPos();
	if (vDir.Length() > fDetectRange)
	{
		ChangeState(L"Idle");
	}
	// Player 가 공격범위에 들어오면 Attack으로 전환
	float fAttackRange = pMon->GetMonInfo().m_fAttRange;
	if (vDir.Length() < fAttackRange)
	{
		ChangeState(L"Attack");
	}

}

void CTraceState::Enter()
{
	CMonster* pMon = dynamic_cast<CMonster*>(GetOwnerObj());
	pMon->trace_enter();
}

void CTraceState::Exit()
{
	CMonster* pMon = dynamic_cast<CMonster*>(GetOwnerObj());
	pMon->trace_exit();
}

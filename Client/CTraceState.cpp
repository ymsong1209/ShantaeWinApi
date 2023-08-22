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
	// ���� ���� ������Ʈ�� ���� ������ �ƴ� ���
	CMonster* pMon = dynamic_cast<CMonster*>(GetOwnerObj());
	assert(pMon);

	// Player �� �˾Ƴ���.
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(pCurLevel->GetLayer(LAYER::PLAYER)[0]);

	assert(pPlayer);

	//Monster�� ���߸��ϰ��
	if (!pMon->GetRigidbody()->GetGravityUse()) {
		Vec2 vMonPos = pMon->GetPos();
		Vec2 vPlayerPos = pPlayer->GetPos();

		Vec2 vMonToPlayer = vPlayerPos - vMonPos;
		vMonToPlayer.Normalize();

		float fSpeed = pMon->GetMonInfo().m_fSpeed;

		vMonPos += vMonToPlayer * DT * fSpeed;

		pMon->SetPos(vMonPos);
		
	}
	//Monster�� ������ϰ��
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
	// Player �� Monster �� �Ÿ����� ���
	float fDetectRange = pMon->GetMonInfo().m_fDetectRange;
	// Player �� Ž���������� ����� Idle�� ��ȯ
	Vec2 vDir = pMon->GetPos() - pPlayer->GetPos();
	if (vDir.Length() > fDetectRange)
	{
		ChangeState(L"Idle");
	}
	// Player �� ���ݹ����� ������ Attack���� ��ȯ
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

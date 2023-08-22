#include "pch.h"
#include "CSquidAttackState.h"
#include "CTimeMgr.h"
#include "CSquidBaron.h"
#include "CAnimator.h"


CSquidAttackState::CSquidAttackState()
{
}

CSquidAttackState::~CSquidAttackState()
{
}

void CSquidAttackState::finaltick()
{
	CSquidBaron* pMon = dynamic_cast<CSquidBaron*>(GetOwnerObj());
	
	

	if (pMon->GetMonInfo().m_iWallHit > 4) {
		pMon->GetMonInfo().m_fAttackFinalDist += DT * pMon->GetMonInfo().m_fSpeed;
		if (pMon->GetMonInfo().m_fAttackFinalDist > 100.f) {
			pMon->GetAI()->ChangeState(L"Jump");
		}
		else {
			if (pMon->GetMonInfo().m_bIsLeft == true) {
				Vec2 vMonPos = pMon->GetPos();
				float fSpeed = pMon->GetMonInfo().m_fSpeed;
				vMonPos.x -= DT * fSpeed;
				pMon->SetPos(Vec2(vMonPos.x, pMon->GetPos().y));
			}
			else if (pMon->GetMonInfo().m_bIsLeft == false) {
				Vec2 vMonPos = pMon->GetPos();
				float fSpeed = pMon->GetMonInfo().m_fSpeed;
				vMonPos.x += DT * fSpeed;
				pMon->SetPos(Vec2(vMonPos.x, pMon->GetPos().y));
			}
		}
	}
	else {
		if (pMon->GetMonInfo().m_bIsLeft == true) {
			Vec2 vMonPos = pMon->GetPos();
			float fSpeed = pMon->GetMonInfo().m_fSpeed;
			vMonPos.x -= DT * fSpeed;
			pMon->SetPos(Vec2(vMonPos.x, pMon->GetPos().y));
		}
		else if (pMon->GetMonInfo().m_bIsLeft == false) {
			Vec2 vMonPos = pMon->GetPos();
			float fSpeed = pMon->GetMonInfo().m_fSpeed;
			vMonPos.x += DT * fSpeed;
			pMon->SetPos(Vec2(vMonPos.x, pMon->GetPos().y));
		}
	}
}

void CSquidAttackState::Enter()
{
	CSquidBaron* pMon = dynamic_cast<CSquidBaron*>(GetOwnerObj());
	if (pMon->GetMonInfo().m_bIsArmored == true) {
		pMon->GetMonInfo().m_fSpeed = 1000.f;
		pMon->AdjustCollider(L"SquidBaron_Armor_Attack", Vec2(180.f, 168.f), Vec2(29.f, 2748.f));
		pMon->GetAnimator()->Play(L"SquidBaron_Armor_Attack", true);
	}
	else if(pMon->GetMonInfo().m_bIsArmored == false) {
		pMon->GetMonInfo().m_fSpeed = 700.f;
		pMon->AdjustCollider(L"SquidBaron_Attack", Vec2(180.f, 168.f), Vec2(6.f, 7752.f));
		pMon->GetAnimator()->Play(L"SquidBaron_Attack", true);
	}
	pMon->GetMonInfo().m_iWallHit = 0;
	pMon->GetMonInfo().m_fTime = 0.f;
	pMon->GetMonInfo().m_fAttackFinalDist = 0.f;
}

void CSquidAttackState::Exit()
{
	CSquidBaron* pMon = dynamic_cast<CSquidBaron*>(GetOwnerObj());
	pMon->GetMonInfo().m_iWallHit = 0;
	pMon->GetMonInfo().m_fTime = 0.f;
	pMon->GetMonInfo().m_fAttackFinalDist = 0.f;
}
#include "pch.h"
#include "CSquidIdleState.h"
#include "CSquidBaron.h"

#include "CMonster.h"
#include "CRigidbody.h"
#include "CAnimator.h"

CSquidIdleState::CSquidIdleState()
{
}

CSquidIdleState::~CSquidIdleState()
{
}


void CSquidIdleState::finaltick()
{
	CSquidBaron* pMon = dynamic_cast<CSquidBaron*>(GetOwnerObj());
	if (pMon->GetMonInfo().m_iSquidAnger < 8) {
		if (pMon->GetAnimator()->AnimationFinish(L"SquidBaron_Grunt")) {
			pMon->GetAnimator()->AnimationReset(L"SquidBaron_Grunt");
			pMon->GetAnimator()->Play(L"SquidBaron_Grunt", false);
			++pMon->GetMonInfo().m_iSquidAnger;
		}
	}
	else {
		pMon->GetAI()->ChangeState(L"BuildUp");
	}

	
	
}

void CSquidIdleState::Enter()
{
	CSquidBaron* pMon = dynamic_cast<CSquidBaron*>(GetOwnerObj());
	pMon->AdjustCollider(L"SquidBaron_Grunt", Vec2(180.f, 168.f), Vec2(3.f,1539.f));
	pMon->GetAnimator()->Play(L"SquidBaron_Grunt", false);
}

void CSquidIdleState::Exit()
{
	CSquidBaron* pMon = dynamic_cast<CSquidBaron*>(GetOwnerObj());
	pMon->GetAnimator()->AnimationReset(L"SquidBaron_Grunt");
}



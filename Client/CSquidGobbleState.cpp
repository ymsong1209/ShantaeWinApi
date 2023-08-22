#include "pch.h"
#include "CSquidGobbleState.h"
#include "CSquidBaron.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CSquidBaronFood.h"
#include "CHealEffect.h"
#include "CResMgr.h"
#include "CSound.h"

CSquidGobbleState::CSquidGobbleState()
{
}

CSquidGobbleState::~CSquidGobbleState()
{
}

void CSquidGobbleState::finaltick()
{
	CSquidBaron* pMon = dynamic_cast<CSquidBaron*>(GetOwnerObj());
	
	if (pMon->GetMonInfo().m_iGobbleCount == 4) {
		if (pMon->GetMonInfo().m_bIsPhase1) {
			pMon->GetAI()->ChangeState(L"BuildUp");
		}
		else {
			pMon->GetAI()->ChangeState(L"ArmorUp");
		}
		
	}
}

void CSquidGobbleState::Enter()
{
	CSquidBaron* pMon = dynamic_cast<CSquidBaron*>(GetOwnerObj());
	pMon->GetMonInfo().m_iGobbleCount = 0;
	pMon->AdjustCollider(L"SquidBaron_Gobble", Vec2(180.f,165.f), Vec2(3.f,1281.f));
	pMon->GetAnimator()->Play(L"SquidBaron_Gobble", true);
	
	CSound* gobblesound = CResMgr::GetInst()->LoadSound(L"chew", L"sound\\monster\\baron_chew.wav");
	gobblesound->Play(true);
	CObj* pFood = new CSquidBaronFood(pMon);
	Vec2 vPos = pMon->GetPos();
	Instantiate(pFood, pMon->GetPos(), LAYER::DEATH_LEFTOVER);
}

void CSquidGobbleState::Exit()
{
	CSound* gobblesound = CResMgr::GetInst()->LoadSound(L"chew", L"sound\\monster\\baron_chew.wav");
	gobblesound->Stop(true);
	CSquidBaron* pMon = dynamic_cast<CSquidBaron*>(GetOwnerObj());
	pMon->GetMonInfo().m_iGobbleCount = 4;
}



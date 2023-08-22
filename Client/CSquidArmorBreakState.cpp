#include "pch.h"
#include "CSquidArmorBreakState.h"
#include "CAnimator.h"
#include "CSquidBaron.h"
#include "CResMgr.h"
#include "CSound.h"

CSquidArmorBreakState::CSquidArmorBreakState()
{
}

CSquidArmorBreakState::~CSquidArmorBreakState()
{
}
void CSquidArmorBreakState::finaltick()
{
	CSquidBaron* pMon = dynamic_cast<CSquidBaron*>(GetOwnerObj());
	if (pMon->GetAnimator()->AnimationFinish(L"SquidBaron_Armor_Break")) {
		pMon->GetMonInfo().m_bIsArmored = false;
		pMon->GetAI()->ChangeState(L"BuildUp");
	}
}

void CSquidArmorBreakState::Enter()
{
	CSquidBaron* pMon = dynamic_cast<CSquidBaron*>(GetOwnerObj());
	CSound* armorbreak = CResMgr::GetInst()->LoadSound(L"armorbreak", L"sound\\monster\\baron_armorbreak.wav");
	armorbreak->SetVolume(100);
	armorbreak->Play();
	pMon->GetAnimator()->Play(L"SquidBaron_Armor_Break", false);
}

void CSquidArmorBreakState::Exit()
{
	CSquidBaron* pMon = dynamic_cast<CSquidBaron*>(GetOwnerObj());
	pMon->GetAnimator()->AnimationReset(L"SquidBaron_Armor_Break");
}





#include "pch.h"
#include "CSquidArmorUpState.h"
#include "CTimeMgr.h"
#include "CSquidBaron.h"
#include "CAnimator.h"
#include "CResMgr.h"
#include "CSound.h"

CSquidArmorUpState::CSquidArmorUpState()
{
}

CSquidArmorUpState::~CSquidArmorUpState()
{
}

void CSquidArmorUpState::finaltick()
{
	CSquidBaron* pMon = dynamic_cast<CSquidBaron*>(GetOwnerObj());
	if (pMon->GetAnimator()->AnimationFinish(L"SquidBaron_ArmorUp")) {
		
		pMon->GetMonInfo().m_bIsArmored = true;
		pMon->GetAI()->ChangeState(L"BuildUp");
	}
}

void CSquidArmorUpState::Enter()
{
	CSquidBaron* pMon = dynamic_cast<CSquidBaron*>(GetOwnerObj());
	if (pMon->GetMonInfo().m_bIsArmored == false) {
		pMon->AdjustCollider(L"SquidBaron_ArmorUp", Vec2(180.f, 168.f), Vec2(94.f, 5893.f));
		pMon->GetAnimator()->Play(L"SquidBaron_ArmorUp", false);
		CSound* sound = CResMgr::GetInst()->LoadSound(L"armorup", L"sound\\monster\\baron_armorup.wav");
		sound->SetVolume(60);
		sound->Play();
	}

}

void CSquidArmorUpState::Exit()
{
	CSquidBaron* pMon = dynamic_cast<CSquidBaron*>(GetOwnerObj());
	
	pMon->GetAnimator()->AnimationReset(L"SquidBaron_ArmorUp");
}

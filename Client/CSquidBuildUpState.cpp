#include "pch.h"
#include "CSquidBuildUpState.h"
#include "CTimeMgr.h"
#include "CSquidBaron.h"
#include "CAnimator.h"
#include "CResMgr.h"
#include "CSound.h"

CSquidBuildUpState::CSquidBuildUpState()
{
}

CSquidBuildUpState::~CSquidBuildUpState()
{
}

void CSquidBuildUpState::finaltick()
{

	CSquidBaron* pMon = dynamic_cast<CSquidBaron*>(GetOwnerObj());
	pMon->SetBuildUpCooltime(pMon->ReturnBuildUpCooltime() + DT);
	if (pMon->ReturnBuildUpCooltime() > 1.f) {
		pMon->GetAI()->ChangeState(L"Attack");
	}
	
}

void CSquidBuildUpState::Enter()
{
	CSquidBaron* pMon = dynamic_cast<CSquidBaron*>(GetOwnerObj());
	CSound* sound = CResMgr::GetInst()->LoadSound(L"buildup", L"sound\\monster\\baron_buildup.wav");
	sound->Play(true);
	if (pMon->GetMonInfo().m_bIsLeft == true) {
		if (pMon->GetMonInfo().m_bIsArmored == true) {
			pMon->AdjustCollider(L"SquidBaron_Armor_BuildUp_L", Vec2(180.f,168.f), Vec2(15.f,4935.f));
			pMon->GetAnimator()->Play(L"SquidBaron_Armor_BuildUp_L", true);
		}
		else {
			pMon->AdjustCollider(L"SquidBaron_BuildUp_L", Vec2(180.f, 168.f), Vec2(15.f, 399.f));
			pMon->GetAnimator()->Play(L"SquidBaron_BuildUp_L", true);
		}
	}
	else if (pMon->GetMonInfo().m_bIsLeft == false) {
		if (pMon->GetMonInfo().m_bIsArmored == true) {
			pMon->AdjustCollider(L"SquidBaron_Armor_BuildUp_R", Vec2(180.f, 168.f), Vec2(15.f, 4935.f));
			pMon->GetAnimator()->Play(L"SquidBaron_Armor_BuildUp_R", true);
		}
		else {
			pMon->AdjustCollider(L"SquidBaron_BuildUp_R", Vec2(180.f, 168.f), Vec2(15.f, 399.f));
			pMon->GetAnimator()->Play(L"SquidBaron_BuildUp_R", true);
		}
	}
}

void CSquidBuildUpState::Exit()
{
	CSquidBaron* pMon = dynamic_cast<CSquidBaron*>(GetOwnerObj());
	CSound* sound = CResMgr::GetInst()->LoadSound(L"buildup", L"sound\\monster\\baron_buildup.wav");
	sound->Stop(true);
	pMon->GetAnimator()->AnimationReset(L"SquidBaron_Armor_BuildUp_L");
	pMon->GetAnimator()->AnimationReset(L"SquidBaron_BuildUp_L");
	pMon->GetAnimator()->AnimationReset(L"SquidBaron_Armor_BuildUp_R");
	pMon->GetAnimator()->AnimationReset(L"SquidBaron_BuildUp_R");
	pMon->SetBuildUpCooltime(0.f);
}



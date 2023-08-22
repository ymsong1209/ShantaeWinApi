#include "pch.h"
#include "CSquidPhase2State.h"
#include "CSquidBaron.h"
#include "CSquidBanner.h"
#include "CAnimator.h"
#include "CRigidbody.h"
#include "CSound.h"
#include "CResMgr.h"

CSquidPhase2State::CSquidPhase2State()
{
}

CSquidPhase2State::~CSquidPhase2State()
{
}


void CSquidPhase2State::finaltick()
{
	CSquidBaron* pMon = dynamic_cast<CSquidBaron*>(GetOwnerObj());

	if (pMon->GetAnimator()->AnimationFinish(L"SquidBaron_Die")) {
		if (pMon->GetMonInfo().m_bBannerSpawn == false) {
			CSound* boss2 = CResMgr::GetInst()->LoadSound(L"Boss2", L"sound\\bgm\\Boss2.wav");
			boss2->Play(true);
			CObj* cbanner = new CSquidBanner(pMon);
			Instantiate(cbanner, Vec2(2200.f, 300.f), LAYER::DEATH_LEFTOVER);
			pMon->GetAnimator()->Play(L"SquidBaron_Sparkle", true);
			pMon->GetMonInfo().m_bBannerSpawn = true;
		}
	}
	
}

void CSquidPhase2State::Enter()
{
	CSquidBaron* pMon = dynamic_cast<CSquidBaron*>(GetOwnerObj());
	pMon->GetMonInfo().m_bIsPhase1 = false;
	pMon->GetMonInfo().m_bIsArmored = true;
	pMon->GetAnimator()->Play(L"SquidBaron_Die", false);
	CSound* boss = CResMgr::GetInst()->LoadSound(L"Boss", L"sound\\bgm\\Boss.wav");
	boss->Stop(true);
}

void CSquidPhase2State::Exit()
{
	CSquidBaron* pMon = dynamic_cast<CSquidBaron*>(GetOwnerObj());
	pMon->GetMonInfo().m_bIsArmored = false;
	pMon->GetAnimator()->AnimationReset(L"SquidBaron_Die");
	//pMon->GetMonInfo().m_bIsArmored = true;
}


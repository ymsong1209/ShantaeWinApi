#include "pch.h"
#include "CSquidDeadState.h"
#include "CSquidBaron.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CTimeMgr.h"
#include "CCollider.h"
#include "CSquidBaronDeath.h"
#include "CResMgr.h"
#include "CSound.h"

CSquidDeadState::CSquidDeadState()
{
}

CSquidDeadState::~CSquidDeadState()
{
}


void CSquidDeadState::finaltick()
{
	CSquidBaron* pMon = dynamic_cast<CSquidBaron*>(GetOwnerObj());
	
	
	
}

void CSquidDeadState::Enter()
{
	CSound* boss2 = CResMgr::GetInst()->LoadSound(L"Boss2", L"sound\\bgm\\Boss2.wav");
	boss2->Stop(true);
	CSquidBaron* pMon = dynamic_cast<CSquidBaron*>(GetOwnerObj());
	pMon->GetAnimator()->Play(L"SquidBaron_Die", true);
	CObj* death = new CSquidBaronDeath();
	Instantiate(death, pMon->GetPos(), LAYER::DEATH_LEFTOVER);
	pMon->SetDead();
}


void CSquidDeadState::Exit()
{
}



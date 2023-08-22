#include "pch.h"
#include "CScareCrowDead.h"
#include "CScareCrow.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CSound.h"

CScareCrowDead::CScareCrowDead(CScareCrow* _pOwner)
	:IsLeft(_pOwner->GetMonInfo().m_bIsLeft)
	, m_sDeath(nullptr)
{
	CreateAnimator();
	GetAnimator()->SetFloorPlay(true);
	CTexture* ScareCrow_L = CResMgr::GetInst()->LoadTexture(L"Scarecrow_L", L"texture\\monster\\Scarecrow_L.bmp");
	CTexture* ScareCrow_R = CResMgr::GetInst()->LoadTexture(L"Scarecrow_R", L"texture\\monster\\Scarecrow_R.bmp");
	GetAnimator()->CreateAnimation(L"ScareCrow_Die_L", ScareCrow_L, Vec2(7.f, 1386.f), Vec2(252.f, 221.f), Vec2(0.f, 0.f), Vec2(7.f, 7.f), 11, 1, 11, 0.1f);
	GetAnimator()->FindAnimation(L"ScareCrow_Die_L")->Save(L"animation\\monster\\ScareCrow_Die_L.anim");
	GetAnimator()->CreateAnimation(L"ScareCrow_Die_R", ScareCrow_R, Vec2(7.f, 1386.f), Vec2(252.f, 221.f), Vec2(0.f, 0.f), Vec2(7.f, 7.f), 11, 1, 11, 0.1f);
	GetAnimator()->FindAnimation(L"ScareCrow_Die_R")->Save(L"animation\\monster\\ScareCrow_Die_R.anim");
	m_sDeath = CResMgr::GetInst()->LoadSound(L"scarecrow_death", L"sound\\monster\\enemy_mermaid_gethit_death.wav");
	m_sDeath->SetVolume(40);
	m_sDeath->Play();
	GetAnimator()->LoadAnimation(L"animation\\monster\\ScareCrow_Die_L.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\ScareCrow_Die_R.anim");
}

CScareCrowDead::~CScareCrowDead()
{
}

void CScareCrowDead::tick()
{
	if (IsLeft) {
		GetAnimator()->Play(L"ScareCrow_Die_L", false);
	}
	else {
		GetAnimator()->Play(L"ScareCrow_Die_R", false);
	}
	if (GetAnimator()->AnimationFinish(L"ScareCrow_Die_L") || GetAnimator()->AnimationFinish(L"ScareCrow_Die_R")) {
		SetDead();
	}
	CObj::tick();
}

void CScareCrowDead::render(HDC _dc)
{
	CObj::render(_dc);
}

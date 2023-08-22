#include "pch.h"
#include "CScorpGalDeath.h"
#include "CScorpGal.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CSound.h"



CScorpGalDeath::CScorpGalDeath(CScorpGal* _pOwner)
	:IsLeft(_pOwner->GetMonInfo().m_bIsLeft)
{
	CreateAnimator();
	GetAnimator()->SetFloorPlay(true);
	CTexture* ScorpGal_L = CResMgr::GetInst()->LoadTexture(L"ScorpGal_L", L"texture\\monster\\ScorpGal_L.bmp");
	CTexture* ScorpGal_R = CResMgr::GetInst()->LoadTexture(L"ScorpGal_R", L"texture\\monster\\ScorpGal_R.bmp");
	/*GetAnimator()->CreateAnimation(L"ScorpGal_Death_L", ScorpGal_L, Vec2(7.f, 1677.f), Vec2(609.f, 381.f), Vec2(0.f, 0.f), Vec2(7.f, 8.f), 40, 4, 12, 0.05f);
	GetAnimator()->FindAnimation(L"ScorpGal_Death_L")->Save(L"animation\\monster\\ScorpGal_Death_L.anim");
	GetAnimator()->CreateAnimation(L"ScorpGal_Death_R", ScorpGal_R, Vec2(7.f, 1677.f), Vec2(609.f, 381.f), Vec2(0.f, 0.f), Vec2(7.f, 8.f), 40, 4, 12, 0.05f);
	GetAnimator()->FindAnimation(L"ScorpGal_Death_R")->Save(L"animation\\monster\\ScorpGal_Death_R.anim");*/
	CSound* deathSound = CResMgr::GetInst()->LoadSound(L"scorpgal_die", L"sound\\monster\\scorpgal_die [1].wav");
	deathSound->SetVolume(40);
	deathSound->Play();
	GetAnimator()->LoadAnimation(L"animation\\monster\\ScorpGal_Death_L.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\ScorpGal_Death_R.anim");
}

CScorpGalDeath::~CScorpGalDeath()
{
}

void CScorpGalDeath::tick()
{
	if (IsLeft) {
		GetAnimator()->Play(L"ScorpGal_Death_L", false);
	}
	else {
		GetAnimator()->Play(L"ScorpGal_Death_R", false);
	}
	if (GetAnimator()->AnimationFinish(L"ScorpGal_Death_L") || GetAnimator()->AnimationFinish(L"ScorpGal_Death_R")) {
		SetDead();
	}
	CObj::tick();
}

void CScorpGalDeath::render(HDC _dc)
{
	CObj::render(_dc);
}

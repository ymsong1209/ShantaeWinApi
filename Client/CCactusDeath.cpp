#include "pch.h"
#include "CCactusDeath.h"
#include "CCactus.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CTexture.h"
#include "CResMgr.h"

#include "CSound.h"

CCactusDeath::CCactusDeath(CCactus* _pOwner)
	:IsLeft(_pOwner->GetMonInfo().m_bIsLeft)
{
	CreateAnimator();
	GetAnimator()->SetFloorPlay(true);
	CTexture* Cactus_L = CResMgr::GetInst()->LoadTexture(L"Cactus_L", L"texture\\monster\\Cactus_L.bmp");
	CTexture* Cactus_R = CResMgr::GetInst()->LoadTexture(L"Cactus_R", L"texture\\monster\\Cactus_R.bmp");
	CSound* death = CResMgr::GetInst()->LoadSound(L"cactus_death", L"sound\\monster\\enemy_cactus_gethit_death.wav");
	death->SetVolume(40);
	death->Play();
	
	//GetAnimator()->CreateAnimation(L"Cactus_Die_L", Cactus_L, Vec2(4.f, 522.f), Vec2(95.f, 79.f), Vec2(0.f, 0.f), Vec2(0.f, 0.f), 1, 1, 1, 1.0f);
	//GetAnimator()->FindAnimation(L"Cactus_Die_L")->Save(L"animation\\monster\\Cactus_Die_L.anim");
	//GetAnimator()->CreateAnimation(L"Cactus_Die_R", Cactus_R, Vec2(4.f, 522.f), Vec2(95.f, 79.f), Vec2(0.f, 0.f), Vec2(0.f, 0.f), 1, 1, 1, 1.0f);
	//GetAnimator()->FindAnimation(L"Cactus_Die_R")->Save(L"animation\\monster\\Cactus_Die_R.anim");

	GetAnimator()->LoadAnimation(L"animation\\monster\\Cactus_Die_L.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\Cactus_Die_R.anim");
}

CCactusDeath::~CCactusDeath()
{
}

void CCactusDeath::tick()
{
	if (IsLeft) {
		GetAnimator()->Play(L"Cactus_Die_L", false);
	}
	else {
		GetAnimator()->Play(L"Cactus_Die_R", false);
	}
	if (GetAnimator()->AnimationFinish(L"Cactus_Die_L") || GetAnimator()->AnimationFinish(L"Cactus_Die_R")) {
		SetDead();
	}
	CObj::tick();
}

void CCactusDeath::render(HDC _dc)
{
	CObj::render(_dc);
}
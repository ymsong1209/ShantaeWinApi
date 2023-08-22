#include "pch.h"
#include "CBatDeath.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CBat.h"
#include "CSound.h"


CBatDeath::CBatDeath(CBat* _pOwner)
	: IsLeft(_pOwner->GetMonInfo().m_bIsLeft)
	, m_sDeath(nullptr)
{
	CreateAnimator();
	CTexture* Bat_L = CResMgr::GetInst()->LoadTexture(L"Bat_L", L"texture\\monster\\Bat_L.bmp");
	CTexture* Bat_R = CResMgr::GetInst()->LoadTexture(L"Bat_R", L"texture\\monster\\Bat_R.bmp");
	/*GetAnimator()->CreateAnimation(L"Bat_Die_L", Bat_L, Vec2(6.f, 600.f), Vec2(144.f, 126.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 20, 2, 12, 0.075f);
	GetAnimator()->FindAnimation(L"Bat_Die_L")->Save(L"animation\\monster\\Bat_Die_L.anim");
	GetAnimator()->CreateAnimation(L"Bat_Die_R", Bat_R, Vec2(6.f, 600.f), Vec2(144.f, 126.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 20, 2, 12, 0.075f);
	GetAnimator()->FindAnimation(L"Bat_Die_R")->Save(L"animation\\monster\\Bat_Die_R.anim");*/

	GetAnimator()->LoadAnimation(L"animation\\monster\\Bat_Die_L.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\Bat_Die_R.anim");
	m_sDeath = CResMgr::GetInst()->LoadSound(L"bat_death", L"sound\\monster\\enemy_bat_death.wav");
	m_sDeath->Play();
}

CBatDeath::~CBatDeath()
{
}

void CBatDeath::tick()
{
	if (IsLeft) {
		GetAnimator()->Play(L"Bat_Die_L", false);
	}
	else {
		GetAnimator()->Play(L"Bat_Die_R", false);
	}
	if (GetAnimator()->AnimationFinish(L"Bat_Die_L") || GetAnimator()->AnimationFinish(L"Bat_Die_R")) {
		SetDead();
	}
	CObj::tick();
}

void CBatDeath::render(HDC _dc)
{
	CObj::render(_dc);
}



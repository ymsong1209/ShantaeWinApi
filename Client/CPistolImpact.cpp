#include "pch.h"
#include "CPistolImpact.h"
#include "CResMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CSound.h"


CPistolImpact::CPistolImpact(PLAYER_DIR _dir)
	:m_EDir(_dir)
{
	CreateAnimator();
	CTexture* pFxTex_L = CResMgr::GetInst()->LoadTexture(L"fx_L", L"texture\\fx\\fx_L.bmp");
	CTexture* pFxTex_R = CResMgr::GetInst()->LoadTexture(L"fx_R", L"texture\\fx\\fx_R.bmp");
	CSound* pistolimpact = CResMgr::GetInst()->LoadSound(L"pistol_impact", L"sound\\player\\player_risky_pistol_impact.wav");
	pistolimpact->SetVolume(25);
	pistolimpact->Play();

	/*GetAnimator()->CreateAnimation(L"Pistol_Bullet_Impact", pFxTex_L, Vec2(3.f, 4521.f), Vec2(24.f, 27.f), Vec2(0.f, 0.f), Vec2(3.f, 0.f), 3, 1, 3, 0.1f);
	GetAnimator()->FindAnimation(L"Pistol_Bullet_Impact")->Save(L"animation\\fx\\Pistol_Bullet_Impact.anim");
	GetAnimator()->CreateAnimation(L"Pistol_Bullet_Impact_R", pFxTex_R, Vec2(3.f, 4521.f), Vec2(24.f, 27.f), Vec2(0.f, 0.f), Vec2(3.f, 0.f), 3, 1, 3, 0.1f);
	GetAnimator()->FindAnimation(L"Pistol_Bullet_Impact_R")->Save(L"animation\\fx\\Pistol_Bullet_Impact_R.anim");*/
	GetAnimator()->LoadAnimation(L"animation\\fx\\Pistol_Bullet_Impact.anim");
	GetAnimator()->LoadAnimation(L"animation\\fx\\Pistol_Bullet_Impact_R.anim");
}

CPistolImpact::~CPistolImpact()
{

}

void CPistolImpact::tick()
{
	if (m_EDir == PLAYER_DIR::LEFT) {
		GetAnimator()->Play(L"Pistol_Bullet_Impact", false);
		if (GetAnimator()->AnimationFinish(L"Pistol_Bullet_Impact")) {
			GetAnimator()->AnimationReset(L"Pistol_Bullet_Impact");
			SetDead();
		}
	}
	else if (m_EDir == PLAYER_DIR::RIGHT) {
		GetAnimator()->Play(L"Pistol_Bullet_Impact_R", false);
		if (GetAnimator()->AnimationFinish(L"Pistol_Bullet_Impact_R")) {
			GetAnimator()->AnimationReset(L"Pistol_Bullet_Impact_R");
			SetDead();
		}
	}
	
	CObj::tick();
}

void CPistolImpact::render(HDC _dc)
{
	CObj::render(_dc);
}

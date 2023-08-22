#include "pch.h"
#include "CExplosion.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CSound.h"


CExplosion::CExplosion(int _isound)
	: m_pAtlas(nullptr)
	, m_iSoundNum(_isound)
{
	CreateAnimator();
	m_pAtlas = CResMgr::GetInst()->LoadTexture(L"fx_L", L"texture\\monster\\fx_L.bmp");
	GetAnimator()->CreateAnimation(L"Explosion", m_pAtlas, Vec2(3.f, 1383.f), Vec2(120.f, 120.f), Vec2(0.f, 0.f), Vec2(3.f, 3.f), 12, 2, 11, 0.05f);
	GetAnimator()->FindAnimation(L"Explosion")->Save(L"animation\\fx\\Explosion.anim");
	GetAnimator()->LoadAnimation(L"animation\\fx\\Explosion.anim");
	if (m_iSoundNum == 0) {
		CSound* sound = CResMgr::GetInst()->LoadSound(L"Explosion1", L"sound\\fx\\explosion_popcorn_01.wav");
		sound->SetVolume(40);
		sound->Play();
	}
	else if (m_iSoundNum == 1) {
		CSound* sound = CResMgr::GetInst()->LoadSound(L"Explosion2", L"sound\\fx\\explosion_popcorn_02.wav");
		sound->SetVolume(40);
		sound->Play();
	}
	else if (m_iSoundNum == 2) {
		CSound* sound = CResMgr::GetInst()->LoadSound(L"Explosion3", L"sound\\fx\\explosion_popcorn_03.wav");
		sound->SetVolume(40);
		sound->Play();
	}
	GetAnimator()->Play(L"Explosion", false);
}

CExplosion::~CExplosion()
{
}
void CExplosion::tick()
{
	if (GetAnimator()->AnimationFinish(L"Explosion")) {
		SetDead();
	}
	CObj::tick();
}

void CExplosion::render(HDC _dc)
{
	CObj::render(_dc);
}





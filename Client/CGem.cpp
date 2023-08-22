#include "pch.h"
#include "CGem.h"
#include "CRigidbody.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CResMgr.h"
#include "CTimeMgr.h"
#include "CPlayer.h"
#include "CPlatform.h"
#include "CSound.h"

CGem::CGem(int _iGemSize)
	 : m_iGemNum(0)
	, m_iGemSize(_iGemSize)
	, m_iGemValue(0)
	, m_sBig(nullptr)
	, m_sMid(nullptr)
	, m_sSmall(nullptr)
	, m_sBounce(nullptr)
{
	//srand(DT);
	srand((UINT)time(NULL));
	//srand((UINT)time(NULL));
	m_iGemNum = rand() % 4;
	CreateAnimator();
	CreateCollider();
	CreateRigidbody();
	m_sSmall = CResMgr::GetInst()->LoadSound(L"Gem_Small", L"sound\\fx\\pickup_gem_small.wav");
	m_sMid = CResMgr::GetInst()->LoadSound(L"Gem_Mid", L"sound\\fx\\pickup_gem_mid.wav");
	m_sBig = CResMgr::GetInst()->LoadSound(L"Gem_Big", L"sound\\fx\\pickup_gem_big.wav");
	m_sBounce = CResMgr::GetInst()->LoadSound(L"Gem_Bounce", L"sound\\fx\\pickup_coin_bounce_small.wav");
	m_sBounce->SetVolume(100);
	GetRigidbody()->SetGravity(true);
	GetRigidbody()->SetGravityAccel(800.f);
	GetRigidbody()->SetGravityVelocityLimit(1000.f);
	GetRigidbody()->SetVelocity(Vec2(0.f, -300.f));
	CreateAnim();
	if (m_iGemSize == 0) {
		GetCollider()->SetScale(Vec2(60.f, 42.f));
		m_iGemValue = 10;
	}
	else if (m_iGemSize == 1) {
		GetCollider()->SetScale(Vec2(30.f, 42.f));
		m_iGemValue = 5;
	}
	else if(m_iGemSize==2) {
		GetCollider()->SetScale(Vec2(30.f, 32.f));
		m_iGemValue = 1;
	}
	
	
}

CGem::~CGem()
{
}

void CGem::tick()
{
	GetAnimator()->Play(m_iGemNum * 3 + m_iGemSize, true);
	CObj::tick();
}

void CGem::render(HDC _dc)
{
	CObj::render(_dc);
}

void CGem::BeginOverlap(CCollider* _pOther)
{
	CPlatform* cPlatform = dynamic_cast<CPlatform*>(_pOther->GetOwner());
	int volume = m_sBounce->GetVolume();
	//m_sBounce->SetVolume(volume / 2);
	if (nullptr != cPlatform) {
		if (GetRigidbody()->GetGround() == false) {
			Vec2 vel = GetRigidbody()->GetVelocity();
			if (0.f <= vel.y && vel.y < 5.f) {
				GetRigidbody()->SetGround(true);
				GetRigidbody()->SetVelocity(Vec2(0.f, 0.f));
			}
			else {
				if (vel.y > 0.f) {
					GetRigidbody()->SetVelocity(Vec2(vel.x, -vel.y * 0.5f));
					m_sBounce->Play();
					
				}
			}
		}
		
		
	}


	CPlayer* cPlayer = dynamic_cast<CPlayer*>(_pOther->GetOwner());
	if (nullptr != cPlayer) {
		int pMoney = cPlayer->ReturnMoney();
		if (m_iGemSize == 0) {
			m_sBig->Play(false);
		}
		else if (m_iGemSize == 1) {
			m_sMid->Play(false);
		}
		else if (m_iGemSize == 2) {
			m_sSmall->Play(false);
		}
		if (pMoney < 999) {
			cPlayer->SetMoney(pMoney+m_iGemValue);
		}
		cPlayer->UpdateMoney();
		SetDead();
	}
}

void CGem::OnOverlap(CCollider* _pOther)
{
	CPlatform* cPlatform = dynamic_cast<CPlatform*>(_pOther->GetOwner());
	if (nullptr != cPlatform) {
		if (GetRigidbody()->GetGround() == false) {
			Vec2 vel = GetRigidbody()->GetVelocity();
			if (0.f <= vel.y && vel.y < 5.f) {
				GetRigidbody()->SetGround(true);
				GetRigidbody()->SetVelocity(Vec2(0.f, 0.f));
			}
			else {
				if (vel.y > 0.f) {
					GetRigidbody()->SetVelocity(Vec2(vel.x, -vel.y * 0.5f));
				}
			}
		}


	}
}




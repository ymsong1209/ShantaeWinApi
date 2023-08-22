#include "pch.h"
//#include "CItem.h"
#include "CHeart.h"

#include "CPlayer.h"
#include "CPlatform.h"
#include "CCollider.h"
#include "CRigidbody.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CPathMgr.h"
#include "CHealEffect.h"
#include "CSound.h"

CHeart::CHeart()
	: m_fTime(0.f)
	, m_fRatio(0.f)
	, m_fDir(1.f)
	, m_sound(nullptr)
{
	CreateCollider();
	CreateAnimator();
	CreateRigidbody();

	GetRigidbody()->SetGravity(true);
	GetRigidbody()->SetGravityAccel(50.f);
	GetRigidbody()->SetGravityVelocityLimit(500.f);
	m_sound = CResMgr::GetInst()->LoadSound(L"Heart", L"sound\\fx\\pickup_heart_small.wav");

	CTexture* Objects = CResMgr::GetInst()->LoadTexture(L"Objects", L"texture\\objects\\Objects.bmp");
	/*GetAnimator()->CreateAnimation(L"Heart", Objects, Vec2(430.f, 615.f), Vec2(30.f, 25.f), Vec2(0.f, 0.f), Vec2(5.f, 0.f), 4, 1, 4, 0.1f);
	GetAnimator()->FindAnimation(L"Heart")->Save(L"animation\\object\\Heart.anim");*/
	GetAnimator()->LoadAnimation(L"animation\\object\\Heart.anim");
	GetCollider()->SetScale(Vec2(30.f, 25.f));
		
}

CHeart::~CHeart()
{
}

void CHeart::tick()
{
	m_fTime += DT;
	m_fRatio += DT * m_fDir * 0.9f;

	if (1.f < m_fRatio)
	{
		m_fRatio = 1.f;
		m_fDir = -1.f;
	}
	else if (m_fRatio < 0.f)
	{
		m_fRatio = 0.f;
		m_fDir = 1;
	}
	if (!(GetRigidbody()->GetGround())) {
		GetRigidbody()->SetVelocity(Vec2(m_fDir*100.f, GetRigidbody()->GetVelocity().y));
	}
	
	GetAnimator()->Play(L"Heart", true);

	CObj::tick();
}

void CHeart::render(HDC _dc)
{
	CObj::render(_dc);
}

void CHeart::BeginOverlap(CCollider* _pOther)
{
	CPlatform* cPlatform = dynamic_cast<CPlatform*>(_pOther->GetOwner());
	if (nullptr != cPlatform) {
		GetRigidbody()->SetGround(true);
	}


	CPlayer* cPlayer = dynamic_cast<CPlayer*>(_pOther->GetOwner());
	if (nullptr != cPlayer) {
		CObj* pHeal = new CHealEffect(1);
		m_sound->Play(false);
		Vec2 vPos = Vec2(cPlayer->GetPos().x, cPlayer->GetPos().y - cPlayer->GetCollider()->GetScale().y);
		Instantiate(pHeal, vPos, LAYER::DAMAGE);
		if (cPlayer->ReturnHP() < cPlayer->ReturnMaxHP()) {
			cPlayer->SetHP(cPlayer->ReturnHP() + 1);
		}
		cPlayer->UpdateHeartContainer();
		SetDead();
	}
}



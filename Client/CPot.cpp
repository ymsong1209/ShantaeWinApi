#include "pch.h"
#include "CPot.h"
#include "CPlayer.h"
#include "CPlatform.h"
#include "CCollider.h"
#include "CRigidbody.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CPathMgr.h"

#include "CHeart.h"
#include "CGem.h"
#include "CPotParticle.h"

#include "CWhip.h"
#include "CPistol.h"
#include "CScimitar.h"
#include "CSound.h"

CPot::CPot()
	: m_iItemNum(0)
	, m_sSound(nullptr)
{
	CreateCollider();
	CreateAnimator();
	m_sSound = CResMgr::GetInst()->LoadSound(L"Pot", L"sound\\fx\\object_pot_smash_small.wav");
	CTexture* object = CResMgr::GetInst()->LoadTexture(L"Objects", L"texture\\objects\\Objects.bmp");
	/*GetAnimator()->CreateAnimation(L"Pot", object, Vec2(105.f, 37.f), Vec2(30.f, 40.f), Vec2(0.f, 0.f), Vec2(5.f, 0.f), 4, 1, 4, 0.1f);
	GetAnimator()->FindAnimation(L"Pot")->Save(L"animation\\object\\Pot.anim");*/
	GetAnimator()->LoadAnimation(L"animation\\object\\Pot.anim");
	GetCollider()->SetScale(Vec2(47.f, 42.f));
}

CPot::~CPot()
{
}

void CPot::tick()
{
	GetAnimator()->Play(L"Pot", true);
	CObj::tick();
}

void CPot::render(HDC _dc)
{
	CObj::render(_dc);
}

void CPot::BeginOverlap(CCollider* _pOther)
{
	CWhip* cWhip = dynamic_cast<CWhip*>(_pOther->GetOwner());
	if (nullptr != cWhip) {
		m_sSound->Play();
		srand((UINT)time(NULL));
		m_iItemNum = rand() % 2;
		CPotParticle* cParticle1 = new CPotParticle(0);
		cParticle1->GetRigidbody()->SetVelocity(Vec2(-150.f, -400.f));
		Instantiate(cParticle1, GetPos(), LAYER::FIELD_OBJ);
		CPotParticle* cParticle2 = new CPotParticle(1);
		cParticle2->GetRigidbody()->SetVelocity(Vec2(0.f, -300.f));
		Instantiate(cParticle2, GetPos(), LAYER::FIELD_OBJ);
		CPotParticle* cParticle3 = new CPotParticle(2);
		cParticle3->GetRigidbody()->SetVelocity(Vec2(160.f, -300.f));
		Instantiate(cParticle3, GetPos(), LAYER::FIELD_OBJ);

		if (m_iItemNum == 0) {
			CHeart* cHeart = new CHeart;
			Instantiate(cHeart, GetPos(), LAYER::FIELD_OBJ);
		}
		else {
			CGem* cGem = new CGem(1);
			Instantiate(cGem, GetPos(), LAYER::FIELD_OBJ);
		}
		SetDead();
	}

	CPistol* cPistol = dynamic_cast<CPistol*>(_pOther->GetOwner());
	if (nullptr != cPistol) {
		m_sSound->Play();
		srand((UINT)time(NULL));
		m_iItemNum = rand() % 2;
		if (m_iItemNum == 0) {
			CHeart* cHeart = new CHeart;
			Instantiate(cHeart, GetPos(), LAYER::FIELD_OBJ);
		}
		else if (m_iItemNum == 1) {
			CGem* cGem = new CGem(1);
			Instantiate(cGem, GetPos(), LAYER::FIELD_OBJ);
		}
		SetDead();
	}
	
	CScimitar* cScimitar = dynamic_cast<CScimitar*>(_pOther->GetOwner());
	if (nullptr != cScimitar) {
		m_sSound->Play();
		srand((UINT)time(NULL));
		m_iItemNum = rand() % 2;
		if (m_iItemNum == 0) {
			CHeart* cHeart = new CHeart;
			Instantiate(cHeart, GetPos(), LAYER::FIELD_OBJ);
		}
		else if (m_iItemNum == 1) {
			CGem* cGem = new CGem(1);
			Instantiate(cGem, GetPos(), LAYER::FIELD_OBJ);
		}
		SetDead();
	}
}
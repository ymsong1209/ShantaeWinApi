#include "pch.h"
#include "CSquidBaron_ElecSmall.h"
#include "CSquidBaron.h"
#include "CResMgr.h"
#include "CTimeMgr.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CRigidbody.h"
#include "CPlayer.h"
#include "CSound.h"

CSquidBaron_ElecSmall::CSquidBaron_ElecSmall(CSquidBaron* _pOwner, float _fDegree)
	: m_pOwner(_pOwner)
	, m_pAtlas_L(nullptr)
	, m_pAtlas_R(nullptr)
	, m_fSpeed(0.f)
	, m_fDegree(_fDegree)
	, m_fTime(0.f)
	, m_iDmg(0)
{
	m_iDmg = (int)m_pOwner->GetMonInfo().m_fAtt;
	m_pAtlas_L = CResMgr::GetInst()->LoadTexture(L"SquidBaron_L", L"texture\\monster\\SquidBaron_L.bmp");
	m_pAtlas_R = CResMgr::GetInst()->LoadTexture(L"SquidBaron_R", L"texture\\monster\\SquidBaron_R.bmp");
	m_fSpeed = 500.f;
	CreateAnimator();
	CreateCollider();
	CSound* sound = CResMgr::GetInst()->LoadSound(L"lightning", L"sound\\monster\\baron_lightning.wav");
	sound->Play();
	GetCollider()->SetScale(Vec2(97.f,53.f));
	GetAnimator()->CreateAnimation(L"ShockWave_L", m_pAtlas_L, Vec2(3.f, 2061.f), Vec2(165.f, 120.f), Vec2(0.f, 0.f), Vec2(3.f, 0.f), 6, 1, 6, 0.1f);
	GetAnimator()->FindAnimation(L"ShockWave_L")->Save(L"animation\\fx\\ShockWave_L.anim");
	GetAnimator()->CreateAnimation(L"ShockWave_R", m_pAtlas_R, Vec2(3.f, 2061.f), Vec2(165.f, 120.f), Vec2(0.f, 0.f), Vec2(3.f, 0.f), 6, 1, 6, 0.1f);
	GetAnimator()->FindAnimation(L"ShockWave_R")->Save(L"animation\\fx\\ShockWave_R.anim");

	GetAnimator()->LoadAnimation(L"animation\\fx\\ShockWave_R.anim");
	GetAnimator()->LoadAnimation(L"animation\\fx\\ShockWave_L.anim");
}

CSquidBaron_ElecSmall::~CSquidBaron_ElecSmall()
{
}


void CSquidBaron_ElecSmall::tick()
{
	m_fTime += DT;
	if (m_fTime > 15.f) {
		SetDead();
	}
	//포토샵 오류, 반대로 설정해야함

	if (m_fDegree == 180.f) {
		GetAnimator()->Play(L"ShockWave_R", true);
	}
	else if (m_fDegree == 0.f) {
		GetAnimator()->Play(L"ShockWave_L", true);
	}
	float fRadian = (m_fDegree * PI) / 180.f;
	Vec2 vPos = GetPos();
	vPos.x += m_fSpeed * cosf(fRadian) * DT;
	vPos.y += m_fSpeed * sinf(fRadian) * DT;
	SetPos(vPos);
	CObj::tick();
}

void CSquidBaron_ElecSmall::render(HDC _dc)
{
	CObj::render(_dc);
}

void CSquidBaron_ElecSmall::BeginOverlap(CCollider* _pOther)
{
	CPlayer* cPlayer = dynamic_cast<CPlayer*>(_pOther->GetOwner());
	if (nullptr != cPlayer) {
		SetDead();
	}
	return;
}


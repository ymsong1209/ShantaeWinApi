#include "pch.h"
#include "CSquidBaron_ElecBig.h"
#include "CSquidBaron.h"
#include "CResMgr.h"
#include "CTimeMgr.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CRigidbody.h"
#include "CPlayer.h"
#include "CSound.h"

CSquidBaron_ElecBig::CSquidBaron_ElecBig(CSquidBaron* _pOwner, float _fDegree)
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
	GetCollider()->SetScale(Vec2(160.f, 94.f));
	CSound* sound = CResMgr::GetInst()->LoadSound(L"lightning", L"sound\\monster\\baron_lightning.wav");
	sound->Play();
	GetAnimator()->CreateAnimation(L"ShockWaveBig_L", m_pAtlas_L, Vec2(3.f, 2244.f), Vec2(246.f, 201.f), Vec2(0.f, 0.f), Vec2(3.f, 0.f), 6, 1, 6, 0.1f);
	GetAnimator()->FindAnimation(L"ShockWaveBig_L")->Save(L"animation\\fx\\ShockWaveBig_L.anim");
	GetAnimator()->CreateAnimation(L"ShockWaveBig_R", m_pAtlas_R, Vec2(3.f, 2244.f), Vec2(246.f, 201.f), Vec2(0.f, 0.f), Vec2(3.f, 0.f), 6, 1, 6, 0.1f);
	GetAnimator()->FindAnimation(L"ShockWaveBig_R")->Save(L"animation\\fx\\ShockWaveBig_R.anim");

	GetAnimator()->LoadAnimation(L"animation\\fx\\ShockWaveBig_R.anim");
	GetAnimator()->LoadAnimation(L"animation\\fx\\ShockWaveBig_L.anim");
}

CSquidBaron_ElecBig::~CSquidBaron_ElecBig()
{
}


void CSquidBaron_ElecBig::tick()
{
	m_fTime += DT;
	if (m_fTime > 15.f) {
		SetDead();
	}
	if (m_fDegree == 0.f) {
		GetAnimator()->Play(L"ShockWaveBig_L", true);
	}
	else if (m_fDegree == 180.f) {
		GetAnimator()->Play(L"ShockWaveBig_R", true);
	}
	float fRadian = (m_fDegree * PI) / 180.f;
	Vec2 vPos = GetPos();
	vPos.x += m_fSpeed * cosf(fRadian) * DT;
	vPos.y += m_fSpeed * sinf(fRadian) * DT;
	SetPos(vPos);
	CObj::tick();
}

void CSquidBaron_ElecBig::render(HDC _dc)
{
	CObj::render(_dc);
}

void CSquidBaron_ElecBig::BeginOverlap(CCollider* _pOther)
{
	CPlayer* cPlayer = dynamic_cast<CPlayer*>(_pOther->GetOwner());
	if (nullptr != cPlayer) {
		SetDead();
	}
	return;
}

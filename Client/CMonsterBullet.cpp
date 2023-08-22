#include "pch.h"
#include "CMonsterBullet.h"
#include "CMonster.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"
#include "CPlayer.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CTimeMgr.h"


CMonsterBullet::CMonsterBullet(CMonster* _pOwner , float _mfDegree)
	: m_pOwner(_pOwner)
	, m_fSpeed(200.f)
	, m_fDegree(_mfDegree)
	, m_fTime(0.f)
	, m_iDmg(0)
{
	CreateAnimator();
	CreateCollider();
	GetCollider()->SetScale(Vec2(21.f, 21.f));
	m_iDmg = (int)m_pOwner->GetMonInfo().m_fAtt;
	CTexture* fx = CResMgr::GetInst()->LoadTexture(L"fx_L", L"texture\\fx\\fx_L.bmp");

	GetAnimator()->CreateAnimation(L"MonsterBullet", fx, Vec2(6.f, 7542.f), Vec2(21.f, 21.f), Vec2(0.f, 0.f), Vec2(9.f, 0.f), 2, 1, 2, 0.1f);
	GetAnimator()->FindAnimation(L"MonsterBullet")->Save(L"animation\\fx\\MonsterBullet.anim");

	GetAnimator()->LoadAnimation(L"animation\\fx\\MonsterBullet.anim");
}

CMonsterBullet::~CMonsterBullet()
{
}


void CMonsterBullet::tick()
{
	Vec2 vPos = GetPos();
	GetAnimator()->Play(L"MonsterBullet", true);
	//vPos.y -= m_fSpeed * DT;
	//대각선으로 쏘기
	float fRadian = (m_fDegree * PI) / 180.f;
	vPos.x += m_fSpeed * cosf(fRadian) * DT;
	vPos.y -= m_fSpeed * sinf(fRadian) * DT;

	SetPos(vPos);
	m_fTime += DT;
	if (3.f < m_fTime) {
		SetDead();
	}
	CObj::tick();
}

void CMonsterBullet::render(HDC _dc)
{
	CObj::render(_dc);
}

void CMonsterBullet::BeginOverlap(CCollider* _pOther)
{
	CPlayer* cPlayer = dynamic_cast<CPlayer*>(_pOther->GetOwner());
	if (nullptr != cPlayer) {
		SetDead();
	}
	return;
}
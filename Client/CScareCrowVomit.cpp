#include "pch.h"
#include "CScareCrowVomit.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"
#include "CPlayer.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CTimeMgr.h"
#include "CSound.h"

CScareCrowVomit::CScareCrowVomit(CMonster* _pOwner)
	: m_pOwner(_pOwner)
	, m_fSpeed(200.f)
	, m_fDegree(0.f)
	, m_fTime(0.f)
	, m_iDmg(0)
	, m_sound(nullptr)
{
	CreateAnimator();
	CreateCollider();
	GetCollider()->SetScale(Vec2(60.f, 60.f));
	if (m_pOwner->GetMonInfo().m_bIsLeft) m_fDegree = 180.f;
	else if(m_pOwner->GetMonInfo().m_bIsLeft == false) m_fDegree = 0.f;
	m_iDmg = m_pOwner->GetMonInfo().m_fAtt;
	CTexture* pPoison = CResMgr::GetInst()->LoadTexture(L"poison", L"texture\\fx\\poison.bmp");
	m_sound = CResMgr::GetInst()->LoadSound(L"scarecrow_shoot", L"sound\\monster\\enemy_mermaid_shoot_bubbles.wav");
	m_sound->SetVolume(40);
	m_sound->Play();

	/*GetAnimator()->CreateAnimation(L"poison", pPoison, Vec2(16.f, 52.f), Vec2(60.f, 60.f), Vec2(0.f, 0.f), Vec2(0.f, 0.f), 4, 1, 4, 0.1f);
	GetAnimator()->FindAnimation(L"poison")->Save(L"animation\\fx\\poison.anim");*/

	GetAnimator()->LoadAnimation(L"animation\\fx\\poison.anim");
}

CScareCrowVomit::~CScareCrowVomit()
{
}


void CScareCrowVomit::tick()
{
	Vec2 vPos = GetPos();
	GetAnimator()->Play(L"poison", true);
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

void CScareCrowVomit::render(HDC _dc)
{
	CObj::render(_dc);
}

void CScareCrowVomit::BeginOverlap(CCollider* _pOther)
{
	CPlayer* cPlayer = dynamic_cast<CPlayer*>(_pOther->GetOwner());
	if(nullptr != cPlayer) {
		SetDead();
	}
	return;
}


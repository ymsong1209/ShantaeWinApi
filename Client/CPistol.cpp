#include "pch.h"
#include "CPistol.h"
#include "CPistolImpact.h"

#include "CTimeMgr.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CResMgr.h"
#include "CSound.h"

#include "CPlayer.h"
#include "CMonster.h"
#include "CPot.h"
#include "CWall.h"
#include "CImpact_Small.h"

CPistol::CPistol(CPlayer* _pOwner)
	: m_pOwner(_pOwner)
	, m_fSpeed(2000.f)
	, m_fDegree(0.f)
	, m_fTime(0.f)
	, m_iDmg(0)
	, m_iExtraDmg(0)
{
	CreateCollider();
	CreateAnimator();
	GetCollider()->SetScale(Vec2(20.f, 20.f));
	CSound* pistol = CResMgr::GetInst()->LoadSound(L"pistol", L"sound\\player\\player_risky_shoot_pistol.wav");
	pistol->SetVolume(25);
	pistol->Play();
	m_iDmg = m_pOwner->ReturnPistolDmg();
	bool extra = m_pOwner->ReturnIsMonsterMilk();
	if (extra) {
		m_iExtraDmg = m_pOwner->ReturnPistolExtraDmg();
	}
	CTexture* pFxTex_L = CResMgr::GetInst()->LoadTexture(L"fx_L", L"texture\\fx\\fx_L.bmp");

	GetAnimator()->CreateAnimation(L"Pistol_Bullet_Idle", pFxTex_L, Vec2(3.f, 4434.f), Vec2(24.f, 24.f), Vec2(0.f, 0.f), Vec2(3.f, 0.f), 3, 1, 3, 0.1f);
	GetAnimator()->FindAnimation(L"Pistol_Bullet_Idle")->Save(L"animation\\fx\\Pistol_Bullet_Idle.anim");
	
	GetAnimator()->LoadAnimation(L"animation\\fx\\Pistol_Bullet_Idle.anim");

}

CPistol::~CPistol()
{
}
void CPistol::tick()
{
	Vec2 vPos = GetPos();
	GetAnimator()->Play(L"Pistol_Bullet_Idle", true);
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

void CPistol::render(HDC _dc)
{
	/*Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vSize = GetScale();
	Ellipse(_dc, (int)(vPos.x - vSize.x / 2.f)
		, (int)(vPos.y - vSize.y / 2.f)
		, (int)(vPos.x + vSize.x / 2.f)
		, (int)(vPos.y + vSize.y / 2.f));*/
	CObj::render(_dc);
}

void CPistol::BeginOverlap(CCollider* _pOther)
{
	
	CMonster* cMonster = dynamic_cast<CMonster*>(_pOther->GetOwner());
	if (nullptr != cMonster) {
		//shoot right
		if (m_fDegree == 180.f) {
			CImpact_Small* pImpact_Small = new CImpact_Small();
			Instantiate(pImpact_Small, GetPos(), LAYER::DAMAGE);
			CPistolImpact* pImpact = new CPistolImpact(PLAYER_DIR::RIGHT);
			Instantiate(pImpact, GetPos(), LAYER::DEATH_LEFTOVER);
			SetDead();
			return;
		}
		//shoot left
		else if (m_fDegree == 0.f) {
			CImpact_Small* pImpact_Small = new CImpact_Small();
			Instantiate(pImpact_Small, GetPos(), LAYER::DAMAGE);
			CPistolImpact* pImpact = new CPistolImpact(PLAYER_DIR::LEFT);
			Instantiate(pImpact, GetPos(), LAYER::DEATH_LEFTOVER);
			SetDead();
			return;
		}
		
	}

	CWall* cWall = dynamic_cast<CWall*>(_pOther->GetOwner());
	if (nullptr != cWall) {
		//shoot right
		if (m_fDegree == 180.f) {
			CPistolImpact* pImpact = new CPistolImpact(PLAYER_DIR::RIGHT);
			Instantiate(pImpact, GetPos(), LAYER::DEATH_LEFTOVER);
			SetDead();
			return;
		}
		//shoot left
		else if (m_fDegree == 0.f) {
			CPistolImpact* pImpact = new CPistolImpact(PLAYER_DIR::LEFT);
			Instantiate(pImpact, GetPos(), LAYER::DEATH_LEFTOVER);
			SetDead();
			return;
		}

	}

	CPot* cPot = dynamic_cast<CPot*>(_pOther->GetOwner());
	if (nullptr != cPot) {
		//shoot right
		if (m_fDegree == 180.f) {
			CPistolImpact* pImpact = new CPistolImpact(PLAYER_DIR::RIGHT);
			Instantiate(pImpact, GetPos(), LAYER::DEATH_LEFTOVER);
			SetDead();
			return;
		}
		//shoot left
		else if (m_fDegree == 0.f) {
			CPistolImpact* pImpact = new CPistolImpact(PLAYER_DIR::LEFT);
			Instantiate(pImpact, GetPos(), LAYER::DEATH_LEFTOVER);
			SetDead();
			return;
		}

	}

	
}
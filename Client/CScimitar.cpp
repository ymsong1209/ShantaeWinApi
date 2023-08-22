#include "pch.h"
#include "CScimitar.h"
#include "CMonster.h"
#include "CRigidbody.h"
#include "CCollider.h"
#include "CTimeMgr.h"
#include "CPlayer.h"
#include "CPlatform.h"
#include "CImpact_Big.h"
#include "CSound.h"
#include "CResMgr.h"


CScimitar::CScimitar(CPlayer* _pOwner)
	: m_pOwner(_pOwner)
	, m_fTime(0.f)
	, m_pAnim(PLAYER_ANIM::NONE)
	, m_iDmg(0)
	, m_iExtraDmg(0)
{
	CreateCollider();
	m_iDmg = m_pOwner->ReturScimitarDmg();
	bool extra = m_pOwner->ReturnIsMonsterMilk();
	if (extra) {
		m_iExtraDmg = m_pOwner->ReturScimitarExtraDmg();
	}
	PLAYER_DIR EPDir = GetOwner()->ReturnDir();
	PLAYER_ANIM EPAnim = GetOwner()->ReturnAnim();

	GetCollider()->SetScale(Vec2(28.f, 46.f));
	//GetCollider()->SetOffsetPos(Vec2(0.f, GetCollider()->GetScale().y / 2));
}


CScimitar::~CScimitar()
{

}

void CScimitar::tick()
{
	
	//플레이어 anim이 scimitar가 아닐 경우 setdead();
	// ,피격 상태이여도 사라져야함
	m_pAnim = GetOwner()->ReturnAnim();
	m_pState = GetOwner()->ReturnState();
	if (m_pAnim != PLAYER_ANIM::SCIMITAR || m_pState == PLAYER_STATE::HIT) {
		SetDead();
	}

	Vec2 pos = GetOwner()->GetCollider()->GetFinalPos();
	Vec2 scale = GetOwner()->GetCollider()->GetScale();
	Vec2 prevpos = GetOwner()->GetPrevPos();
	Vec2 curpos = GetOwner()->GetPos();
	Vec2 diff = curpos - prevpos;

	//공격 도중 이동을 하면 그에 맞게 scimitar도 이동해야함
	//SetPos(Vec2(pos.x + diff.x, pos.y + diff.y));
	SetPos(Vec2(pos.x, pos.y+scale.y/2 + GetCollider()->GetScale().y/2));

	
	CObj::tick();
}

void CScimitar::render(HDC _dc)
{

	CObj::render(_dc);
}

void CScimitar::BeginOverlap(CCollider* _pOther)
{
	CMonster* mMonster = dynamic_cast<CMonster*>(_pOther->GetOwner());
	if (nullptr != mMonster) {
		CSound* scimitar = CResMgr::GetInst()->LoadSound(L"Scimitar", L"sound\\player\\object_starfish_fire.wav");
		scimitar->Play();
		GetOwner()->GetRigidbody()->SetVelocity(Vec2(0.f, -500.f));
		CImpact_Big* impact = new CImpact_Big;
		Instantiate(impact, GetPos(), LAYER::DEATH_LEFTOVER);
	}
	

	CPlatform* mPlatform = dynamic_cast<CPlatform*>(_pOther->GetOwner());
	if (nullptr != mPlatform) {
		Vec2 PlayerPos = GetOwner()->GetPos();
		GetOwner()->SetPos(Vec2(PlayerPos.x, PlayerPos.y + GetCollider()->GetScale().y));
		SetDead();
	}
}
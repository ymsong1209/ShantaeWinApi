#include "pch.h"
#include "CWhip.h"
#include "CMonster.h"
#include "CRigidbody.h"
#include "CCollider.h"
#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CPlayer.h"
#include "CSound.h"
#include "CImpact_Big.h"


CWhip::CWhip(CPlayer* _pOwner)
	: m_pOwner(_pOwner)
	, m_fTime(0.f)
	, m_iDmg(0)
	, m_iExtraDmg(0)
{
	CreateCollider();
	m_iDmg = m_pOwner->ReturnWhipDmg();
	bool extra = m_pOwner->ReturnIsMonsterMilk();
	if (extra) {
		m_iExtraDmg = m_pOwner->ReturnWhipExtraDmg();
	}
	PLAYER_DIR EPDir = GetOwner()->ReturnDir();
	PLAYER_ANIM EPrevAnim = GetOwner()->ReturnPrevAnim();
	if (EPrevAnim == PLAYER_ANIM::IDLE||EPrevAnim == PLAYER_ANIM::RUN||EPrevAnim==PLAYER_ANIM::LAND) {
		if (EPDir == PLAYER_DIR::LEFT) {
			GetCollider()->SetScale(Vec2(182.f, 42.f));
			GetCollider()->SetOffsetPos(Vec2(-GetCollider()->GetScale().x / 2, -GetCollider()->GetScale().y / 2));
		}
		else if (EPDir == PLAYER_DIR::RIGHT) {
			GetCollider()->SetScale(Vec2(182.f, 42.f));
			GetCollider()->SetOffsetPos(Vec2(GetCollider()->GetScale().x / 2, -GetCollider()->GetScale().y / 2));
		}
	}
	else if (EPrevAnim == PLAYER_ANIM::DUCK) {
		if (EPDir == PLAYER_DIR::LEFT) {
			GetCollider()->SetScale(Vec2(170.f, 26.f));
			GetCollider()->SetOffsetPos(Vec2(-GetCollider()->GetScale().x / 2, -GetCollider()->GetScale().y / 2));
		}
		else if (EPDir == PLAYER_DIR::RIGHT) {
			GetCollider()->SetScale(Vec2(170.f, 26.f));
			GetCollider()->SetOffsetPos(Vec2(GetCollider()->GetScale().x / 2, -GetCollider()->GetScale().y / 2));
		}
	}
	else if (EPrevAnim == PLAYER_ANIM::JUMP|| EPrevAnim == PLAYER_ANIM::FALL|| EPrevAnim == PLAYER_ANIM::HAT) {
		if (EPDir == PLAYER_DIR::LEFT) {
			GetCollider()->SetScale(Vec2(182.f, 42.f));
			GetCollider()->SetOffsetPos(Vec2(-GetCollider()->GetScale().x / 2, -GetCollider()->GetScale().y / 2));
		}
		else if (EPDir == PLAYER_DIR::RIGHT) {
			GetCollider()->SetScale(Vec2(182.f, 42.f));
			GetCollider()->SetOffsetPos(Vec2(GetCollider()->GetScale().x / 2, -GetCollider()->GetScale().y / 2));
		}
	}

	/*CSound* whipsound = CResMgr::GetInst()->LoadSound(L"Whip_03", L"sound\\player\\player_hair_whip_normal_03.wav");
	whipsound->SetVolume(25);
	whipsound->Play();*/
	//srand((UINT)CTimeMgr::GetInst()->ReturnCurCount());
	if (rand() % 3 + 1 == 1) {
		CSound* whipsound = CResMgr::GetInst()->LoadSound(L"Whip_01", L"sound\\player\\player_hair_whip_normal.wav");
		whipsound->SetVolume(25);
		whipsound->Play();
	}
	else if (rand() % 3 + 1 == 2) {
		CSound* whipsound = CResMgr::GetInst()->LoadSound(L"Whip_02", L"sound\\player\\player_hair_whip_normal_02.wav");
		whipsound->SetVolume(25);
		whipsound->Play();
	}
	else if (rand() % 3  + 1 == 3) {
		CSound* whipsound = CResMgr::GetInst()->LoadSound(L"Whip_03", L"sound\\player\\player_hair_whip_normal_03.wav");
		whipsound->SetVolume(25);
		whipsound->Play();
	}
	else {
		CSound* whipsound = CResMgr::GetInst()->LoadSound(L"Whip_03", L"sound\\player\\player_hair_whip_normal_03.wav");
		whipsound->SetVolume(25);
		whipsound->Play();
	}
	
}


CWhip::~CWhip()
{

}

void CWhip::tick()
{
	Vec2 pos = GetPos();

	Vec2 prevpos = GetOwner()->GetPrevPos();
	Vec2 curpos = GetOwner()->GetPos();
	Vec2 diff = curpos - prevpos;

	//공격 도중 이동을 하면 그에 맞게 whip도 이동해야함
	SetPos(Vec2(pos.x + diff.x, pos.y + diff.y));
	
	m_fTime += DT;
	if (0.5f < m_fTime) {
		SetDead();
	}
	CObj::tick();
}

void CWhip::render(HDC _dc)
{

	CObj::render(_dc);
}

void CWhip::BeginOverlap(CCollider* _pOther)
{
	CMonster* mMonster = dynamic_cast<CMonster*>(_pOther->GetOwner());
	if (nullptr != mMonster) {
		CImpact_Big* impact = new CImpact_Big;
		Vec2 WhipPos = GetCollider()->GetFinalPos();
		Vec2 MonPos = mMonster->GetCollider()->GetFinalPos();
		if (WhipPos.x < MonPos.x) {
			Vec2 pos = Vec2(MonPos.x - (MonPos.x - WhipPos.x) / 2, WhipPos.y);
			Instantiate(impact, pos, LAYER::DEATH_LEFTOVER);
		}
		else{
			Vec2 pos = Vec2(WhipPos.x - (WhipPos.x-MonPos.x) / 2, WhipPos.y);
			Instantiate(impact, pos, LAYER::DEATH_LEFTOVER);
		}
		
	}
		return;
}
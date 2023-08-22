#include "pch.h"
#include "CMonster.h"

#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "CPlayer.h"
#include "CCollider.h"
#include "CFSM.h"
#include "CIdleState.h"
#include "CTraceState.h"
#include "CAnimator.h"
#include "CKeyMgr.h"
#include "CAnimation.h"

#include "CWhip.h"
#include "CPistol.h"
#include "CScimitar.h"
#include "CPikeBall.h"
#include "CDamage.h"

CMonster::CMonster()
	: m_pTarget(nullptr)
	, m_pTex(nullptr)
	, m_tInfo{}
	, m_vSpawnPos{}
{	
	
	CreateAnimator();
	CreateCollider();
	CreateRigidbody();
	CreateAI();

}

CMonster::~CMonster()
{
}

void CMonster::tick()
{
	// Á×À½ ÆÇÁ¤
	if (m_tInfo.m_iHP <= 0) {
		SetDead();
	}
	//GetAnimator()->Play(L"ScorpGal_Idle_R", true);
	
	/*if (IsValid(m_pTarget))
	{
		Vec2 vTargetPos = m_pTarget->GetPos();
		m_pTarget->SetName(L"Player");
		Vec2 vPos = GetPos();

		Vec2 vDir = vTargetPos - vPos;
		vDir.Normalize();

		vPos.x += vDir.x * 100.f * DT;
		vPos.y += vDir.y * 100.f * DT;

		SetPos(vPos);
	}
	else
	{

	}*/


	CObj::tick();
}

void CMonster::render(HDC _dc)
{
	CObj::render(_dc);
}

void CMonster::BeginOverlap(CCollider* _pOther)
{
	
	/*CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther->GetOwner());
	if (nullptr == pPlayer)
		return;*/

	CWhip* pWhip = dynamic_cast<CWhip*>(_pOther->GetOwner());
	if (nullptr != pWhip) {
		m_tInfo.m_iHP -= (pWhip->ReturnWhipDmg() + pWhip->ReturnWhipExtraDmg());
		CObj* cDamage = new CDamage(pWhip->ReturnWhipDmg(), false);
		Vec2 DamagePos = Vec2(GetPos().x, GetPos().y - GetCollider()->GetScale().y);
		Vec2 Damage2Pos = Vec2(DamagePos.x + 15, DamagePos.y);
		CObj* cDamage2 = new CDamage(pWhip->ReturnWhipExtraDmg(), true);
		Instantiate(cDamage, DamagePos, LAYER::DAMAGE);
		Instantiate(cDamage2, Damage2Pos, LAYER::DAMAGE);
	}

	CPistol* pPistol = dynamic_cast<CPistol*>(_pOther->GetOwner());
	if (nullptr != pPistol) {
		m_tInfo.m_iHP -= (pPistol->ReturnPistolDmg() + pPistol->ReturnPistolExtraDmg());
		CObj* cDamage = new CDamage(pPistol->ReturnPistolDmg(), false);
		Vec2 DamagePos = Vec2(GetPos().x, GetPos().y - GetCollider()->GetScale().y);
		Vec2 Damage2Pos = Vec2(DamagePos.x + 15, DamagePos.y);
		CObj* cDamage2 = new CDamage(pPistol->ReturnPistolExtraDmg(), true);
		Instantiate(cDamage, DamagePos, LAYER::DAMAGE);
		Instantiate(cDamage2, Damage2Pos, LAYER::DAMAGE);
	}
	CScimitar* pScimitar = dynamic_cast<CScimitar*>(_pOther->GetOwner());
	if (nullptr != pScimitar) {
		m_tInfo.m_iHP -= (pScimitar->ReturnScimitarDmg() + pScimitar->ReturnScimitarExtraDmg());
		CObj* cDamage = new CDamage(pScimitar->ReturnScimitarDmg(), false);
		Vec2 DamagePos = Vec2(GetPos().x, GetPos().y - GetCollider()->GetScale().y);
		Vec2 Damage2Pos = Vec2(DamagePos.x + 15, DamagePos.y);
		CObj* cDamage2 = new CDamage(pScimitar->ReturnScimitarExtraDmg(), true);
		Instantiate(cDamage, DamagePos, LAYER::DAMAGE);
		Instantiate(cDamage2, Damage2Pos, LAYER::DAMAGE);
	}
	
	CPikeBall* pPikeBall = dynamic_cast<CPikeBall*>(_pOther->GetOwner());
	if (nullptr != pPikeBall) {
		m_tInfo.m_iHP -= (pPikeBall->ReturnPikeBallDmg());
		CObj* cDamage = new CDamage(pPikeBall->ReturnPikeBallDmg(), false);
		Vec2 DamagePos = Vec2(GetPos().x, GetPos().y - GetCollider()->GetScale().y);
		
		Instantiate(cDamage, DamagePos, LAYER::DAMAGE);
		
	}
	
}

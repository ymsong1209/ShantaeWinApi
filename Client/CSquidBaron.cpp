#include "pch.h"
#include "CSquidBaron.h"
#include "CCollider.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CRigidbody.h"
#include "CResMgr.h"
#include "CWall.h"
#include "CWhip.h"
#include "CPistol.h"
#include "CScimitar.h"
#include "CPikeBall.h"
#include "CDamage.h"
#include "CSound.h"

#include "CSquidAttackState.h"
#include "CSquidIdleState.h"
#include "CSquidJumpState.h"
#include "CSquidBuildUpState.h"
#include "CSquidArmorUpState.h"
#include "CSquidGobbleState.h"
#include "CSquidPhase2State.h"
#include "CSquidArmorBreakState.h"
#include "CSquidDeadState.h"



CSquidBaron::CSquidBaron()
	: m_fBuildUpCooltime(0.f)
	, SquidBaron_L(nullptr)
	, SquidBaron_R(nullptr)
{
	m_tInfo.m_iHP = 80;
	m_tInfo.m_iMaxHP = 80;
	m_tInfo.m_bIsLeft = true;
	m_tInfo.m_fAtt = 1;
	m_tInfo.m_bIsPhase1 = true;
	m_tInfo.m_bIsArmored = false;
	m_tInfo.m_iWallHit = 0;
	m_tInfo.m_bBannerSpawn = false;
	m_tInfo.m_iGobbleCount = 0;
	m_tInfo.m_fTime = 0.f;
	m_tInfo.m_fAttackFinalDist = 0.f;
	m_tInfo.m_bJumpPoint1 = false;
	m_tInfo.m_bJumpPoint2 = false;
	m_tInfo.m_bJumpPoint3 = false;
	m_tInfo.m_bDeathIntensify = false;

	/*SquidBaron_L = CResMgr::GetInst()->LoadTexture(L"SquidBaron_L", L"texture\\monster\\SquidBaron_L.bmp");
	SquidBaron_R = CResMgr::GetInst()->LoadTexture(L"SquidBaron_R", L"texture\\monster\\SquidBaron_R.bmp");*/
	//SquidBaron_L = CResMgr::GetInst()->FindTexture(L"SquidBaron_L");
	//SquidBaron_R = CResMgr::GetInst()->FindTexture(L"SquidBaron_R");
	LoadSquidBaronAnimation();
	GetAnimator()->SetFloorPlay(true);
	GetRigidbody()->SetGravity(true);
	GetRigidbody()->SetGravityAccel(300.f);
	GetRigidbody()->SetGravityVelocityLimit(1000.f);

	GetAI()->AddState(L"Idle", new CSquidIdleState);
	GetAI()->AddState(L"Attack", new CSquidAttackState);
	GetAI()->AddState(L"BuildUp", new CSquidBuildUpState);
	GetAI()->AddState(L"Jump", new CSquidJumpState);
	GetAI()->AddState(L"Gobble", new CSquidGobbleState);
	GetAI()->AddState(L"ArmorUp", new CSquidArmorUpState);
	GetAI()->AddState(L"Armor_Break", new CSquidArmorBreakState);
	GetAI()->AddState(L"Phase2", new CSquidPhase2State);
	GetAI()->AddState(L"Dead", new CSquidDeadState);

	GetAI()->ChangeState(L"Idle");
	
}

CSquidBaron::~CSquidBaron()
{
}


void CSquidBaron::tick()
{	
	if (m_tInfo.m_bIsPhase1 == true && m_tInfo.m_iHP < 60) {
		GetAI()->ChangeState(L"Phase2");
	}
	if (m_tInfo.m_iHP < 0&& !IsDead()) {
		GetAI()->ChangeState(L"Dead");
	}
	CObj::tick();
}

void CSquidBaron::render(HDC _dc)
{
	CObj::render(_dc);
}

void CSquidBaron::BeginOverlap(CCollider* _pOther)
{
	//벽에 부딪힐 경우 Position을 반대로
	CWall* pWall = dynamic_cast<CWall*>(_pOther->GetOwner());
	if (pWall != nullptr) {
		CSound* sound = CResMgr::GetInst()->LoadSound(L"wallimpact", L"sound\\monster\\baron_wallimpact.wav");
		sound->Play();
		m_tInfo.m_bIsLeft = !m_tInfo.m_bIsLeft;
		++m_tInfo.m_iWallHit;
	}

	//Whip에 맞을 경우
	CWhip* pWhip = dynamic_cast<CWhip*>(_pOther->GetOwner());
	if (nullptr != pWhip) {
		if (m_tInfo.m_bIsArmored == true) {
			CObj* cDamage = new CDamage(0, false);
			Vec2 DamagePos = Vec2(GetPos().x, GetPos().y - GetCollider()->GetScale().y);
			Vec2 Damage2Pos = Vec2(DamagePos.x + 15, DamagePos.y);
			CObj* cDamage2 = new CDamage(0, true);
			Instantiate(cDamage, DamagePos, LAYER::DAMAGE);
			Instantiate(cDamage2, Damage2Pos, LAYER::DAMAGE);
		}
		else {
			m_tInfo.m_iHP -= (pWhip->ReturnWhipDmg() + pWhip->ReturnWhipExtraDmg());
			CObj* cDamage = new CDamage(pWhip->ReturnWhipDmg(), false);
			Vec2 DamagePos = Vec2(GetPos().x, GetPos().y - GetCollider()->GetScale().y);
			Vec2 Damage2Pos = Vec2(DamagePos.x + 15, DamagePos.y);
			CObj* cDamage2 = new CDamage(pWhip->ReturnWhipExtraDmg(), true);
			Instantiate(cDamage, DamagePos, LAYER::DAMAGE);
			Instantiate(cDamage2, Damage2Pos, LAYER::DAMAGE);
		}
	}
	//Pistol에 맞을 경우
	CPistol* pPistol = dynamic_cast<CPistol*>(_pOther->GetOwner());
	if (nullptr != pPistol) {
		if (m_tInfo.m_bIsArmored == true) {
			CObj* cDamage = new CDamage(0, false);
			Vec2 DamagePos = Vec2(GetPos().x, GetPos().y - GetCollider()->GetScale().y);
			Vec2 Damage2Pos = Vec2(DamagePos.x + 15, DamagePos.y);
			CObj* cDamage2 = new CDamage(0, true);
			Instantiate(cDamage, DamagePos, LAYER::DAMAGE);
			Instantiate(cDamage2, Damage2Pos, LAYER::DAMAGE);
		}
		else {
			m_tInfo.m_iHP -= (pPistol->ReturnPistolDmg() + pPistol->ReturnPistolExtraDmg());
			CObj* cDamage = new CDamage(pPistol->ReturnPistolDmg(), false);
			Vec2 DamagePos = Vec2(GetPos().x, GetPos().y - GetCollider()->GetScale().y);
			Vec2 Damage2Pos = Vec2(DamagePos.x + 15, DamagePos.y);
			CObj* cDamage2 = new CDamage(pPistol->ReturnPistolExtraDmg(), true);
			Instantiate(cDamage, DamagePos, LAYER::DAMAGE);
			Instantiate(cDamage2, Damage2Pos, LAYER::DAMAGE);
		}
		
	}
	//Scimitar에 맞을 경우
	CScimitar* pScimitar = dynamic_cast<CScimitar*>(_pOther->GetOwner());
	if (nullptr != pScimitar) {
		if (m_tInfo.m_bIsArmored == true) {
			GetAI()->ChangeState(L"Armor_Break");
			CObj* cDamage = new CDamage(0, false);
			Vec2 DamagePos = Vec2(GetPos().x, GetPos().y - GetCollider()->GetScale().y);
			Vec2 Damage2Pos = Vec2(DamagePos.x + 15, DamagePos.y);
			CObj* cDamage2 = new CDamage(0, true);
			Instantiate(cDamage, DamagePos, LAYER::DAMAGE);
			Instantiate(cDamage2, Damage2Pos, LAYER::DAMAGE);
		}
		else {
			m_tInfo.m_iHP -= (pScimitar->ReturnScimitarDmg() + pScimitar->ReturnScimitarExtraDmg());
			CObj* cDamage = new CDamage(pScimitar->ReturnScimitarDmg(), false);
			Vec2 DamagePos = Vec2(GetPos().x, GetPos().y - GetCollider()->GetScale().y);
			Vec2 Damage2Pos = Vec2(DamagePos.x + 15, DamagePos.y);
			CObj* cDamage2 = new CDamage(pScimitar->ReturnScimitarExtraDmg(), true);
			Instantiate(cDamage, DamagePos, LAYER::DAMAGE);
			Instantiate(cDamage2, Damage2Pos, LAYER::DAMAGE);
		}
		
	}

	CPikeBall* pPikeBall = dynamic_cast<CPikeBall*>(_pOther->GetOwner());
	if (nullptr != pPikeBall) {
		if (m_tInfo.m_bIsArmored == true) {
			CObj* cDamage = new CDamage(0, false);
			Vec2 DamagePos = Vec2(GetPos().x, GetPos().y - GetCollider()->GetScale().y);
			Instantiate(cDamage, DamagePos, LAYER::DAMAGE);
		}
		else {
			m_tInfo.m_iHP -= (pPikeBall->ReturnPikeBallDmg());
			CObj* cDamage = new CDamage(pPikeBall->ReturnPikeBallDmg(), false);
			Vec2 DamagePos = Vec2(GetPos().x, GetPos().y - GetCollider()->GetScale().y);
			Instantiate(cDamage, DamagePos, LAYER::DAMAGE);
		}
	}
}


void CSquidBaron::LoadSquidBaronAnimation()
{
	//SquidBaron_L =  CResMgr::GetInst()->LoadTexture(L"SquidBaron_L", L"texture\\monster\\SquidBaron_L.bmp");
	//SquidBaron_R = CResMgr::GetInst()->LoadTexture(L"SquidBaron_R", L"texture\\monster\\SquidBaron_R.bmp");
	CTexture* SquidBaron_L = CResMgr::GetInst()->LoadTexture(L"SquidBaron_L", L"texture\\monster\\SquidBaron_L.bmp");
	CTexture* SquidBaron_R = CResMgr::GetInst()->LoadTexture(L"SquidBaron_R", L"texture\\monster\\SquidBaron_R.bmp");
	

	
	/*GetAnimator()->CreateAnimation(L"SquidBaron_BuildUp_L", SquidBaron_L, Vec2(3.f, 396.f), Vec2(240.f, 171.f), Vec2(0.f, 0.f), Vec2(3.f, 0.f), 4, 1, 4, 0.1f);
	GetAnimator()->FindAnimation(L"SquidBaron_BuildUp_L")->Save(L"animation\\monster\\SquidBaron_BuildUp_L.anim");
	GetAnimator()->CreateAnimation(L"SquidBaron_BuildUp_R", SquidBaron_R, Vec2(3.f, 396.f), Vec2(240.f, 171.f), Vec2(0.f, 0.f), Vec2(3.f, 0.f), 4, 1, 4, 0.1f);
	GetAnimator()->FindAnimation(L"SquidBaron_BuildUp_R")->Save(L"animation\\monster\\SquidBaron_BuildUp_R.anim");

	GetAnimator()->CreateAnimation(L"SquidBaron_Food", SquidBaron_R, Vec2(3.f, 891.f), Vec2(93.f, 69.f), Vec2(0.f, 0.f), Vec2(3.f, 0.f), 9, 1, 9, 0.1f);
	GetAnimator()->FindAnimation(L"SquidBaron_Food")->Save(L"animation\\monster\\SquidBaron_Food.anim");

	GetAnimator()->CreateAnimation(L"SquidBaron_Gobble", SquidBaron_R, Vec2(3.f, 1263.f), Vec2(180.f, 201.f), Vec2(0.f, 21.f), Vec2(3.f, 0.f), 8, 1, 8, 0.1f);
	GetAnimator()->FindAnimation(L"SquidBaron_Gobble")->Save(L"animation\\monster\\SquidBaron_Gobble.anim");

	GetAnimator()->CreateAnimation(L"SquidBaron_Grunt", SquidBaron_R, Vec2(3.f, 1536.f), Vec2(180.f, 171.f), Vec2(0.f, 0.f), Vec2(3.f, 0.f), 3, 1, 3, 0.1f);
	GetAnimator()->FindAnimation(L"SquidBaron_Grunt")->Save(L"animation\\monster\\SquidBaron_Grunt.anim");

	GetAnimator()->CreateAnimation(L"SquidBaron_Jump1", SquidBaron_R, Vec2(3.f, 1773.f), Vec2(207.f, 210.f), Vec2(0.f, 0.f), Vec2(3.f, 0.f), 3, 1, 3, 0.1f);
	GetAnimator()->FindAnimation(L"SquidBaron_Jump1")->Save(L"animation\\monster\\SquidBaron_Jump1.anim");
	GetAnimator()->CreateAnimation(L"SquidBaron_Jump2", SquidBaron_R, Vec2(633.f, 1773.f), Vec2(207.f, 219.f), Vec2(0.f, 0.f), Vec2(3.f, 0.f), 3, 1, 3, 0.1f);
	GetAnimator()->FindAnimation(L"SquidBaron_Jump2")->Save(L"animation\\monster\\SquidBaron_Jump2.anim");
	GetAnimator()->CreateAnimation(L"SquidBaron_Jump3", SquidBaron_R, Vec2(1263.f, 1773.f), Vec2(207.f, 210.f), Vec2(0.f, 0.f), Vec2(3.f, 0.f), 5, 1, 5, 0.1f);
	GetAnimator()->FindAnimation(L"SquidBaron_Jump3")->Save(L"animation\\monster\\SquidBaron_Jump3.anim");

	GetAnimator()->CreateAnimation(L"SquidBaron_Sparkle", SquidBaron_R, Vec2(3.f, 2508.f), Vec2(345.f, 171.f), Vec2(0.f, 0.f), Vec2(3.f, 0.f), 3, 1, 3, 0.1f);
	GetAnimator()->FindAnimation(L"SquidBaron_Sparkle")->Save(L"animation\\monster\\SquidBaron_Sparkle.anim");

	GetAnimator()->CreateAnimation(L"SquidBaron_Armor_Attack", SquidBaron_R, Vec2(3.f, 2745.f), Vec2(231.f, 171.f), Vec2(0.f, 0.f), Vec2(3.f, 0.f), 6, 1, 6, 0.1f);
	GetAnimator()->FindAnimation(L"SquidBaron_Armor_Attack")->Save(L"animation\\monster\\SquidBaron_Armor_Attack.anim");

	GetAnimator()->CreateAnimation(L"SquidBaron_Armor_Break", SquidBaron_R, Vec2(3.f, 2982.f), Vec2(519.f, 201.f), Vec2(0.f, 0.f), Vec2(3.f, 9.f), 34, 9, 4, 0.1f);
	GetAnimator()->FindAnimation(L"SquidBaron_Armor_Break")->Save(L"animation\\monster\\SquidBaron_Armor_Break.anim");

	GetAnimator()->CreateAnimation(L"SquidBaron_Armor_BuildUp_L", SquidBaron_L, Vec2(3.f, 4932.f), Vec2(240.f, 171.f), Vec2(0.f, 0.f), Vec2(3.f, 9.f), 4, 1, 4, 0.1f);
	GetAnimator()->FindAnimation(L"SquidBaron_Armor_BuildUp_L")->Save(L"animation\\monster\\SquidBaron_Armor_BuildUp_L.anim");
	GetAnimator()->CreateAnimation(L"SquidBaron_Armor_BuildUp_R", SquidBaron_R, Vec2(3.f, 4932.f), Vec2(240.f, 171.f), Vec2(0.f, 0.f), Vec2(3.f, 9.f), 4, 1, 4, 0.1f);
	GetAnimator()->FindAnimation(L"SquidBaron_Armor_BuildUp_R")->Save(L"animation\\monster\\SquidBaron_Armor_BuildUp_R.anim");

	GetAnimator()->CreateAnimation(L"SquidBaron_Armor_Idle_L", SquidBaron_L, Vec2(3.f, 5169.f), Vec2(186.f, 174.f), Vec2(0.f, 0.f), Vec2(3.f, 0.f), 4, 1, 4, 0.1f);
	GetAnimator()->FindAnimation(L"SquidBaron_Armor_Idle_L")->Save(L"animation\\monster\\SquidBaron_Armor_Idle_L.anim");
	GetAnimator()->CreateAnimation(L"SquidBaron_Armor_Idle_R", SquidBaron_R, Vec2(3.f, 5169.f), Vec2(186.f, 174.f), Vec2(0.f, 0.f), Vec2(3.f, 0.f), 4, 1, 4, 0.1f);
	GetAnimator()->FindAnimation(L"SquidBaron_Armor_Idle_R")->Save(L"animation\\monster\\SquidBaron_Armor_Idle_R.anim");

	GetAnimator()->CreateAnimation(L"SquidBaron_Armor_Jump1", SquidBaron_R, Vec2(3.f, 5409.f), Vec2(210.f, 210.f), Vec2(0.f, 9.f), Vec2(3.f, 0.f), 3, 1, 3, 0.1f);
	GetAnimator()->FindAnimation(L"SquidBaron_Armor_Jump1")->Save(L"animation\\monster\\SquidBaron_Armor_Jump1.anim");
	GetAnimator()->CreateAnimation(L"SquidBaron_Armor_Jump2", SquidBaron_R, Vec2(642.f, 5409.f), Vec2(210.f, 219.f), Vec2(0.f, 0.f), Vec2(3.f, 0.f), 3, 1, 3, 0.1f);
	GetAnimator()->FindAnimation(L"SquidBaron_Armor_Jump2")->Save(L"animation\\monster\\SquidBaron_Armor_Jump2.anim");
	GetAnimator()->CreateAnimation(L"SquidBaron_Armor_Jump3", SquidBaron_R, Vec2(1281.f, 5409.f), Vec2(210.f, 210.f), Vec2(0.f, 0.f), Vec2(3.f, 0.f), 5, 1, 5, 0.1f);
	GetAnimator()->FindAnimation(L"SquidBaron_Armor_Jump3")->Save(L"animation\\monster\\SquidBaron_Armor_Jump3.anim");

	GetAnimator()->CreateAnimation(L"SquidBaron_ArmorUp", SquidBaron_R, Vec2(3.f, 5697.f), Vec2(360.f, 363.f), Vec2(0.f, 0.f), Vec2(3.f, 12.f), 24, 4, 6, 0.1f);
	GetAnimator()->FindAnimation(L"SquidBaron_ArmorUp")->Save(L"animation\\monster\\SquidBaron_ArmorUp.anim");

	GetAnimator()->CreateAnimation(L"SquidBaron_Attack", SquidBaron_R, Vec2(3.f, 7749.f), Vec2(189.f, 171.f), Vec2(0.f, 0.f), Vec2(3.f, 12.f), 6, 1, 6, 0.1f);
	GetAnimator()->FindAnimation(L"SquidBaron_Attack")->Save(L"animation\\monster\\SquidBaron_Attack.anim");

	GetAnimator()->CreateAnimation(L"SquidBaron_Die", SquidBaron_R, Vec2(3.f, 633.f), Vec2(162.f, 195.f), Vec2(0.f, 0.f), Vec2(3.f, 12.f), 1, 1, 1, 2.0f);
	GetAnimator()->FindAnimation(L"SquidBaron_Die")->Save(L"animation\\monster\\SquidBaron_Die.anim");*/


	GetAnimator()->LoadAnimation(L"animation\\monster\\SquidBaron_BuildUp_L.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\SquidBaron_BuildUp_R.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\SquidBaron_Food.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\SquidBaron_Gobble.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\SquidBaron_Grunt.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\SquidBaron_Jump1.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\SquidBaron_Jump2.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\SquidBaron_Jump3.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\SquidBaron_Sparkle.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\SquidBaron_Armor_Attack.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\SquidBaron_Armor_Break.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\SquidBaron_Armor_BuildUp_L.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\SquidBaron_Armor_BuildUp_R.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\SquidBaron_Armor_Idle_R.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\SquidBaron_Armor_Jump1.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\SquidBaron_Armor_Jump2.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\SquidBaron_Armor_Jump3.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\SquidBaron_ArmorUp.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\SquidBaron_Attack.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\SquidBaron_Die.anim");

}

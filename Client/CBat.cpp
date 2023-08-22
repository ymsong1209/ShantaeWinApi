#include "pch.h"
#include "CBat.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"
#include "CRigidbody.h"
#include "CFSM.h"
#include "CIdleState.h"
#include "CTraceState.h"
#include "CAttackState.h"
#include "CHitState.h"
#include "CDeadState.h"
#include "CBatDeath.h"

#include "CTimeMgr.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CPlayer.h"

#include "CWhip.h"
#include "CPistol.h"
#include "CPikeBall.h"
#include "CScimitar.h"
#include "CSound.h"
CBat::CBat()
{
	m_tInfo.m_iMaxHP = 3;
	m_tInfo.m_iHP = 3;
	m_tInfo.m_fDetectRange = 500.f;
	m_tInfo.m_fAttRange = 200.f;
	m_tInfo.m_fAtt = 1;
	m_tInfo.m_fSpeed = 100.f;
	m_tInfo.m_bIsLeft = true;
	m_tInfo.m_iGemValue = 2;
	m_sTrace = CResMgr::GetInst()->LoadSound(L"bat_wing3", L"sound\\monster\\enemy_bat_wing_flap_03.wav");
	m_sAttack = CResMgr::GetInst()->LoadSound(L"bat_wing1", L"sound\\monster\\enemy_bat_wing_flap_01.wav");
	GetAnimator()->SetFloorPlay(true);
	GetRigidbody()->SetGravity(false);
	LoadBatAnimation();	
	GetAI()->AddState(L"Idle", new CIdleState);
	GetAI()->AddState(L"Trace", new CTraceState);
	GetAI()->AddState(L"Attack", new CAttackState);
	GetAI()->AddState(L"Hit", new CHitState);
	GetAI()->AddState(L"Dead", new CDeadState);

	GetAI()->ChangeState(L"Idle");

}

CBat::~CBat()
{
}



void CBat::tick()
{
	if (m_tInfo.m_iHP <= 0 && !IsDead()) {
		GetAI()->ChangeState(L"Dead");
	}
	CObj::tick();
	
}

void CBat::render(HDC _dc)
{
	CObj::render(_dc);
}

void CBat::BeginOverlap(CCollider* _pOther)
{
	CMonster::BeginOverlap(_pOther);
	if (GetAI()->ReturnState() != GetAI()->FindState(L"Hit")) {
		CWhip* pWhip = dynamic_cast<CWhip*>(_pOther->GetOwner());
		if (nullptr != pWhip) {
			GetAI()->ChangeState(L"Hit");
		}

		CPistol* pPistol = dynamic_cast<CPistol*>(_pOther->GetOwner());
		if (nullptr != pPistol) {
			GetAI()->ChangeState(L"Hit");
		}
		CScimitar* pScimitar = dynamic_cast<CScimitar*>(_pOther->GetOwner());
		if (nullptr != pScimitar) {
			GetAI()->ChangeState(L"Hit");
		}

		CPikeBall* pPikeBall = dynamic_cast<CPikeBall*>(_pOther->GetOwner());
		if (nullptr != pPikeBall) {
			GetAI()->ChangeState(L"Hit");
		}
	}
}



//----------Idle---------//
void CBat::idle_enter()
{
	m_tInfo.m_fSpeed = 100.f;
	if (m_tInfo.m_bIsLeft == true) {
		AdjustCollider(L"Bat_Idle_L", Vec2(45.f, 50.f), Vec2(31.f, 55.f));
		GetAnimator()->Play(L"Bat_Idle_L", true);
	}
	else {
		AdjustCollider(L"Bat_Idle_R", Vec2(45.f, 50.f), Vec2(31.f, 55.f));
		GetAnimator()->Play(L"Bat_Idle_R", true);
	}
	
}

void CBat::idle_exit()
{
}

//----------Trace-------//
void CBat::trace_enter()
{
	m_sTrace->Play(true);
	m_tInfo.m_fSpeed = 100.f;
	if (m_tInfo.m_bIsLeft == true) {
		AdjustCollider(L"Bat_AttackA_L", Vec2(45.f, 50.f), Vec2(31.f, 171.f));
		GetAnimator()->Play(L"Bat_AttackA_L", true);
	}
	else {
		AdjustCollider(L"Bat_AttackA_R", Vec2(45.f, 50.f), Vec2(31.f, 171.f));
		GetAnimator()->Play(L"Bat_AttackA_R", true);
	}
}


void CBat::trace_changeAnim()
{
	// Player 를 알아낸다.
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(pCurLevel->GetLayer(LAYER::PLAYER)[0]);
	
	//monster가 Player의 왼쪽에 있다 ->오른쪽을 봐야함
	if (GetPos().x < pPlayer->GetPos().x) {
		//monster가 Player의 왼쪽에 있는데 왼쪽을 바라보고 있음
		if (m_tInfo.m_bIsLeft == true) {
			AdjustCollider(L"Bat_AttackA_R", Vec2(45.f, 50.f), Vec2(31.f, 171.f));
			GetAnimator()->Play(L"Bat_AttackA_R", true);
			m_tInfo.m_bIsLeft = false;
		}
		//이미 오른쪽을 보고 있으면 굳이 안바꿔도 된다.
	}
	//monster가 Player의 오른쪽에 있다 -> 왼쪽을 봐야함
	else if (GetPos().x > pPlayer->GetPos().x) {
		if (m_tInfo.m_bIsLeft == false) {
			AdjustCollider(L"Bat_AttackA_L", Vec2(45.f, 50.f), Vec2(31.f, 171.f));
			GetAnimator()->Play(L"Bat_AttackA_L", true);
			m_tInfo.m_bIsLeft = true;
		}
		//이미 왼쪽을 보고 있으면 굳이 안바꿔도 된다.
	}
}

void CBat::trace_exit()
{
	m_sTrace->Stop(true);
}

//---------Attack---------//
void CBat::attack_enter()
{
	m_sAttack->Play(true);
	m_tInfo.m_fSpeed = 200.f;
	if (m_tInfo.m_bIsLeft == true) {
		AdjustCollider(L"Bat_AttackB_L", Vec2(46.f, 52.f), Vec2(33.f, 281.f));
		GetAnimator()->Play(L"Bat_AttackB_L", true);
	}
	else if(m_tInfo.m_bIsLeft == false) {
		AdjustCollider(L"Bat_AttackB_R", Vec2(46.f, 52.f), Vec2(33.f, 281.f));
		GetAnimator()->Play(L"Bat_AttackB_R", true);
	}
}
void CBat::attack()
{
	// Player 를 알아낸다.
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(pCurLevel->GetLayer(LAYER::PLAYER)[0]);

	assert(pPlayer);

	Vec2 vMonPos = GetPos();
	Vec2 vPlayerPos = pPlayer->GetPos();

	Vec2 vMonToPlayer = vPlayerPos - vMonPos;
	vMonToPlayer.Normalize();

	float fSpeed = m_tInfo.m_fSpeed;

	vMonPos += vMonToPlayer * DT * fSpeed;

	SetPos(vMonPos);
	//monster가 Player의 왼쪽에 있다 ->오른쪽을 봐야함
	if (GetPos().x < pPlayer->GetPos().x) {
		//현재 monster가 왼쪽을 바라보고 있는 상태
		if (m_tInfo.m_bIsLeft == true) {
			AdjustCollider(L"Bat_AttackB_R", Vec2(46.f, 52.f), Vec2(33.f, 281.f));
			GetAnimator()->Play(L"Bat_AttackB_R", true);
			m_tInfo.m_bIsLeft = false;
		}
		//이미 오른쪽을 보고 있으면 굳이 안바꿔도 된다.
	}
	//monster가 Player의 오른쪽에 있다 -> 왼쪽을 봐야함
	else if (GetPos().x > pPlayer->GetPos().x) {
		if (m_tInfo.m_bIsLeft == false) {
			AdjustCollider(L"Bat_AttackB_L", Vec2(46.f, 52.f), Vec2(33.f, 281.f));
			GetAnimator()->Play(L"Bat_AttackB_L", true);
			m_tInfo.m_bIsLeft = true;
		}
		//이미 왼쪽을 보고 있으면 굳이 안바꿔도 된다.
	}
	// Player 와 Monster 의 거리값을 계산
	float fDetectRange = m_tInfo.m_fDetectRange;
	// Player 가 탐지범위에서 벗어나면 Idle로 전환
	Vec2 vDir = GetPos() - pPlayer->GetPos();
	if (vDir.Length() > fDetectRange)
	{
		GetAI()->ChangeState(L"Idle");
	}
	// Player가 Attack범위 안에 있지만 Trace범위 내이면 Trace로 전환
	float fAttackRange = m_tInfo.m_fAttRange;
	if (fAttackRange < vDir.Length()&& vDir.Length() < fDetectRange)
	{
		GetAI()->ChangeState(L"Trace");
	}

}
void CBat::attack_exit()
{
	m_sAttack->Stop(true);
}

//----------Hit-------------//
void CBat::hit() {
	m_tInfo.m_fSpeed = 0.f;
	if (GetAnimator()->AnimationFinish(L"Bat_GetHit_L") || GetAnimator()->AnimationFinish(L"Bat_GetHit_R")) {
		GetAI()->ChangeState(L"Idle");
	}
	else {
		if (m_tInfo.m_bIsLeft == true) {
			AdjustCollider(L"Bat_GetHit_L", Vec2(53.f, 55.f), Vec2(39.f, 507.f));
			GetAnimator()->Play(L"Bat_GetHit_L", false);
		}
		else if (m_tInfo.m_bIsLeft == false) {
			AdjustCollider(L"Bat_GetHit_R", Vec2(53.f, 55.f), Vec2(39.f, 507.f));
			GetAnimator()->Play(L"Bat_GetHit_R", false);
		}
	}

	
}
void CBat::hit_exit() {
	GetAnimator()->AnimationReset(L"Bat_GetHit_R");
	GetAnimator()->AnimationReset(L"Bat_GetHit_L");
}
//----------Dead------------//

void CBat::dead()
{
	CObj* cBatdead = new CBatDeath(this);
	Instantiate(cBatdead, GetPos(), LAYER::DEATH_LEFTOVER);
	SetDead();
}


void CBat::LoadBatAnimation()
{
	CTexture* Bat_L = CResMgr::GetInst()->LoadTexture(L"Bat_L", L"texture\\monster\\Bat_L.bmp");
	CTexture* Bat_R = CResMgr::GetInst()->LoadTexture(L"Bat_R", L"texture\\monster\\Bat_R.bmp");
	

	//GetAnimator()->CreateAnimation(L"Bat_Idle_L", Bat_L, Vec2(6.f, 30.f), Vec2(108.f, 90.f), Vec2(0.f, 0.f), Vec2(6.f, 0.f), 5, 1, 5, 0.1f);
	//GetAnimator()->FindAnimation(L"Bat_Idle_L")->Save(L"animation\\monster\\Bat_Idle_L.anim");
	//GetAnimator()->CreateAnimation(L"Bat_Idle_R", Bat_R, Vec2(6.f, 30.f), Vec2(108.f, 90.f), Vec2(0.f, 0.f), Vec2(6.f, 0.f), 5, 1, 5, 0.1f);
	//GetAnimator()->FindAnimation(L"Bat_Idle_R")->Save(L"animation\\monster\\Bat_Idle_R.anim");
	//
	//GetAnimator()->CreateAnimation(L"Bat_AttackA_L", Bat_L, Vec2(6.f, 156.f), Vec2(108.f, 66.f), Vec2(0.f, 0.f), Vec2(6.f, 0.f), 2, 1, 2, 0.1f);
	//GetAnimator()->FindAnimation(L"Bat_AttackA_L")->Save(L"animation\\monster\\Bat_AttackA_L.anim");
	//GetAnimator()->CreateAnimation(L"Bat_AttackA_R", Bat_R, Vec2(6.f, 156.f), Vec2(108.f, 66.f), Vec2(0.f, 0.f), Vec2(6.f, 0.f), 2, 1, 2, 0.1f);
	//GetAnimator()->FindAnimation(L"Bat_AttackA_R")->Save(L"animation\\monster\\Bat_AttackA_R.anim");

	//GetAnimator()->CreateAnimation(L"Bat_AttackB_L", Bat_L, Vec2(6.f, 258.f), Vec2(108.f, 90.f), Vec2(0.f, 0.f), Vec2(6.f, 0.f), 12, 1, 12, 0.1f);
	//GetAnimator()->FindAnimation(L"Bat_AttackB_L")->Save(L"animation\\monster\\Bat_AttackB_L.anim");
	//GetAnimator()->CreateAnimation(L"Bat_AttackB_R", Bat_R, Vec2(6.f, 258.f), Vec2(108.f, 90.f), Vec2(0.f, 0.f), Vec2(6.f, 0.f), 12, 1, 12, 0.1f);
	//GetAnimator()->FindAnimation(L"Bat_AttackB_R")->Save(L"animation\\monster\\Bat_AttackB_R.anim");

	//GetAnimator()->CreateAnimation(L"Bat_GetHit_L", Bat_L, Vec2(6.f, 486.f), Vec2(108.f, 78.f), Vec2(0.f, 0.f), Vec2(6.f, 0.f), 5, 1, 5, 0.075f);
	//GetAnimator()->FindAnimation(L"Bat_GetHit_L")->Save(L"animation\\monster\\Bat_GetHit_L.anim");
	//GetAnimator()->CreateAnimation(L"Bat_GetHit_R", Bat_R, Vec2(6.f, 486.f), Vec2(108.f, 78.f), Vec2(0.f, 0.f), Vec2(6.f, 0.f), 5, 1, 5, 0.075f);
	//GetAnimator()->FindAnimation(L"Bat_GetHit_R")->Save(L"animation\\monster\\Bat_GetHit_R.anim");
	//


	GetAnimator()->LoadAnimation(L"animation\\monster\\Bat_Idle_L.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\Bat_Idle_R.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\Bat_AttackA_L.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\Bat_AttackA_R.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\Bat_AttackB_L.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\Bat_AttackB_R.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\Bat_GetHit_L.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\Bat_GetHit_R.anim");
}

#include "pch.h"
#include "CScareCrow.h"
#include "CResMgr.h"
#include "CTimeMgr.h"
#include "CAttackState.h"
#include "CIdleState.h"
#include "CTraceState.h"
#include "CHitState.h"
#include "CDeadState.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"
#include "CRigidbody.h"
#include "CMonster.h"
#include "CTexture.h"
#include "CPlayer.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CScareCrowDead.h"
#include "CWhip.h"
#include "CPikeBall.h"
#include "CPistol.h"
#include "CScimitar.h"
#include "CScareCrowVomit.h"
#include "CSound.h"
CScareCrow::CScareCrow()
  : m_fAttackCoolTime(0.f)
{
	m_tInfo.m_iHP = 20;
	m_tInfo.m_iMaxHP = 20;
	m_tInfo.m_fDetectRange = 800.f;
	m_tInfo.m_fAttRange = 300.f;
	m_tInfo.m_bIsLeft = true;
	m_tInfo.m_fAtt = 1;
	m_tInfo.m_iGemValue = 1;

	LoadScareCrowAnimation();
	GetAnimator()->SetFloorPlay(true);
	GetRigidbody()->SetGravity(true);
	GetRigidbody()->SetGravityAccel(300.f);
	GetRigidbody()->SetGravityVelocityLimit(1000.f);
	GetAI()->AddState(L"Idle", new CIdleState);
	GetAI()->AddState(L"Trace", new CTraceState);
	GetAI()->AddState(L"Attack", new CAttackState);
	GetAI()->AddState(L"Hit", new CHitState);
	GetAI()->AddState(L"Dead", new CDeadState);

	GetAI()->ChangeState(L"Idle");
}

CScareCrow::~CScareCrow()
{
}

void CScareCrow::tick()
{
	m_fAttackCoolTime += DT;
	if (m_tInfo.m_iHP <= 0 && !IsDead()) {
		GetAI()->ChangeState(L"Dead");
	}
	CObj::tick();
}

void CScareCrow::render(HDC _dc)
{
	CObj::render(_dc);
}

void CScareCrow::BeginOverlap(CCollider* _pOther)
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

void CScareCrow::idle_enter()
{
	m_tInfo.m_fSpeed = 100.f;
	if (m_tInfo.m_bIsLeft == true) {
		AdjustCollider(L"ScareCrow_Idle_L", Vec2(80.f, 160.f), Vec2(53.f, 46.f));
		GetAnimator()->Play(L"ScareCrow_Idle_L", true);
	}
	else {
		AdjustCollider(L"ScareCrow_Idle_R", Vec2(80.f, 160.f), Vec2(53.f, 46.f));
		GetAnimator()->Play(L"ScareCrow_Idle_R", true);
	}
}

void CScareCrow::idle()
{
	if (m_tInfo.m_bIsLeft == true) {
		AdjustCollider(L"ScareCrow_Idle_L", Vec2(80.f, 160.f), Vec2(53.f, 46.f));
		GetAnimator()->Play(L"ScareCrow_Idle_L", true);
	}
	else {
		AdjustCollider(L"ScareCrow_Idle_R", Vec2(80.f, 160.f), Vec2(53.f, 46.f));
		GetAnimator()->Play(L"ScareCrow_Idle_R", true);
	}
}

void CScareCrow::idle_exit()
{
}

void CScareCrow::trace_enter()
{
	m_tInfo.m_fSpeed = 100.f;
	if (m_tInfo.m_bIsLeft == true) {
		AdjustCollider(L"ScareCrow_Walk_L", Vec2(80.f, 160.f), Vec2(63.f, 281.f));
		GetAnimator()->Play(L"ScareCrow_Walk_L", true);
	}
	else {
		AdjustCollider(L"ScareCrow_Walk_R", Vec2(80.f, 160.f), Vec2(63.f, 281.f));
		GetAnimator()->Play(L"ScareCrow_Walk_R", true);
	}
}

void CScareCrow::trace_changeAnim()
{
	// Player 를 알아낸다.
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(pCurLevel->GetLayer(LAYER::PLAYER)[0]);

	//monster가 Player의 왼쪽에 있다 ->오른쪽을 봐야함
	if (GetPos().x < pPlayer->GetPos().x) {
		//monster가 Player의 왼쪽에 있는데 왼쪽을 바라보고 있음
		if (m_tInfo.m_bIsLeft == true) {
			AdjustCollider(L"ScareCrow_Walk_R", Vec2(80.f, 160.f), Vec2(63.f, 281.f));
			GetAnimator()->Play(L"ScareCrow_Walk_R", true);
			m_tInfo.m_bIsLeft = false;
		}
		//이미 오른쪽을 보고 있으면 굳이 안바꿔도 된다.
	}
	//monster가 Player의 오른쪽에 있다 -> 왼쪽을 봐야함
	else if (GetPos().x > pPlayer->GetPos().x) {
		if (m_tInfo.m_bIsLeft == false) {
			AdjustCollider(L"ScareCrow_Walk_L", Vec2(80.f, 160.f), Vec2(63.f, 281.f));
			GetAnimator()->Play(L"ScareCrow_Walk_L", true);
			m_tInfo.m_bIsLeft = true;
		}
		//이미 왼쪽을 보고 있으면 굳이 안바꿔도 된다.
	}
}

void CScareCrow::attack_enter()
{
	m_tInfo.m_fSpeed = 0.f;
}
void CScareCrow::attack()
{
	// Player 를 알아낸다.
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(pCurLevel->GetLayer(LAYER::PLAYER)[0]);
	if (GetPos().x < pPlayer->GetPos().x) m_tInfo.m_bIsLeft = false;
	else if(GetPos().x < pPlayer->GetPos().x) m_tInfo.m_bIsLeft = true;

	//한번 공격후 3초가 지나야지 다시 공격
	if (m_fAttackCoolTime > 3.f) {
		//왼쪽 보고 있으면 독가스 왼쪽으로
		if (m_tInfo.m_bIsLeft == true) {
			if (GetAnimator()->AnimationFinish(L"ScareCrow_Vomit_L")) {
				GetAnimator()->AnimationReset(L"ScareCrow_Vomit_L");
				CObj* Cvomit = new CScareCrowVomit(this);
				Vec2 vPos = Vec2(GetPos().x, GetPos().y - 100);
				Instantiate(Cvomit, vPos, LAYER::MONSTER_PROJECTILE);
				m_fAttackCoolTime = 0.f;
			}
			else {
				AdjustCollider(L"ScareCrow_Vomit_L", Vec2(80.f, 160.f), Vec2(64.f, 715.f));
				GetAnimator()->Play(L"ScareCrow_Vomit_L", false);
			}
		}
		//오른쪽 보고 있으면 독가스 오른쪽으로
		else {
			if (GetAnimator()->AnimationFinish(L"ScareCrow_Vomit_R")) {
				GetAnimator()->AnimationReset(L"ScareCrow_Vomit_R");
				CObj* Cvomit = new CScareCrowVomit(this);
				Vec2 vPos = Vec2(GetPos().x, GetPos().y - 100);
				Instantiate(Cvomit, vPos, LAYER::MONSTER_PROJECTILE);
				m_fAttackCoolTime = 0.f;
			}
			else {
				AdjustCollider(L"ScareCrow_Vomit_R", Vec2(80.f, 160.f), Vec2(64.f, 715.f));
				GetAnimator()->Play(L"ScareCrow_Vomit_R", false);
			}
		}
	}
	//아니면 Idle포즈를 취한다.
	else {
		if (m_tInfo.m_bIsLeft == true) {
			AdjustCollider(L"ScareCrow_Idle_L", Vec2(80.f, 160.f), Vec2(53.f, 46.f));
			GetAnimator()->Play(L"ScareCrow_Idle_L", true);
		}
		else if (m_tInfo.m_bIsLeft == false) {
			AdjustCollider(L"ScareCrow_Idle_R", Vec2(80.f, 160.f), Vec2(53.f, 46.f));
			GetAnimator()->Play(L"ScareCrow_Idle_R", true);
			
		}
	}

	// Player 와 Monster 의 거리값을 계산
	float fDetectRange = m_tInfo.m_fDetectRange;
	// Player 가 탐지범위에서 벗어나면 Idle로 전환
	Vec2 vDir = GetPos() - pPlayer->GetPos();
	if (abs(vDir.x) > fDetectRange || abs(vDir.y) > 20.f)
	{
		GetAI()->ChangeState(L"Idle");
	}
	// Player가 Attack범위 안에 있지만 Trace범위 내이면 Trace로 전환
	float fAttackRange = m_tInfo.m_fAttRange;
	if (fAttackRange < abs(vDir.x) && abs(vDir.x) < fDetectRange)
	{
		GetAI()->ChangeState(L"Trace");
	}
	
}
void CScareCrow::attack_exit()
{
	GetAnimator()->AnimationReset(L"ScareCrow_Vomit_L");
	GetAnimator()->AnimationReset(L"ScareCrow_Vomit_R");
}
void CScareCrow::hit()
{
	m_tInfo.m_fSpeed = 0.f;
	if (GetAnimator()->AnimationFinish(L"ScareCrow_GetHit_L") || GetAnimator()->AnimationFinish(L"ScareCrow_GetHit_R")) {
		GetAI()->ChangeState(L"Idle");
	}
	
}

void CScareCrow::hit_enter()
{
	CSound* hitsound = CResMgr::GetInst()->LoadSound(L"scarecrow_hit", L"sound\\monster\\enemy_global_gethit_01.wav");
	hitsound->SetVolume(40);
	hitsound->Play();
	if (m_tInfo.m_bIsLeft == true) {
		AdjustCollider(L"ScareCrow_GetHit_L", Vec2(80.f, 160.f), Vec2(77.f, 1177.f));
		GetAnimator()->Play(L"ScareCrow_GetHit_L", false);
	}
	else if (m_tInfo.m_bIsLeft == false) {
		AdjustCollider(L"ScareCrow_GetHit_R", Vec2(80.f, 160.f), Vec2(77.f, 1177.f));
		GetAnimator()->Play(L"ScareCrow_GetHit_R", false);
	}
}
void CScareCrow::hit_exit()
{
	GetAnimator()->AnimationReset(L"ScareCrow_GetHit_R");
	GetAnimator()->AnimationReset(L"ScareCrow_GetHit_L");
}

void CScareCrow::dead()
{
	CObj* cScareCrowDead = new CScareCrowDead(this);
	Instantiate(cScareCrowDead, GetPos(), LAYER::DEATH_LEFTOVER);
	SetDead();
}


void CScareCrow::LoadScareCrowAnimation()
{
	CTexture* ScareCrow_L = CResMgr::GetInst()->LoadTexture(L"Scarecrow_L", L"texture\\monster\\Scarecrow_L.bmp");
	CTexture* ScareCrow_R = CResMgr::GetInst()->LoadTexture(L"Scarecrow_R", L"texture\\monster\\Scarecrow_R.bmp");

	/*GetAnimator()->CreateAnimation(L"ScareCrow_Idle_L", ScareCrow_L, Vec2(7.f, 35.f), Vec2(168.f, 171.f), Vec2(0.f, 0.f), Vec2(7.f, 0.f), 9, 1, 9, 0.1f);
	GetAnimator()->FindAnimation(L"ScareCrow_Idle_L")->Save(L"animation\\monster\\ScareCrow_Idle_L.anim");
	GetAnimator()->CreateAnimation(L"ScareCrow_Idle_R", ScareCrow_R, Vec2(7.f, 35.f), Vec2(168.f, 171.f), Vec2(0.f, 0.f), Vec2(7.f, 0.f), 9, 1, 9, 0.1f);
	GetAnimator()->FindAnimation(L"ScareCrow_Idle_R")->Save(L"animation\\monster\\ScareCrow_Idle_R.anim");

	GetAnimator()->CreateAnimation(L"ScareCrow_Walk_L", ScareCrow_L, Vec2(7.f, 255.f), Vec2(189.f, 187.f), Vec2(0.f, 0.f), Vec2(7.f, 14.f), 18, 2, 12, 0.1f);
	GetAnimator()->FindAnimation(L"ScareCrow_Walk_L")->Save(L"animation\\monster\\ScareCrow_Walk_L.anim");
	GetAnimator()->CreateAnimation(L"ScareCrow_Walk_R", ScareCrow_R, Vec2(7.f, 255.f), Vec2(189.f, 187.f), Vec2(0.f, 0.f), Vec2(7.f, 14.f), 18, 2, 12, 0.1f);
	GetAnimator()->FindAnimation(L"ScareCrow_Walk_R")->Save(L"animation\\monster\\ScareCrow_Walk_R.anim");

	GetAnimator()->CreateAnimation(L"ScareCrow_Vomit_L", ScareCrow_L, Vec2(7.f, 690.f), Vec2(189.f, 185.f), Vec2(0.f, 0.f), Vec2(7.f, 14.f), 21, 2, 12, 0.05f);
	GetAnimator()->FindAnimation(L"ScareCrow_Vomit_L")->Save(L"animation\\monster\\ScareCrow_Vomit_L.anim");
	GetAnimator()->CreateAnimation(L"ScareCrow_Vomit_R", ScareCrow_R, Vec2(7.f, 690.f), Vec2(189.f, 185.f), Vec2(0.f, 0.f), Vec2(7.f, 14.f), 21, 2, 12, 0.05f);
	GetAnimator()->FindAnimation(L"ScareCrow_Vomit_R")->Save(L"animation\\monster\\ScareCrow_Vomit_R.anim");

	GetAnimator()->CreateAnimation(L"ScareCrow_GetHit_L", ScareCrow_L, Vec2(7.f, 1124.f), Vec2(189.f, 213.f), Vec2(0.f, 0.f), Vec2(7.f, 7.f), 6, 1, 6, 0.075f);
	GetAnimator()->FindAnimation(L"ScareCrow_GetHit_L")->Save(L"animation\\monster\\ScareCrow_GetHit_L.anim");
	GetAnimator()->CreateAnimation(L"ScareCrow_GetHit_R", ScareCrow_R, Vec2(7.f, 1124.f), Vec2(189.f, 213.f), Vec2(0.f, 0.f), Vec2(7.f, 7.f), 6, 1, 6, 0.075f);
	GetAnimator()->FindAnimation(L"ScareCrow_GetHit_R")->Save(L"animation\\monster\\ScareCrow_GetHit_R.anim");*/



	GetAnimator()->LoadAnimation(L"animation\\monster\\ScareCrow_Idle_L.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\ScareCrow_Idle_R.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\ScareCrow_Walk_L.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\ScareCrow_Walk_R.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\ScareCrow_Vomit_L.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\ScareCrow_Vomit_R.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\ScareCrow_GetHit_L.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\ScareCrow_GetHit_R.anim");
	
}
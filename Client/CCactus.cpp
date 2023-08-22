#include "pch.h"
#include "CCactus.h"
#include "CResMgr.h"
#include "CTimeMgr.h"
#include "CAttackState.h"
#include "CIdleState.h"
#include "CTraceState.h"
#include "CHitState.h"
#include "CFallState.h"
#include "CLandState.h"
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
#include "CSound.h"

#include "CWhip.h"
#include "CPikeBall.h"
#include "CPistol.h"
#include "CScimitar.h"
#include "CMonsterBullet.h"
#include "CCactusDeath.h"

CCactus::CCactus()
	: m_fAttackCoolTime(0.f)
{
	m_tInfo.m_iHP = 2;
	m_tInfo.m_iMaxHP = 2;
	m_tInfo.m_fDetectRange = 1000.f;
	m_tInfo.m_fAttRange = 1000.f;
	m_tInfo.m_bIsLeft = true;
	m_tInfo.m_fAtt = 1;
	m_tInfo.m_iGemValue = 2;
	
	
	LoadCactusAnimation();
	GetAnimator()->SetFloorPlay(true);
	GetRigidbody()->SetGravity(true);
	GetRigidbody()->SetGravityAccel(300.f);
	GetRigidbody()->SetGravityVelocityLimit(1000.f);
	GetAI()->AddState(L"Idle", new CIdleState);
	GetAI()->AddState(L"Trace", new CTraceState);
	GetAI()->AddState(L"Attack", new CAttackState);
	GetAI()->AddState(L"Hit", new CHitState);
	GetAI()->AddState(L"Fall", new CFallState);
	GetAI()->AddState(L"Land", new CLandState);
	GetAI()->AddState(L"Dead", new CDeadState);

	GetAI()->ChangeState(L"Idle");
}

CCactus::~CCactus()
{
}


void CCactus::tick()
{
	if (m_tInfo.m_iHP <= 0 && !IsDead()) {
		GetAI()->ChangeState(L"Dead");
	}
	if (GetRigidbody()->GetGround() == false) {
		GetAI()->ChangeState(L"Fall");
	}
	CObj::tick();
}

void CCactus::render(HDC _dc)
{
	CObj::render(_dc);
}

void CCactus::BeginOverlap(CCollider* _pOther)
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

void CCactus::idle_enter()
{
	m_tInfo.m_fSpeed = 50.f;
	
}

void CCactus::idle_exit()
{
	GetAnimator()->AnimationReset(L"CactusLtoR");
	GetAnimator()->AnimationReset(L"CactusRtoL");
	m_tInfo.m_fPatrolRange = 0.f;
}



void CCactus::walk()
{
	m_tInfo.m_fPatrolRange += DT;
	if (m_tInfo.m_fPatrolRange > 5.f) {
		if (m_tInfo.m_bIsLeft == true) {
			if (GetAnimator()->AnimationFinish(L"CactusLtoR")) {
				GetAnimator()->AnimationReset(L"CactusLtoR");
				m_tInfo.m_bIsLeft = false;
				m_tInfo.m_fPatrolRange = 0.f;
			}
			else {
				GetAnimator()->Play(L"CactusLtoR", false);
			}
			
		}
		else if (m_tInfo.m_bIsLeft == false) {
			if (GetAnimator()->AnimationFinish(L"CactusRtoL")) {
				GetAnimator()->AnimationReset(L"CactusRtoL");
				m_tInfo.m_bIsLeft = true;
				m_tInfo.m_fPatrolRange = 0.f;
			}
			else {
				GetAnimator()->Play(L"CactusRtoL", false);
			}

		}
	}
	else {
		if (m_tInfo.m_bIsLeft == true) {
			GetAnimator()->Play(L"Cactus_Walk_L", true);
			Vec2 vMonPos = GetPos();
			vMonPos.x -= m_tInfo.m_fSpeed * DT;
			SetPos(vMonPos);
		}
		else if (m_tInfo.m_bIsLeft == false) {
			GetAnimator()->Play(L"Cactus_Walk_R", true);
			Vec2 vMonPos = GetPos();
			vMonPos.x += m_tInfo.m_fSpeed * DT;
			SetPos(vMonPos);
		}
	}
	
}


void CCactus::attack_enter()
{
	m_tInfo.m_fPatrolRange = 0.f;
	m_fAttackCoolTime = 2.0f;
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(pCurLevel->GetLayer(LAYER::PLAYER)[0]);
	//방향전환
	if (GetPos().x < pPlayer->GetPos().x) {
		m_tInfo.m_bIsLeft = false;
	}
	else if (GetPos().x > pPlayer->GetPos().x) {
		m_tInfo.m_bIsLeft = true;
	}
}

void CCactus::attack()
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(pCurLevel->GetLayer(LAYER::PLAYER)[0]);

	//방향전환
	m_fAttackCoolTime += DT;
	if (m_fAttackCoolTime > 3.f) {
		//왼쪽 보는 상태로 총알
		if (m_tInfo.m_bIsLeft == true) {
			if (GetAnimator()->AnimationFinish(L"Cactus_Concentrate_L")) {
				if (GetAnimator()->AnimationFinish(L"Cactus_Burst_L")) {
					CSound* shoot = CResMgr::GetInst()->LoadSound(L"cactus_shoot", L"sound\\monster\\enemy_cactus_shootspikes.wav");
					shoot->Play();
					for (int i = 0; i < 7; ++i) {
						CObj* CBullet = new CMonsterBullet(this, (float)i*30);
						Vec2 vPos = Vec2(GetPos().x, GetPos().y - 25);
						Instantiate(CBullet, vPos, LAYER::MONSTER_PROJECTILE);
					}
					GetAnimator()->AnimationReset(L"Cactus_Burst_L");
					GetAnimator()->AnimationReset(L"Cactus_Concentrate_L");
					m_fAttackCoolTime = 0.f;
				}
				else {
					//AdjustCollider(L"Cactus_Burst_L", Vec2(37.f, 37.f), Vec2(42.f, 458.f));
					GetAnimator()->Play(L"Cactus_Burst_L", false);
				}

			}
			else {
				//AdjustCollider(L"Cactus_Concentrate_L", Vec2(37.f, 37.f), Vec2(35.f, 375.f));
				GetAnimator()->Play(L"Cactus_Concentrate_L", false);
			}
		}
		//오른쪽 보는 상태로 총알
		else {
			if (GetAnimator()->AnimationFinish(L"Cactus_Concentrate_R")) {
				if (GetAnimator()->AnimationFinish(L"Cactus_Burst_R")) {
					CSound* shoot = CResMgr::GetInst()->LoadSound(L"cactus_shoot", L"sound\\monster\\enemy_cactus_shootspikes.wav");
					shoot->Play();
					for (int i = 0; i < 7; ++i) {
						CObj* CBullet = new CMonsterBullet(this, (float)i * 30);
						Vec2 vPos = Vec2(GetPos().x, GetPos().y - 25);
						Instantiate(CBullet, vPos, LAYER::MONSTER_PROJECTILE);
					}
					GetAnimator()->AnimationReset(L"Cactus_Burst_R");
					GetAnimator()->AnimationReset(L"Cactus_Concentrate_R");
					m_fAttackCoolTime = 0.f;
				}
				else {
					//AdjustCollider(L"Cactus_Burst_R", Vec2(37.f, 37.f), Vec2(40.f, 458.f));
					GetAnimator()->Play(L"Cactus_Burst_R", false);
				}

			}
			else {
				//AdjustCollider(L"Cactus_Concentrate_R", Vec2(37.f, 37.f), Vec2(33.f, 375.f));
				GetAnimator()->Play(L"Cactus_Concentrate_R", false);
			}
		}
	}
	else {
		walk();
	}

	// Player 와 Monster 의 거리값을 계산
	float fAttackRange = m_tInfo.m_fAttRange;

	Vec2 vDir = GetPos() - pPlayer->GetPos();
	if (GetMonInfo().m_bIsLeft == true) {
		if (pPlayer->GetPos().x < GetPos().x) {
			if (abs(vDir.x) > fAttackRange || abs(vDir.y) > 20.f)
			{
				GetAI()->ChangeState(L"Idle");
			}
		}
		else {
			GetAI()->ChangeState(L"Idle");
		}
	}
	//몬스터가 오른쪽을 바라보고 있을경우
	else if (GetMonInfo().m_bIsLeft == false) {
		if (GetPos().x < pPlayer->GetPos().x) {
			if (abs(vDir.x) > fAttackRange || abs(vDir.y) > 20.f)
			{
				GetAI()->ChangeState(L"Idle");
			}
		}
		else {
			GetAI()->ChangeState(L"Idle");
		}
	}
	//// Player 가 탐지범위에서 벗어나면 Idle로 전환
	//Vec2 vDir = GetPos() - pPlayer->GetPos();
	//if (abs(vDir.x) > fDetectRange || abs(vDir.y) > 20.f)
	//{
	//	GetAI()->ChangeState(L"Idle");
	//}
}

void CCactus::attack_exit()
{
	m_fAttackCoolTime = 0.f;
	m_tInfo.m_fPatrolRange = 0.f;
	GetAnimator()->AnimationReset(L"Cactus_Burst_L");
	GetAnimator()->AnimationReset(L"Cactus_Concentrate_L");
	GetAnimator()->AnimationReset(L"Cactus_Burst_R");
	GetAnimator()->AnimationReset(L"Cactus_Concentrate_R");
}

void CCactus::hit()
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(pCurLevel->GetLayer(LAYER::PLAYER)[0]);
	//왼쪽을 보고 있는데 오른쪽에서 맞을 경우 Turn
	if (m_tInfo.m_bIsLeft == true && GetPos().x < pPlayer->GetPos().x) {
		if (GetAnimator()->AnimationFinish(L"CactusLtoR")) {
			GetAnimator()->AnimationReset(L"CactusLtoR");
			m_tInfo.m_bIsLeft = false;
			GetAI()->ChangeState(L"Idle");
		}
		else {
			GetAnimator()->Play(L"CactusLtoR", false);
		}

	}
	//오른쪽을 보고 있는데 왼쪽에서 맞을 경우 Turn
	else if (m_tInfo.m_bIsLeft == false && pPlayer->GetPos().x < GetPos().x) {
		if (GetAnimator()->AnimationFinish(L"CactusRtoL")) {
			GetAnimator()->AnimationReset(L"CactusRtoL");
			m_tInfo.m_bIsLeft = true;
			GetAI()->ChangeState(L"Idle");
		}
		else {
			GetAnimator()->Play(L"CactusRtoL", false);
		}

	}
}

void CCactus::hit_exit()
{
	GetAnimator()->AnimationReset(L"CactusLtoR");
	GetAnimator()->AnimationReset(L"CactusRtoL");
}

void CCactus::fall_enter()
{
	m_tInfo.m_fSpeed = 0.f;
}

void CCactus::fall()
{
	if (m_tInfo.m_bIsLeft == true) {
		AdjustCollider(L"Cactus_Fall_L", Vec2(38.f, 38.f), Vec2(31.f, 209.f));
		GetAnimator()->Play(L"Cactus_Fall_L", true);
	}
	else if (m_tInfo.m_bIsLeft == false) {
		AdjustCollider(L"Cactus_Fall_R", Vec2(38.f, 38.f), Vec2(31.f, 209.f));
		GetAnimator()->Play(L"Cactus_Fall_R", true);
	}
}

void CCactus::fall_exit()
{
}

void CCactus::land_enter()
{
}

void CCactus::land()
{
	if (m_tInfo.m_bIsLeft == true) {
		if (GetAnimator()->AnimationFinish(L"Cactus_Land_L")) {
			GetAI()->ChangeState(L"Idle");
		}
		else {
			GetAnimator()->Play(L"Cactus_Land_L", false);
		}
		
	}
	else if (m_tInfo.m_bIsLeft == false) {
		if (GetAnimator()->AnimationFinish(L"Cactus_Land_R")) {
			GetAI()->ChangeState(L"Idle");
		}
		else {
			GetAnimator()->Play(L"Cactus_Land_R", false);
		}
	}
}

void CCactus::land_exit()
{
	GetAnimator()->AnimationReset(L"Cactus_Land_L");
	GetAnimator()->AnimationReset(L"Cactus_Land_R");
}

void CCactus::dead()
{
	CObj* CactusDeath = new CCactusDeath(this);
	Instantiate(CactusDeath, GetPos(), LAYER::DEATH_LEFTOVER);
	SetDead();
}

void CCactus::LoadCactusAnimation()
{
	CTexture* Cactus_L = CResMgr::GetInst()->LoadTexture(L"Cactus_L", L"texture\\monster\\Cactus_L.bmp");
	CTexture* Cactus_R = CResMgr::GetInst()->LoadTexture(L"Cactus_R", L"texture\\monster\\Cactus_R.bmp");

	/*GetAnimator()->CreateAnimation(L"CactusLtoR", Cactus_L, Vec2(4.f, 22.f), Vec2(109.f, 57.f), Vec2(0.f, 0.f), Vec2(4.f, 0.f), 2, 1, 2, 0.1f);
	GetAnimator()->FindAnimation(L"CactusLtoR")->Save(L"animation\\monster\\CactusLtoR.anim");
	GetAnimator()->CreateAnimation(L"CactusRtoL", Cactus_R, Vec2(4.f, 22.f), Vec2(109.f, 57.f), Vec2(0.f, 0.f), Vec2(4.f, 0.f), 2, 1, 2, 0.1f);
	GetAnimator()->FindAnimation(L"CactusRtoL")->Save(L"animation\\monster\\CactusRtoL.anim");

	GetAnimator()->CreateAnimation(L"Cactus_Walk_L", Cactus_L, Vec2(4.f, 106.f), Vec2(109.f, 56.f), Vec2(0.f, 0.f), Vec2(4.f, 0.f), 6, 1, 6, 0.1f);
	GetAnimator()->FindAnimation(L"Cactus_Walk_L")->Save(L"animation\\monster\\Cactus_Walk_L.anim");
	GetAnimator()->CreateAnimation(L"Cactus_Walk_R", Cactus_R, Vec2(4.f, 106.f), Vec2(109.f, 56.f), Vec2(0.f, 0.f), Vec2(4.f, 0.f), 6, 1, 6, 0.1f);
	GetAnimator()->FindAnimation(L"Cactus_Walk_R")->Save(L"animation\\monster\\Cactus_Walk_R.anim");

	GetAnimator()->CreateAnimation(L"Cactus_Fall_L", Cactus_L, Vec2(4.f, 189.f), Vec2(95.f, 57.f), Vec2(0.f, 0.f), Vec2(5.f, 0.f), 3, 1, 3, 0.1f);
	GetAnimator()->FindAnimation(L"Cactus_Fall_L")->Save(L"animation\\monster\\Cactus_Fall_L.anim");
	GetAnimator()->CreateAnimation(L"Cactus_Fall_R", Cactus_R, Vec2(4.f, 189.f), Vec2(95.f, 57.f), Vec2(0.f, 0.f), Vec2(5.f, 0.f), 3, 1, 3, 0.1f);
	GetAnimator()->FindAnimation(L"Cactus_Fall_R")->Save(L"animation\\monster\\Cactus_Fall_R.anim");

	GetAnimator()->CreateAnimation(L"Cactus_Land_L", Cactus_L, Vec2(5.f, 273.f), Vec2(94.f, 55.f), Vec2(0.f, 0.f), Vec2(5.f, 0.f), 3, 1, 3, 0.1f);
	GetAnimator()->FindAnimation(L"Cactus_Land_L")->Save(L"animation\\monster\\Cactus_Land_L.anim");
	GetAnimator()->CreateAnimation(L"Cactus_Land_R", Cactus_R, Vec2(5.f, 273.f), Vec2(94.f, 55.f), Vec2(0.f, 0.f), Vec2(5.f, 0.f), 3, 1, 3, 0.1f);
	GetAnimator()->FindAnimation(L"Cactus_Land_R")->Save(L"animation\\monster\\Cactus_Land_R.anim");

	GetAnimator()->CreateAnimation(L"Cactus_Concentrate_L", Cactus_L, Vec2(5.f, 355.f), Vec2(94.f, 57.f), Vec2(0.f, 0.f), Vec2(5.f, 0.f), 4, 1, 4, 0.1f);
	GetAnimator()->FindAnimation(L"Cactus_Concentrate_L")->Save(L"animation\\monster\\Cactus_Concentrate_L.anim");
	GetAnimator()->CreateAnimation(L"Cactus_Concentrate_R", Cactus_R, Vec2(5.f, 355.f), Vec2(94.f, 57.f), Vec2(0.f, 0.f), Vec2(5.f, 0.f), 4, 1, 4, 0.1f);
	GetAnimator()->FindAnimation(L"Cactus_Concentrate_R")->Save(L"animation\\monster\\Cactus_Concentrate_R.anim");

	GetAnimator()->CreateAnimation(L"Cactus_Burst_L", Cactus_L, Vec2(4.f, 439.f), Vec2(109.f, 56.f), Vec2(0.f, 0.f), Vec2(4.f, 0.f), 4, 1, 4, 0.1f);
	GetAnimator()->FindAnimation(L"Cactus_Burst_L")->Save(L"animation\\monster\\Cactus_Burst_L.anim");
	GetAnimator()->CreateAnimation(L"Cactus_Burst_R", Cactus_R, Vec2(4.f, 439.f), Vec2(109.f, 56.f), Vec2(0.f, 0.f), Vec2(4.f, 0.f), 4, 1, 4, 0.1f);
	GetAnimator()->FindAnimation(L"Cactus_Burst_R")->Save(L"animation\\monster\\Cactus_Burst_R.anim");*/



	GetAnimator()->LoadAnimation(L"animation\\monster\\CactusLtoR.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\CactusRtoL.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\Cactus_Walk_L.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\Cactus_Walk_R.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\Cactus_Fall_L.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\Cactus_Fall_R.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\Cactus_Land_L.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\Cactus_Land_R.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\Cactus_Concentrate_L.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\Cactus_Concentrate_R.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\Cactus_Burst_L.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\Cactus_Burst_R.anim");
}

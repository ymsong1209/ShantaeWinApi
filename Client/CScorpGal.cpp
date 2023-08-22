#include "pch.h"
#include "CScorpGal.h"
#include "CResMgr.h"
#include "CTimeMgr.h"
#include "CAttackState.h"
#include "CIdleState.h"
#include "CTraceState.h"
#include "CHitState.h"
#include "CBlockState.h"
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
#include "CWhip.h"
#include "CPikeBall.h"
#include "CPistol.h"
#include "CScimitar.h"
#include "CDamage.h"
#include "CScorpGalAttack.h"
#include "CScorpGalDeath.h"
#include "CSound.h"
CScorpGal::CScorpGal()
	: m_fAttackCoolTime(0.f)
	, m_fPatrolCoolTime(0.f)
	, m_fIdleCoolTime(0.f)
	, m_bWasPatrollingLeft(true)
	, m_bHasAttacked(false)
	, m_sPatrol(nullptr)
	, m_sBlockSound(nullptr)
{
	m_tInfo.m_iHP = 15;
	m_tInfo.m_iMaxHP = 15;
	m_tInfo.m_fDetectRange = 550.f;
	m_tInfo.m_fAttRange = 350.f;
	m_tInfo.m_bIsLeft = true;
	m_tInfo.m_fAtt = 1;
	m_tInfo.m_iGemValue = 0;

	LoadScorpGalAnimation();
	m_sPatrol = CResMgr::GetInst()->LoadSound(L"scorpgal_walk", L"sound\\monster\\enemey_crab_footstep_01.wav");
	m_sBlockSound = CResMgr::GetInst()->LoadSound(L"scorpgal_block", L"sound\\monster\\scorpgal_block.wav");
	GetAnimator()->SetFloorPlay(true);
	GetRigidbody()->SetGravity(true);
	GetRigidbody()->SetGravityAccel(300.f);
	GetRigidbody()->SetGravityVelocityLimit(1000.f);
	GetAI()->AddState(L"Idle", new CIdleState);
	GetAI()->AddState(L"Trace", new CTraceState);
	GetAI()->AddState(L"Attack", new CAttackState);
	GetAI()->AddState(L"Hit", new CHitState);
	GetAI()->AddState(L"Block", new CBlockState);
	GetAI()->AddState(L"Dead", new CDeadState);

	GetAI()->ChangeState(L"Idle");
	
	
}

CScorpGal::~CScorpGal()
{
}



void CScorpGal::tick()
{
	if (m_tInfo.m_iHP <= 0&& !IsDead()) {
		GetAI()->ChangeState(L"Dead");
	}
	CObj::tick();
	
}

void CScorpGal::render(HDC _dc)
{
	CObj::render(_dc);
}

void CScorpGal::BeginOverlap(CCollider* _pOther)
{
	CWhip* pWhip = dynamic_cast<CWhip*>(_pOther->GetOwner());
	if (nullptr != pWhip) {
		//whip이 왼쪽에서 왔는데 ScorpGal이 왼쪽을 바라보고 있다.
		if (pWhip->GetPos().x < GetPos().x && m_tInfo.m_bIsLeft == true) {
			GetAI()->ChangeState(L"Block");
		}
		//whip이 왼쪽에서 왔는데 ScopGal이 오른쪽을 바라보고 있다.
		else if(pWhip->GetPos().x<GetPos().x && m_tInfo.m_bIsLeft == false) {
			GetAI()->ChangeState(L"Hit");
			m_tInfo.m_iHP -= (pWhip->ReturnWhipDmg() + pWhip->ReturnWhipExtraDmg());
			CObj* cDamage = new CDamage(pWhip->ReturnWhipDmg(), false);
			Vec2 DamagePos = Vec2(GetPos().x, GetPos().y - GetCollider()->GetScale().y);
			Vec2 Damage2Pos = Vec2(DamagePos.x + 15, DamagePos.y);
			CObj* cDamage2 = new CDamage(pWhip->ReturnWhipExtraDmg(), true);
			Instantiate(cDamage, DamagePos, LAYER::DAMAGE);
			Instantiate(cDamage2, Damage2Pos, LAYER::DAMAGE);
		}

		//whip이 오른쪽에서 왔는데 ScorpGal이 오른쪽을 바라보고 있다.
		if (GetPos().x < pWhip->GetPos().x && m_tInfo.m_bIsLeft == false) {
			GetAI()->ChangeState(L"Block");
		}
		//whip이 오른쪽에서 왔는데 ScopGal이 왼쪽을 바라보고 있다.
		else if (GetPos().x < pWhip->GetPos().x && m_tInfo.m_bIsLeft == true) {
			GetAI()->ChangeState(L"Hit");
			m_tInfo.m_iHP -= (pWhip->ReturnWhipDmg() + pWhip->ReturnWhipExtraDmg());
			CObj* cDamage = new CDamage(pWhip->ReturnWhipDmg(), false);
			Vec2 DamagePos = Vec2(GetPos().x, GetPos().y - GetCollider()->GetScale().y);
			Vec2 Damage2Pos = Vec2(DamagePos.x + 15, DamagePos.y);
			CObj* cDamage2 = new CDamage(pWhip->ReturnWhipExtraDmg(), true);
			Instantiate(cDamage, DamagePos, LAYER::DAMAGE);
			Instantiate(cDamage2, Damage2Pos, LAYER::DAMAGE);
		}
	}

	CPistol* pPistol = dynamic_cast<CPistol*>(_pOther->GetOwner());
	if (nullptr != pPistol) {
		//pistol이 왼쪽에서 왔는데 ScorpGal이 왼쪽을 바라보고 있다.
		if (pPistol->GetPos().x < GetPos().x && m_tInfo.m_bIsLeft == true) {
			GetAI()->ChangeState(L"Block");
		}
		//pistol이 왼쪽에서 왔는데 ScopGal이 오른쪽을 바라보고 있다.
		else if (pPistol->GetPos().x < GetPos().x && m_tInfo.m_bIsLeft == false) {
			GetAI()->ChangeState(L"Hit");
			m_tInfo.m_iHP -= (pPistol->ReturnPistolDmg() + pPistol->ReturnPistolExtraDmg());
			CObj* cDamage = new CDamage(pPistol->ReturnPistolDmg(), false);
			Vec2 DamagePos = Vec2(GetPos().x, GetPos().y - GetCollider()->GetScale().y);
			Vec2 Damage2Pos = Vec2(DamagePos.x + 15, DamagePos.y);
			CObj* cDamage2 = new CDamage(pPistol->ReturnPistolExtraDmg(), true);
			Instantiate(cDamage, DamagePos, LAYER::DAMAGE);
			Instantiate(cDamage2, Damage2Pos, LAYER::DAMAGE);
		}

		//pistol이 오른쪽에서 왔는데 ScorpGal이 오른쪽을 바라보고 있다.
		if (GetPos().x < pPistol->GetPos().x && m_tInfo.m_bIsLeft == false) {
			GetAI()->ChangeState(L"Block");
		}
		//pistol이 오른쪽에서 왔는데 ScopGal이 왼쪽을 바라보고 있다.
		else if (GetPos().x < pPistol->GetPos().x && m_tInfo.m_bIsLeft == true) {
			GetAI()->ChangeState(L"Hit");
			m_tInfo.m_iHP -= (pPistol->ReturnPistolDmg() + pPistol->ReturnPistolExtraDmg());
			CObj* cDamage = new CDamage(pPistol->ReturnPistolDmg(), false);
			Vec2 DamagePos = Vec2(GetPos().x, GetPos().y - GetCollider()->GetScale().y);
			Vec2 Damage2Pos = Vec2(DamagePos.x + 15, DamagePos.y);
			CObj* cDamage2 = new CDamage(pPistol->ReturnPistolExtraDmg(), true);
			Instantiate(cDamage, DamagePos, LAYER::DAMAGE);
			Instantiate(cDamage2, Damage2Pos, LAYER::DAMAGE);
		}
		
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

void CScorpGal::idle_enter()
{
	
	m_tInfo.m_fSpeed = 150.f;
	//m_sPatrol->Play(true);
	
	
}

void CScorpGal::idle_exit()
{
	//m_sPatrol->Stop();
}



void CScorpGal::walk()
{
	//원래 왼쪽으로 Patrol하고 있었는데 Hit때문에 오른쪽을 보고 있었다.
	if (m_bWasPatrollingLeft == true && m_tInfo.m_bIsLeft == false) {
		if (GetAnimator()->AnimationFinish(L"ScorpGal_RtoL")) {
			GetAnimator()->AnimationReset(L"ScorpGal_RtoL");
			m_tInfo.m_bIsLeft = true;
		}
		else {
			AdjustCollider(L"ScorpGal_RtoL", Vec2(242.f, 242.f), Vec2(126.f, 374.f));
			GetAnimator()->Play(L"ScorpGal_RtoL", false);
		}
	}
	//원래 오른쪽으로 Patrol하고 있었는데 Hit때문에 왼쪽을 보고 있었다.
	else if (m_bWasPatrollingLeft == false && m_tInfo.m_bIsLeft == true) {
		if (GetAnimator()->AnimationFinish(L"ScorpGal_LtoR")) {
			GetAnimator()->AnimationReset(L"ScorpGal_LtoR");
			m_tInfo.m_bIsLeft = false;
		}
		else {
			AdjustCollider(L"ScorpGal_LtoR", Vec2(242.f, 242.f), Vec2(126.f, 374.f));
			GetAnimator()->Play(L"ScorpGal_LtoR", false);
		}
	}
	else {
		m_tInfo.m_fPatrolRange += DT;
		if (m_tInfo.m_fPatrolRange > 3.f) {
			if (m_tInfo.m_bIsLeft == true) {
				if (GetAnimator()->AnimationFinish(L"ScorpGal_LtoR")) {
					GetAnimator()->AnimationReset(L"ScorpGal_LtoR");
					m_tInfo.m_bIsLeft = false;
					m_bWasPatrollingLeft = false;
					m_tInfo.m_fPatrolRange = 0.f;
				}
				else {
					AdjustCollider(L"ScorpGal_LtoR", Vec2(242.f, 242.f), Vec2(126.f, 374.f));
					GetAnimator()->Play(L"ScorpGal_LtoR", false);
				}

			}
			else if (m_tInfo.m_bIsLeft == false) {
				if (GetAnimator()->AnimationFinish(L"ScorpGal_RtoL")) {
					GetAnimator()->AnimationReset(L"ScorpGal_RtoL");
					m_tInfo.m_bIsLeft = true;
					m_bWasPatrollingLeft = true;
					m_tInfo.m_fPatrolRange = 0.f;
				}
				else {
					AdjustCollider(L"ScorpGal_RtoL", Vec2(242.f, 242.f), Vec2(126.f, 374.f));
					GetAnimator()->Play(L"ScorpGal_RtoL", false);
				}

			}
		}
		else {
			if (m_tInfo.m_bIsLeft == true) {
				AdjustCollider(L"ScorpGal_Walk_L", Vec2(242.f, 242.f), Vec2(92.f, 700.f));
				GetAnimator()->Play(L"ScorpGal_Walk_L", true);
				Vec2 vMonPos = GetPos();
				vMonPos.x -= m_tInfo.m_fSpeed * DT;
				SetPos(vMonPos);
			}
			else if (m_tInfo.m_bIsLeft == false) {
				AdjustCollider(L"ScorpGal_Walk_R", Vec2(242.f, 242.f), Vec2(92.f, 700.f));
				GetAnimator()->Play(L"ScorpGal_Walk_R", true);
				Vec2 vMonPos = GetPos();
				vMonPos.x += m_tInfo.m_fSpeed * DT;
				SetPos(vMonPos);
			}
		}
	}

	
}
void CScorpGal::trace_enter()
{
	m_tInfo.m_fSpeed = 0.f;
	if (m_tInfo.m_bIsLeft == true) {
		AdjustCollider(L"ScorpGal_Idle_L", Vec2(242.f, 242.f), Vec2(119.f, 62.f));
		GetAnimator()->Play(L"ScorpGal_Idle_L", true);
	}
	else if (m_tInfo.m_bIsLeft == false) {
		AdjustCollider(L"ScorpGal_Idle_R", Vec2(242.f, 242.f), Vec2(119.f, 62.f));
		GetAnimator()->Play(L"ScorpGal_Idle_R", true);
	}
}

void CScorpGal::trace_changeAnim()
{
}

void CScorpGal::attack_enter()
{
	m_fAttackCoolTime = 2.f;
	m_tInfo.m_fSpeed = 0.f;
}

void CScorpGal::attack()
{
	//공격범위 내이고 공격 쿨타임 3초가 지났다.
	if (m_fAttackCoolTime > 3.f) {
		//왼쪽공격
		if (m_tInfo.m_bIsLeft == true) {
			//공격준비모션
			if (GetAnimator()->AnimationFinish(L"ScorpGal_Attack1_L")) {
				//공격모션
				if (GetAnimator()->AnimationFinish(L"ScorpGal_Attack2_L")) {
					//공격마무리모션
					if (GetAnimator()->AnimationFinish(L"ScorpGal_Attack3_L")) {
						GetAnimator()->AnimationReset(L"ScorpGal_Attack1_L");
						GetAnimator()->AnimationReset(L"ScorpGal_Attack2_L");
						GetAnimator()->AnimationReset(L"ScorpGal_Attack3_L");
						m_bHasAttacked = false;
						m_fAttackCoolTime = 0.f;
					}
					else {
						GetAnimator()->Play(L"ScorpGal_Attack3_L", false);
					}
				}
				else {
					GetAnimator()->Play(L"ScorpGal_Attack2_L", false);
					if (m_bHasAttacked == false) {
						//공격
						CObj* attack = new CScorpGalAttack(this);
						Vec2 vPos = GetCollider()->GetFinalPos();
						Vec2 vFinalpos = Vec2(vPos.x - 245, vPos.y - 20);
						Instantiate(attack, vFinalpos, LAYER::MONSTER_PROJECTILE);
						CSound* attackSound = CResMgr::GetInst()->LoadSound(L"scorpgal_attack", L"sound\\monster\\enemy_scropion_girl_attack_sword.wav");
						attackSound->SetVolume(40);
						attackSound->Play();
						m_bHasAttacked = true;
					}
				}
			}
			else {
				AdjustCollider(L"ScorpGal_Attack1_L", Vec2(242.f, 242.f), Vec2(381.f, 1393.f));
				GetAnimator()->Play(L"ScorpGal_Attack1_L", false);
			}

		}
		//오른쪽공격
		else if (m_tInfo.m_bIsLeft == false) {
			//공격준비모션
			if (GetAnimator()->AnimationFinish(L"ScorpGal_Attack1_R")) {
				//공격모션
				if (GetAnimator()->AnimationFinish(L"ScorpGal_Attack2_R")) {
					//공격마무리모션
					if (GetAnimator()->AnimationFinish(L"ScorpGal_Attack3_R")) {
						GetAnimator()->AnimationReset(L"ScorpGal_Attack1_R");
						GetAnimator()->AnimationReset(L"ScorpGal_Attack2_R");
						GetAnimator()->AnimationReset(L"ScorpGal_Attack3_R");
						m_bHasAttacked = false;
						m_fAttackCoolTime = 0.f;
					}
					else {
						GetAnimator()->Play(L"ScorpGal_Attack3_R", false);
					}
				}
				else {
					GetAnimator()->Play(L"ScorpGal_Attack2_R", false);
					if (m_bHasAttacked == false) {
						//공격
						CObj* attack = new CScorpGalAttack(this);
						Vec2 vPos = GetCollider()->GetFinalPos();
						Vec2 vFinalpos = Vec2(vPos.x + 245, vPos.y -20);
						Instantiate(attack, vFinalpos, LAYER::MONSTER_PROJECTILE);
						CSound* attackSound = CResMgr::GetInst()->LoadSound(L"scorpgal_attack", L"sound\\monster\\enemy_scropion_girl_attack_sword.wav");
						attackSound->SetVolume(40);
						attackSound->Play();
						m_bHasAttacked = true;
					}
				}
			}
			else {
				AdjustCollider(L"ScorpGal_Attack1_R", Vec2(242.f, 242.f), Vec2(381.f, 1393.f));
				GetAnimator()->Play(L"ScorpGal_Attack1_R", false);
			}
		}
	}
	else {
		m_fAttackCoolTime += DT;
		if (m_tInfo.m_bIsLeft == true) {
			AdjustCollider(L"ScorpGal_Idle_L", Vec2(242.f, 242.f), Vec2(119.f, 62.f));
			GetAnimator()->Play(L"ScorpGal_Idle_L", true);
		}
		else if (m_tInfo.m_bIsLeft == false) {
			AdjustCollider(L"ScorpGal_Idle_R", Vec2(242.f, 242.f), Vec2(119.f, 62.f));
			GetAnimator()->Play(L"ScorpGal_Idle_R", true);
		}
	}
	
	// Player 를 알아낸다.
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(pCurLevel->GetLayer(LAYER::PLAYER)[0]);
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

void CScorpGal::attack_exit()
{
	GetAnimator()->AnimationReset(L"ScorpGal_Attack1_L");
	GetAnimator()->AnimationReset(L"ScorpGal_Attack2_L");
	GetAnimator()->AnimationReset(L"ScorpGal_Attack3_L");
	GetAnimator()->AnimationReset(L"ScorpGal_Attack1_R");
	GetAnimator()->AnimationReset(L"ScorpGal_Attack2_R");
	GetAnimator()->AnimationReset(L"ScorpGal_Attack3_R");
	m_bHasAttacked = false;
}

void CScorpGal::block()
{
	if (m_tInfo.m_bIsLeft == true) {
		AdjustCollider(L"ScorpGal_Block_L", Vec2(242.f,242.f), Vec2(119.f,1039.f));
		GetAnimator()->Play(L"ScorpGal_Block_L",false);
		if (GetAnimator()->AnimationFinish(L"ScorpGal_Block_L")) {
			GetAI()->ChangeState(L"Idle");
		}
	}
	else if (m_tInfo.m_bIsLeft == false) {
		AdjustCollider(L"ScorpGal_Block_R", Vec2(242.f, 242.f), Vec2(119.f, 1039.f));
		GetAnimator()->Play(L"ScorpGal_Block_R", false);
		if (GetAnimator()->AnimationFinish(L"ScorpGal_Block_R")) {
			GetAI()->ChangeState(L"Idle");
		}
	}
}

void CScorpGal::block_enter()
{
	
	m_sBlockSound->SetVolume(35);
	m_sBlockSound->Play();
	GetAnimator()->AnimationReset(L"ScorpGal_Block_L");
	GetAnimator()->AnimationReset(L"ScorpGal_Block_R");
}

void CScorpGal::block_exit()
{
	m_sBlockSound->Stop(true);
	//m_sBlockSound->SetPosition(0);
	GetAnimator()->AnimationReset(L"ScorpGal_Block_L");
	GetAnimator()->AnimationReset(L"ScorpGal_Block_R");
}

void CScorpGal::hit()
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(pCurLevel->GetLayer(LAYER::PLAYER)[0]);
	//왼쪽을 바라보고 있는데 오른쪽에서 맞았다.
	if (GetPos().x < pPlayer->GetPos().x) {
		if (GetAnimator()->AnimationFinish(L"ScorpGal_LtoR")) {
			GetAnimator()->AnimationReset(L"ScorpGal_LtoR");
			GetAI()->ChangeState(L"Idle");
		}
		else {
			AdjustCollider(L"ScorpGal_LtoR", Vec2(242.f, 242.f), Vec2(126.f, 374.f));
			m_tInfo.m_bIsLeft = false;
			GetAnimator()->Play(L"ScorpGal_LtoR", false);
		}

	}
	//오른쪽을 바라보고 있는데 왼쪽에서 맞았다.
	else if (pPlayer->GetPos().x < GetPos().x) {
		if (GetAnimator()->AnimationFinish(L"ScorpGal_RtoL")) {
			GetAnimator()->AnimationReset(L"ScorpGal_RtoL");
			GetAI()->ChangeState(L"Idle");
		}
		else {
			AdjustCollider(L"ScorpGal_RtoL", Vec2(242.f, 242.f), Vec2(126.f, 374.f));
			m_tInfo.m_bIsLeft = true;
			GetAnimator()->Play(L"ScorpGal_RtoL", false);
		}

	}
	else {
		GetAI()->ChangeState(L"Idle");
	}
}

void CScorpGal::hit_exit()
{
	GetAnimator()->AnimationReset(L"ScorpGal_LtoR");
	GetAnimator()->AnimationReset(L"ScorpGal_RtoL");
}

void CScorpGal::dead_enter()
{
	CObj* CDeath = new CScorpGalDeath(this);
	Instantiate(CDeath, GetPos(), LAYER::DEATH_LEFTOVER);
	SetDead();
}


void CScorpGal::LoadScorpGalAnimation()
{
	CTexture* ScorpGal_L = CResMgr::GetInst()->LoadTexture(L"ScorpGal_L", L"texture\\monster\\ScorpGal_L.bmp");
	CTexture* ScorpGal_R = CResMgr::GetInst()->LoadTexture(L"ScorpGal_R", L"texture\\monster\\ScorpGal_R.bmp");

	//주석 해제하지 말것!!!!!!!!!!!!! Attack함수 일부 조정함!!!!!

	//GetAnimator()->CreateAnimation(L"ScorpGal_Idle_L", ScorpGal_L, Vec2(7.f, 35.f), Vec2(462.f, 269.f), Vec2(0.f, 0.f), Vec2(7.f, 0.f), 6, 1, 6, 0.1f);
	//GetAnimator()->FindAnimation(L"ScorpGal_Idle_L")->Save(L"animation\\monster\\ScorpGal_Idle_L.anim");
	//GetAnimator()->CreateAnimation(L"ScorpGal_Idle_R", ScorpGal_R, Vec2(7.f, 35.f), Vec2(462.f, 269.f), Vec2(0.f, 0.f), Vec2(7.f, 0.f), 6, 1, 6, 0.1f);
	//GetAnimator()->FindAnimation(L"ScorpGal_Idle_R")->Save(L"animation\\monster\\ScorpGal_Idle_R.anim");

	//GetAnimator()->CreateAnimation(L"ScorpGal_LtoR", ScorpGal_L, Vec2(7.f, 346.f), Vec2(483.f, 270.f), Vec2(0.f, 0.f), Vec2(7.f, 0.f), 10, 1, 10, 0.075f);
	//GetAnimator()->FindAnimation(L"ScorpGal_LtoR")->Save(L"animation\\monster\\ScorpGal_LtoR.anim");
	//GetAnimator()->CreateAnimation(L"ScorpGal_RtoL", ScorpGal_R, Vec2(7.f, 346.f), Vec2(483.f, 270.f), Vec2(0.f, 0.f), Vec2(7.f, 0.f), 10, 1, 10, 0.075f);
	//GetAnimator()->FindAnimation(L"ScorpGal_RtoL")->Save(L"animation\\monster\\ScorpGal_RtoL.anim");

	//GetAnimator()->CreateAnimation(L"ScorpGal_Walk_L", ScorpGal_L, Vec2(7.f, 658.f), Vec2(420.f, 284.f), Vec2(0.f, 0.f), Vec2(7.f, 0.f), 6, 1, 6, 0.1f);
	//GetAnimator()->FindAnimation(L"ScorpGal_Walk_L")->Save(L"animation\\monster\\ScorpGal_Walk_L.anim");
	//GetAnimator()->CreateAnimation(L"ScorpGal_Walk_R", ScorpGal_R, Vec2(7.f, 658.f), Vec2(420.f, 284.f), Vec2(0.f, 0.f), Vec2(7.f, 0.f), 6, 1, 6, 0.1f);
	//GetAnimator()->FindAnimation(L"ScorpGal_Walk_R")->Save(L"animation\\monster\\ScorpGal_Walk_R.anim");

	//GetAnimator()->CreateAnimation(L"ScorpGal_Block_L", ScorpGal_L, Vec2(7.f, 984.f), Vec2(462.f, 297.f), Vec2(0.f, 0.f), Vec2(7.f, 0.f), 6, 1, 6, 0.1f);
	//GetAnimator()->FindAnimation(L"ScorpGal_Block_L")->Save(L"animation\\monster\\ScorpGal_Block_L.anim");
	//GetAnimator()->CreateAnimation(L"ScorpGal_Block_R", ScorpGal_R, Vec2(7.f, 984.f), Vec2(462.f, 297.f), Vec2(0.f, 0.f), Vec2(7.f, 0.f), 6, 1, 6, 0.1f);
	//GetAnimator()->FindAnimation(L"ScorpGal_Block_R")->Save(L"animation\\monster\\ScorpGal_Block_R.anim");

	//GetAnimator()->CreateAnimation(L"ScorpGal_Attack1_L", ScorpGal_L, Vec2(7.f, 1323.f), Vec2(987.f, 312.f), Vec2(0.f, 0.f), Vec2(7.f, 0.f), 5, 1, 5, 0.1f);
	//GetAnimator()->FindAnimation(L"ScorpGal_Attack1_L")->Save(L"animation\\monster\\ScorpGal_Attack1_L.anim");
	//GetAnimator()->CreateAnimation(L"ScorpGal_Attack1_R", ScorpGal_R, Vec2(7.f, 1323.f), Vec2(987.f, 312.f), Vec2(0.f, 0.f), Vec2(7.f, 0.f), 5, 1, 5, 0.1f);
	//GetAnimator()->FindAnimation(L"ScorpGal_Attack1_R")->Save(L"animation\\monster\\ScorpGal_Attack1_R.anim");

	//GetAnimator()->CreateAnimation(L"ScorpGal_Attack2_L", ScorpGal_L, Vec2(4977.f, 1323.f), Vec2(987.f, 312.f), Vec2(0.f, 0.f), Vec2(7.f, 0.f), 4, 1, 4, 0.1f);
	//GetAnimator()->FindAnimation(L"ScorpGal_Attack2_L")->Save(L"animation\\monster\\ScorpGal_Attack2_L.anim");
	//GetAnimator()->CreateAnimation(L"ScorpGal_Attack2_R", ScorpGal_R, Vec2(4977.f, 1323.f), Vec2(987.f, 312.f), Vec2(0.f, 0.f), Vec2(7.f, 0.f), 4, 1, 4, 0.1f);
	//GetAnimator()->FindAnimation(L"ScorpGal_Attack2_R")->Save(L"animation\\monster\\ScorpGal_Attack2_R.anim");

	//GetAnimator()->CreateAnimation(L"ScorpGal_Attack3_L", ScorpGal_L, Vec2(8953.f, 1323.f), Vec2(987.f, 312.f), Vec2(0.f, 0.f), Vec2(7.f, 0.f), 3, 1, 3, 0.1f);
	//GetAnimator()->FindAnimation(L"ScorpGal_Attack3_L")->Save(L"animation\\monster\\ScorpGal_Attack3_L.anim");
	//GetAnimator()->CreateAnimation(L"ScorpGal_Attack3_R", ScorpGal_R, Vec2(8953.f, 1323.f), Vec2(987.f, 312.f), Vec2(0.f, 0.f), Vec2(7.f, 0.f), 3, 1, 3, 0.1f);
	//GetAnimator()->FindAnimation(L"ScorpGal_Attack3_R")->Save(L"animation\\monster\\ScorpGal_Attack3_R.anim");

	GetAnimator()->LoadAnimation(L"animation\\monster\\ScorpGal_Idle_L.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\ScorpGal_Idle_R.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\ScorpGal_LtoR.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\ScorpGal_RtoL.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\ScorpGal_Walk_L.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\ScorpGal_Walk_R.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\ScorpGal_Block_L.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\ScorpGal_Block_R.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\ScorpGal_Attack1_L.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\ScorpGal_Attack1_R.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\ScorpGal_Attack2_L.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\ScorpGal_Attack2_R.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\ScorpGal_Attack3_L.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\ScorpGal_Attack3_R.anim");
}
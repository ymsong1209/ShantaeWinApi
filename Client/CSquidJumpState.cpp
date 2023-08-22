#include "pch.h"
#include "CSquidJumpState.h"
#include "CSquidBaron.h"
#include "CTimeMgr.h"
#include "CAnimator.h"
#include "CRigidbody.h"
#include "CSquidBaron_ElecSmall.h"
#include "CSquidBaron_ElecBig.h"
#include "CResMgr.h"
#include "CSound.h"

CSquidJumpState::CSquidJumpState()
{
}

CSquidJumpState::~CSquidJumpState()
{
}

void CSquidJumpState::finaltick()
{
	CSquidBaron* pMon = dynamic_cast<CSquidBaron*>(GetOwnerObj());
	if (pMon->GetMonInfo().m_bJumpPoint1 == false) {
		if (pMon->GetRigidbody()->GetGravityUse() == false) {
			CSound* JumpSound = CResMgr::GetInst()->LoadSound(L"baronjump", L"sound\\monster\\baron_jump.wav");
			JumpSound->SetVolume(70);
			JumpSound->Play();
			Vec2 JumpPoint1 = Vec2(800.f, 300.f);
			Vec2 vMonPos = pMon->GetPos();
			Vec2 vMontoJumpPoint = JumpPoint1 - vMonPos;
			vMontoJumpPoint.Normalize();
			float fSpeed = pMon->GetMonInfo().m_fSpeed;
			vMonPos += vMontoJumpPoint * DT * fSpeed;
			pMon->SetPos(vMonPos);
			if (vMonPos.y < 302.f) {
				pMon->GetRigidbody()->SetGravity(true);
				pMon->GetRigidbody()->SetGravityAccel(1500.f);
				pMon->GetRigidbody()->SetGravityVelocityLimit(1500.f);
			}
		}
		else if (pMon->GetRigidbody()->GetGravityUse() == true) {
			if (pMon->GetRigidbody()->GetGround() == true) {
				if (pMon->GetMonInfo().m_bIsArmored == true) {
					pMon->GetAnimator()->Play(L"SquidBaron_Armor_Jump3", false);
				}
				else {
					pMon->GetAnimator()->Play(L"SquidBaron_Jump3", false);
				}
				//傍拜 积己
				
				CCamera::GetInst()->CameraShake(5.0, 150.f, 0.5f);
				CObj* shockwave_small1 = new CSquidBaron_ElecSmall(pMon, 0.f);
				CObj* shockwave_small2 = new CSquidBaron_ElecSmall(pMon, 180.f);
				Instantiate(shockwave_small1, Vec2(pMon->GetPos().x, pMon->GetPos().y - 20.f), LAYER::MONSTER_PROJECTILE);
				Instantiate(shockwave_small2, Vec2(pMon->GetPos().x, pMon->GetPos().y - 20.f), LAYER::MONSTER_PROJECTILE);
				/*Instantiate(shockwave_small1, pMon->GetPos(), LAYER::MONSTER_PROJECTILE);
				Instantiate(shockwave_small2, pMon->GetPos(), LAYER::MONSTER_PROJECTILE);*/
				pMon->GetMonInfo().m_bJumpPoint1 = true;
				pMon->GetRigidbody()->SetGravity(false);
			}
			else {
				if (pMon->GetMonInfo().m_bIsArmored == true) {
					pMon->GetAnimator()->Play(L"SquidBaron_Armor_Jump2", false);
				}
				else {
					pMon->GetAnimator()->Play(L"SquidBaron_Jump2", true);
				}
			}
		}
		
	}
	else if (pMon->GetMonInfo().m_bJumpPoint2 == false && (pMon->GetAnimator()->AnimationFinish(L"SquidBaron_Jump3")||pMon->GetAnimator()->AnimationFinish(L"SquidBaron_Armor_Jump3"))) {
		if (pMon->GetRigidbody()->GetGravityUse() == false) {
			CSound* JumpSound = CResMgr::GetInst()->LoadSound(L"baronjump", L"sound\\monster\\baron_jump.wav");
			JumpSound->SetVolume(70);
			JumpSound->Play();
			if (pMon->GetMonInfo().m_bIsArmored == true) {
				pMon->GetAnimator()->Play(L"SquidBaron_Armor_Jump1", true);
			}
			else {
				pMon->GetAnimator()->Play(L"SquidBaron_Jump1", true);
			}
			
			Vec2 JumpPoint2 = Vec2(1150.f, 300.f);
			Vec2 vMonPos = pMon->GetPos();
			Vec2 vMontoJumpPoint = JumpPoint2 - vMonPos;
			vMontoJumpPoint.Normalize();
			float fSpeed = pMon->GetMonInfo().m_fSpeed;
			vMonPos += vMontoJumpPoint * DT * fSpeed;
			pMon->SetPos(vMonPos);
			if (vMonPos.y < 302.f) {
				pMon->GetRigidbody()->SetGravity(true);
				pMon->GetRigidbody()->SetGravityAccel(1500.f);
				pMon->GetRigidbody()->SetGravityVelocityLimit(1500.f);
			}
		}
		else if (pMon->GetRigidbody()->GetGravityUse() == true) {
			if (pMon->GetRigidbody()->GetGround() == true) {
				if (pMon->GetMonInfo().m_bIsArmored == true) {
					pMon->GetAnimator()->Play(L"SquidBaron_Armor_Jump3", false);
				}
				else {
					pMon->GetAnimator()->Play(L"SquidBaron_Jump3", false);
				}
				//傍拜 积己
				
				CCamera::GetInst()->CameraShake(5.0, 150.f, 0.5f);
				CObj* shockwave_small3 = new CSquidBaron_ElecSmall(pMon, 0.f);
				CObj* shockwave_small4 = new CSquidBaron_ElecSmall(pMon, 180.f);
				Instantiate(shockwave_small3, Vec2(pMon->GetPos().x, pMon->GetPos().y - 20.f), LAYER::MONSTER_PROJECTILE);
				Instantiate(shockwave_small4, Vec2(pMon->GetPos().x, pMon->GetPos().y - 20.f), LAYER::MONSTER_PROJECTILE);
				/*Instantiate(shockwave_small3, pMon->GetPos(), LAYER::MONSTER_PROJECTILE);
				Instantiate(shockwave_small4, pMon->GetPos(), LAYER::MONSTER_PROJECTILE);*/
				pMon->GetMonInfo().m_bJumpPoint2 = true;
				pMon->GetRigidbody()->SetGravity(false);
			}
			else {
				if (pMon->GetMonInfo().m_bIsArmored == true) {
					pMon->GetAnimator()->Play(L"SquidBaron_Armor_Jump2", false);
				}
				else {
					pMon->GetAnimator()->Play(L"SquidBaron_Jump2", true);
				}
			}
		}
	}
	else if (pMon->GetMonInfo().m_bJumpPoint3 == false && (pMon->GetAnimator()->AnimationFinish(L"SquidBaron_Jump3") || pMon->GetAnimator()->AnimationFinish(L"SquidBaron_Armor_Jump3"))) {
		if (pMon->GetRigidbody()->GetGravityUse() == false) {
			CSound* JumpSound = CResMgr::GetInst()->LoadSound(L"baronjump", L"sound\\monster\\baron_jump.wav");
			JumpSound->SetVolume(70);
			JumpSound->Play();
			if (pMon->GetMonInfo().m_bIsArmored == true) {
				pMon->GetAnimator()->Play(L"SquidBaron_Armor_Jump1", true);
			}
			else {
				pMon->GetAnimator()->Play(L"SquidBaron_Jump1", true);
			}
			Vec2 JumpPoint3 = Vec2(450.f, 300.f);
			Vec2 vMonPos = pMon->GetPos();
			Vec2 vMontoJumpPoint = JumpPoint3 - vMonPos;
			vMontoJumpPoint.Normalize();
			float fSpeed = pMon->GetMonInfo().m_fSpeed;
			vMonPos += vMontoJumpPoint * DT * fSpeed;
			pMon->SetPos(vMonPos);
			if (vMonPos.y < 302.f) {
				pMon->GetRigidbody()->SetGravity(true);
				pMon->GetRigidbody()->SetGravityAccel(1500.f);
				pMon->GetRigidbody()->SetGravityVelocityLimit(1500.f);
			}
		}
		else if (pMon->GetRigidbody()->GetGravityUse() == true) {
			if (pMon->GetRigidbody()->GetGround() == true) {
				if (pMon->GetMonInfo().m_bIsArmored == true) {
					pMon->GetAnimator()->Play(L"SquidBaron_Armor_Jump3", false);
				}
				else {
					pMon->GetAnimator()->Play(L"SquidBaron_Jump3", false);
				}
				//傍拜 积己
				CCamera::GetInst()->CameraShake(5.0, 150.f, 0.5f);
				CObj* shockwave_small5 = new CSquidBaron_ElecBig(pMon, 0.f);
				CObj* shockwave_small6 = new CSquidBaron_ElecBig(pMon, 180.f);
				Instantiate(shockwave_small5, Vec2(pMon->GetPos().x, pMon->GetPos().y - 20.f), LAYER::MONSTER_PROJECTILE);
				Instantiate(shockwave_small6, Vec2(pMon->GetPos().x, pMon->GetPos().y - 20.f), LAYER::MONSTER_PROJECTILE);
				/*Instantiate(shockwave_small5, pMon->GetPos(), LAYER::MONSTER_PROJECTILE);
				Instantiate(shockwave_small6, pMon->GetPos(), LAYER::MONSTER_PROJECTILE);*/
				pMon->GetMonInfo().m_bJumpPoint3 = true;
				pMon->GetRigidbody()->SetGravity(false);
			}
			else {
				if (pMon->GetMonInfo().m_bIsArmored == true) {
					pMon->GetAnimator()->Play(L"SquidBaron_Armor_Jump2", false);
				}
				else {
					pMon->GetAnimator()->Play(L"SquidBaron_Jump2", true);
				}
			}
		}
	}
	else {
			if (pMon->GetAnimator()->AnimationFinish(L"SquidBaron_Jump3") || pMon->GetAnimator()->AnimationFinish(L"SquidBaron_Armor_Jump3")) {
				if (pMon->GetMonInfo().m_bIsArmored == true) {
					pMon->GetAI()->ChangeState(L"BuildUp");
				}
				else {
					pMon->GetAI()->ChangeState(L"Gobble");
				}
				
			}
	}
	
	
}

void CSquidJumpState::Enter()
{
	CSquidBaron* pMon = dynamic_cast<CSquidBaron*>(GetOwnerObj());

	pMon->GetRigidbody()->SetGravity(false);
	if (pMon->GetMonInfo().m_bIsArmored == true) {
		pMon->GetMonInfo().m_fSpeed = 1300.f;
		pMon->AdjustCollider(L"SquidBaron_Armor_Jump1", Vec2(171.f, 168.f), Vec2(24.f, 5451.f));
		pMon->GetAnimator()->Play(L"SquidBaron_Armor_Jump1", true);
	}
	else {
		pMon->GetMonInfo().m_fSpeed = 1000.f;
		pMon->AdjustCollider(L"SquidBaron_Jump1", Vec2(171.f, 168.f), Vec2(24.f, 1815.f));
		pMon->GetAnimator()->Play(L"SquidBaron_Jump1", true);
	}
	
	
	
}

void CSquidJumpState::Exit()
{
	CSquidBaron* pMon = dynamic_cast<CSquidBaron*>(GetOwnerObj());
	pMon->GetRigidbody()->SetGravity(true);
	pMon->GetMonInfo().m_bJumpPoint1 = false;
	pMon->GetMonInfo().m_bJumpPoint2 = false;
	pMon->GetMonInfo().m_bJumpPoint3 = false;
}



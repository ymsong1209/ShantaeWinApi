#include "pch.h"
#include "CKeyMgr.h"
#include "CPlayer.h"
#include "CRigidbody.h"
#include "CCollider.h"
#include "CMonster.h"
#include "CScareCrowVomit.h"
#include "CMonsterBullet.h"
#include "CScorpGalAttack.h"
#include "CSquidBaron_ElecSmall.h"
#include "CSquidBaron_ElecBig.h"
#include "CSquidSmith.h"
#include "CLevelChangeInteract.h"

void CPlayer::BeginOverlap(CCollider* _pOther)
{
	//몬스터 피격
	CMonster* cMonster = dynamic_cast<CMonster*>(_pOther->GetOwner());
	if (nullptr != cMonster) {
		if (m_EState == PLAYER_STATE::NORMAL && m_bInvincible == false) {
			m_btick = true;
			m_EState = PLAYER_STATE::HIT;
			--m_iHP;
			UpdateHeartContainer();
		}
	}
	CScareCrowVomit* cVomit = dynamic_cast<CScareCrowVomit*>(_pOther->GetOwner());
	if (nullptr != cVomit) {
		if (m_EState == PLAYER_STATE::NORMAL && m_bInvincible == false) {
			m_btick = true;
			m_EState = PLAYER_STATE::HIT;
			m_iHP -= cVomit->ReturnDmg();
			UpdateHeartContainer();
		}
	}

	CMonsterBullet* cBullet = dynamic_cast<CMonsterBullet*>(_pOther->GetOwner());
	if (nullptr != cBullet) {
		if (m_EState == PLAYER_STATE::NORMAL && m_bInvincible == false) {
			m_btick = true;
			m_EState = PLAYER_STATE::HIT;
			m_iHP -= cBullet->ReturnDmg();
			UpdateHeartContainer();
		}
	}

	CScorpGalAttack* cScorpGalAttack = dynamic_cast<CScorpGalAttack*>(_pOther->GetOwner());
	if (nullptr != cScorpGalAttack) {
		if (m_EState == PLAYER_STATE::NORMAL && m_bInvincible == false) {
			m_btick = true;
			m_EState = PLAYER_STATE::HIT;
			m_iHP -= cScorpGalAttack->ReturnDmg();
			UpdateHeartContainer();
		}
	}

	CSquidBaron_ElecSmall* cShockSmall = dynamic_cast<CSquidBaron_ElecSmall*>(_pOther->GetOwner());
	if (nullptr != cShockSmall) {
		if (m_EState == PLAYER_STATE::NORMAL && m_bInvincible == false) {
			m_btick = true;
			m_EState = PLAYER_STATE::HIT;
			m_iHP -= cShockSmall->ReturnDmg();
			UpdateHeartContainer();
		}
	}

	CSquidBaron_ElecBig* cShockBig = dynamic_cast<CSquidBaron_ElecBig*>(_pOther->GetOwner());
	if (nullptr != cShockBig) {
		if (m_EState == PLAYER_STATE::NORMAL && m_bInvincible == false) {
			m_btick = true;
			m_EState = PLAYER_STATE::HIT;
			m_iHP -= cShockBig->ReturnDmg();
			UpdateHeartContainer();
		}
	}
}

void CPlayer::OnOverlap(CCollider* _pOther)
{
	CMonster* cMonster = dynamic_cast<CMonster*>(_pOther->GetOwner());
	if (nullptr != cMonster) {
		if (m_EState == PLAYER_STATE::NORMAL && m_bInvincible == false) {
			m_btick = true;
			m_EState = PLAYER_STATE::HIT;
			m_iHP -= (int)cMonster->GetMonInfo().m_fAtt;
			UpdateHeartContainer();
		}
	}
	CScareCrowVomit* cVomit = dynamic_cast<CScareCrowVomit*>(_pOther->GetOwner());
	if (nullptr != cVomit) {
		if (m_EState == PLAYER_STATE::NORMAL && m_bInvincible == false) {
			m_btick = true;
			m_EState = PLAYER_STATE::HIT;
			m_iHP -= cVomit->ReturnDmg();
			UpdateHeartContainer();
		}
	}

	CMonsterBullet* cBullet = dynamic_cast<CMonsterBullet*>(_pOther->GetOwner());
	if (nullptr != cBullet) {
		if (m_EState == PLAYER_STATE::NORMAL && m_bInvincible == false) {
			m_btick = true;
			m_EState = PLAYER_STATE::HIT;
			m_iHP -= cBullet->ReturnDmg();
			UpdateHeartContainer();
		}
	}

	CSquidSmith* cSmith = dynamic_cast<CSquidSmith*>(_pOther->GetOwner());
	if (nullptr != cSmith) {
		if (IsTap(KEY::UP)) {
			if (m_iSquidHeart > 3 && !(cSmith->ReturnForge()) && m_iMoney>=100) {
				cSmith->Slam();
			}
		}
		
	}
	

	CLevelChangeInteract* cInteract = dynamic_cast<CLevelChangeInteract*>(_pOther->GetOwner());
	if (nullptr != cInteract) {
		if (IsTap(KEY::UP)) {
			GetRigidbody()->SetVelocity(Vec2(0.f, 0.f));
			m_EAnim = PLAYER_ANIM::ENTER;
			cInteract->LevelChange();
		}

	}
	int a = 0;
}

void CPlayer::EndOverlap(CCollider* _pOther)
{

}
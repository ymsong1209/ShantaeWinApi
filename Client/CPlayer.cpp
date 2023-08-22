#include "pch.h"
#include "CPlayer.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CPathMgr.h"
#include "CEventMgr.h"
#include "CSound.h"
#include "CTexture.h"
#include "CResMgr.h"

#include "CMissile.h"
#include "CPistol.h"
#include "CWhip.h"
#include "CScimitar.h"
#include "CMonster.h"
#include "CPikeBall.h"
#include "CHealEffect.h"
#include "CDust.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CRigidbody.h"
#include "CPlayerInfo.h"
#include "CPlatform.h"

CPlayer::CPlayer()
	: m_fSpeed(100.f)
	, pShantaeTex(nullptr)
	, pShantaeTex_R(nullptr)
	, m_EAnim(PLAYER_ANIM::NONE)
	, m_EPrevAnim(PLAYER_ANIM::NONE)
	, m_EDir(PLAYER_DIR::NONE)
	, m_EPrevDir(PLAYER_DIR::NONE)
	, m_EState(PLAYER_STATE::NONE)
	, m_EPrevState(PLAYER_STATE::NONE)
	, m_fTime(0.f)
	, m_iHP(0)
	, m_iMaxHp(0)
	, m_iWhipDmg(0)
	, m_iPistolDmg(0)
	, m_iScimitarDmg(0)
	, m_iWhipExtraDmg(0)
	, m_iPistolExtraDmg(0)
	, m_iScimitarExtraDmg(0)
	, m_iMeatCount(0)
	, m_iMonsterMilkCount(0)
	, m_iPikeBallCount(0)
	, m_bMonsterMilk(false)
	, m_bPikeBall(false)
	, m_fExtraDmgTime(0.f)
	, m_iMoney(0)
	, m_iSquidHeart(0)
	, m_fAttvoiceCooldown(0)
	, m_bInvincible(false)
	, m_fInvincibleTime(0.f)
	, m_bForceDuck(false)
	, m_bHitAir(true)
	, m_bAttack(true)
	, m_btick(true)
	, m_bCamerafollow(false)
	, m_bforceinvincible(false)
	, m_vSpawnPos{}
	, m_bSpawnChange(false)
	
{
	//pShantaeTex = CResMgr::GetInst()->LoadTexture(L"Shantae_L", L"texture\\player\\Shantae_original_L.bmp");
	//pShantaeTex_R = CResMgr::GetInst()->LoadTexture(L"Shantae_R", L"texture\\player\\Shantae_original_R.bmp");
	
	m_EAnim = CPlayerInfo::GetInst()->ReturnAnim();
	m_EDir = CPlayerInfo::GetInst()->ReturnDir();
	m_EState = CPlayerInfo::GetInst()->ReturnState();
	m_iHP = CPlayerInfo::GetInst()->ReturnHP();
	m_iMaxHp = CPlayerInfo::GetInst()->ReturnMaxHP();
	m_iWhipDmg = CPlayerInfo::GetInst()->ReturnWhipDmg();
	m_iPistolDmg = CPlayerInfo::GetInst()->ReturnPistolDmg();
	m_iScimitarDmg = CPlayerInfo::GetInst()->ReturnScimitarDmg();
	m_iWhipExtraDmg = CPlayerInfo::GetInst()->ReturnWhipExtraDmg();
	m_iPistolExtraDmg = CPlayerInfo::GetInst()->ReturnPistolExtraDmg();
	m_iScimitarExtraDmg = CPlayerInfo::GetInst()->ReturnScimitarExtraDmg();
	m_iMeatCount = CPlayerInfo::GetInst()->ReturnMeat();
	m_iMonsterMilkCount = CPlayerInfo::GetInst()->ReturnMonsterMilk();
	m_iPikeBallCount = CPlayerInfo::GetInst()->ReturnPikeBall();
	m_iMoney = CPlayerInfo::GetInst()->ReturnMoney();
	m_iSquidHeart = CPlayerInfo::GetInst()->ReturnSquidHeart();
	m_bSpawnChange = CPlayerInfo::GetInst()->ReturnSpawnChange();
	m_vSpawnPos = CPlayerInfo::GetInst()->ReturnSpawnPos();

	if (m_EAnim == PLAYER_ANIM::ENTER) m_EAnim = PLAYER_ANIM::IDLE;
	CreateAnimator();
	
	CreateAnimation();
	UpdateHeartContainer();
	UpdateMoney();
	UpdateItem();

	CreateCollider();
	CreateRigidbody();

	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(100.f, 120.f));

	// �ǰݵɽ� ���ĺ���ó��. default�� transparentblt�������
	GetAnimator()->SetAlphablend(false);
	// �÷��̾��� �߽��� �ٴڿ� �д�.
	GetAnimator()->SetFloorPlay(true);
	// Rigidbody ����	
	GetRigidbody()->SetFriction(480.f);
	GetRigidbody()->SetGravity(true);
	GetRigidbody()->SetGravityAccel(800.f);

	GetRigidbody()->SetVelocityLimit(300.f);
	GetRigidbody()->SetGravityVelocityLimit(1000.f);


}

CPlayer::CPlayer(const CPlayer& _other)
	: CObj(_other)
	, m_fSpeed(_other.m_fSpeed)
	, pShantaeTex(_other.pShantaeTex)
	, pShantaeTex_R(_other.pShantaeTex_R)
	, m_EAnim(_other.m_EAnim)
	, m_EPrevAnim(_other.m_EPrevAnim)
	, m_EDir(_other.m_EDir)
	, m_EPrevDir(_other.m_EPrevDir)
	, m_EState(_other.m_EState)
	, m_EPrevState(_other.m_EPrevState)
	, m_fTime(_other.m_fTime)
	, m_iHP(_other.m_iHP)
	, m_iMaxHp(_other.m_iMaxHp)
	, m_iWhipDmg(_other.m_iWhipDmg)
	, m_iPistolDmg(_other.m_iPistolDmg)
	, m_iScimitarDmg(_other.m_iScimitarDmg)
	, m_iWhipExtraDmg(_other.m_iWhipExtraDmg)
	, m_iPistolExtraDmg(_other.m_iWhipExtraDmg)
	, m_iScimitarExtraDmg(_other.m_iScimitarExtraDmg)
	, m_iMeatCount(_other.m_iMeatCount)
	, m_iMonsterMilkCount(_other.m_iMonsterMilkCount)
	, m_iPikeBallCount(_other.m_iPikeBallCount)
	, m_bMonsterMilk(_other.m_bMonsterMilk) 
	, m_bPikeBall(_other.m_bPikeBall)
	, m_fExtraDmgTime(_other.m_fExtraDmgTime)
	, m_iMoney(_other.m_iMoney)
	, m_iSquidHeart(_other.m_iSquidHeart)
	, m_fAttvoiceCooldown(_other.m_fAttvoiceCooldown)
	, m_bInvincible(_other.m_bInvincible)
	, m_fInvincibleTime(_other.m_fInvincibleTime)
	, m_bForceDuck(_other.m_bForceDuck)
	, m_bHitAir(_other.m_bHitAir)
	, m_bAttack(_other.m_bAttack)
	, m_btick(_other.m_btick)
	, m_bCamerafollow(_other.m_bCamerafollow)
	, m_bforceinvincible(_other.m_bforceinvincible)
{
}

CPlayer::~CPlayer()
{
	//�÷��̾� ������ ������ ������ ������Ʈ
	CPlayerInfo::GetInst()->SetAnim(m_EAnim);
	CPlayerInfo::GetInst()->SetDir(m_EDir);
	CPlayerInfo::GetInst()->SetState(m_EState);
	CPlayerInfo::GetInst()->SetHP(m_iHP);
	CPlayerInfo::GetInst()->SetMaxHP(m_iMaxHp);
	CPlayerInfo::GetInst()->SetWhipDmg(m_iWhipDmg);
	CPlayerInfo::GetInst()->SetPistolDmg(m_iPistolDmg);
	CPlayerInfo::GetInst()->SetScimitarDmg(m_iScimitarDmg);
	CPlayerInfo::GetInst()->SetWhipExtraDmg(m_iWhipExtraDmg);
	CPlayerInfo::GetInst()->SetPistolExtraDmg(m_iScimitarExtraDmg);
	CPlayerInfo::GetInst()->SetScimitarExtraDmg(m_iScimitarExtraDmg);
	CPlayerInfo::GetInst()->SetMeat(m_iMeatCount);
	CPlayerInfo::GetInst()->SetMonsterMilk(m_iMonsterMilkCount);
	CPlayerInfo::GetInst()->SetPikeBall(m_iPikeBallCount);

	CPlayerInfo::GetInst()->SetMoney(m_iMoney);
	CPlayerInfo::GetInst()->SetSquidHeart(m_iSquidHeart);
	CPlayerInfo::GetInst()->SetSpawnPos(m_vSpawnPos);
	CPlayerInfo::GetInst()->SetSpawnChange(m_bSpawnChange);
}

void CPlayer::tick()
{	
	
	m_fAttvoiceCooldown += DT;
	// MonsterMilk ó��
	if (m_bMonsterMilk) {
		m_fExtraDmgTime += DT;
		if (m_fExtraDmgTime > 30.f) {
			m_bMonsterMilk = false;
			m_fExtraDmgTime = 0.f;
		}
	}

	if (m_bCamerafollow) {
		Vec2 PlayerPrevPos = GetPrevPos();
		Vec2 PlayerCurPos = GetPos();
		Vec2 diff = PlayerCurPos - PlayerPrevPos;
		Vec2 vCamera = CCamera::GetInst()->GetLook();
		CCamera::GetInst()->SetLook(Vec2(vCamera.x + diff.x, vCamera.y + diff.y));
	}
	

	// �ǰ�����
	switch (m_EState)
	{
	case PLAYER_STATE::NORMAL: {
		// ��������, �ǰ� ��� ���Ŀ� ���
		if (m_iHP == 0) {
			if (GetAnimator()->AnimationFinish(L"Die") || GetAnimator()->AnimationFinish(L"Die_R")) {
				if (GetAnimator()->AnimationFinish(L"Wakeup") || GetAnimator()->AnimationFinish(L"Wakeup_R")) {
					m_iHP = m_iMaxHp;
					UpdateHeartContainer();
					GetAnimator()->AnimationReset(L"Die");
					GetAnimator()->AnimationReset(L"Die_R");
					GetAnimator()->AnimationReset(L"Wakeup");
					GetAnimator()->AnimationReset(L"Wakeup_R");
					m_btick = true;
					m_EAnim = PLAYER_ANIM::IDLE;
					CObj::tick();
					return;
				}

				if (IsTap(KEY::_0)) {
					if (m_EDir == PLAYER_DIR::LEFT) {
						GetAnimator()->Play(L"Wakeup", false);
						CObj::tick();
						return;
					}
					else if (m_EDir == PLAYER_DIR::RIGHT) {
						GetAnimator()->Play(L"Wakeup_R", false);
						CObj::tick();
						return;
					}
				}
			}
			else {
				if (m_EDir == PLAYER_DIR::LEFT) {
					AdjustCollider(L"Die", Vec2(65.f, 62.f), Vec2(67.f, 15559.f));
					GetAnimator()->Play(L"Die", false);
					CObj::tick();
					return;
				}
				else if (m_EDir == PLAYER_DIR::RIGHT) {
					AdjustCollider(L"Die_R", Vec2(65.f, 62.f), Vec2(67.f, 15559.f));
					GetAnimator()->Play(L"Die_R", false);
					CObj::tick();
					return;
				}
			}
			CObj::tick();
			return;
		}
		// ��������
		if (m_bforceinvincible == true) {
			GetAnimator()->SetAlphablend(true);
			if (m_iHP != m_iMaxHp) {
				m_iHP = m_iMaxHp;
				UpdateHeartContainer();
			}
			if (m_iMeatCount < 9 || m_iMonsterMilkCount < 9 || m_iPikeBallCount < 9) {
				m_iMeatCount = 9;
				m_iMonsterMilkCount = 9;
				m_iPikeBallCount = 9;
				UpdateItem();
			}
		
			m_bInvincible = true;
		}
		//�ǰݽ� ����
		else {
			if (m_bInvincible) {
				GetAnimator()->SetAlphablend(true);
				m_fInvincibleTime += DT;
				if (m_fInvincibleTime > 3.f) {
					GetAnimator()->SetAlphablend(false);
					m_bInvincible = false;
					m_fInvincibleTime = 0.f;
				}
			}
		}
		
		

		// �ִϸ��̼� �б���
		switch (m_EAnim)
		{

		case PLAYER_ANIM::IDLE:
		{
			GetRigidbody()->SetVelocityLimit(300.f);
			// Idle Motion
			m_fTime += DT;
			if (m_EDir == PLAYER_DIR::LEFT) {
				Update();
				if (m_iHP == 1) {
					AdjustCollider(L"Hurt", Vec2(75.f, 117.f), Vec2(39.f, 14202.f));
					GetAnimator()->Play(L"Hurt", true);
				}
				else {
					if (m_fTime < 3.0f) {
						AdjustCollider(L"Standing_Idle", Vec2(71.f, 123.f), Vec2(48.f, 42.f));
						GetAnimator()->Play(L"Standing_Idle", true);
					}
					else {
						AdjustCollider(L"Standing_Idle_Long", Vec2(72.f, 114.f), Vec2(90.f, 552.f));
						GetAnimator()->Play(L"Standing_Idle_Long", false);
						if (GetAnimator()->AnimationFinish(L"Standing_Idle_Long")) {
							m_fTime = 0.f;
						}
					}
				}
			}
			else if (m_EDir == PLAYER_DIR::RIGHT) {
				Update();
				if (m_iHP == 1) {
					AdjustCollider(L"Hurt_R", Vec2(75.f, 117.f), Vec2(42.f, 14202.f));
					GetAnimator()->Play(L"Hurt_R", true);
				}
				else {
					if (m_fTime < 3.0f) {
						AdjustCollider(L"Standing_Idle_R", Vec2(71.f, 123.f), Vec2(37.f, 42.f));
						GetAnimator()->Play(L"Standing_Idle_R", true);
					}
					else {
						AdjustCollider(L"Standing_Idle_Long", Vec2(72.f, 114.f), Vec2(66.f, 552.f));
						GetAnimator()->Play(L"Standing_Idle_Long_R", false);
						if (GetAnimator()->AnimationFinish(L"Standing_Idle_Long_R")) {
							m_fTime = 0.f;
						}
					}
				}
			}

			// State change
			if (IsTap(KEY::LEFT) || IsPressed(KEY::LEFT))
			{
				Update();
				m_EAnim = PLAYER_ANIM::RUN;
				m_EDir = PLAYER_DIR::LEFT;
				m_fTime = 0.f;
			}
			else if (IsTap(KEY::RIGHT) || IsPressed(KEY::RIGHT))
			{
				Update();
				m_EAnim = PLAYER_ANIM::RUN;
				m_EDir = PLAYER_DIR::RIGHT;
				m_fTime = 0.f;
			}
			if (IsTap(KEY::DOWN) || IsPressed(KEY::DOWN)) {
				Update();
				m_EAnim = PLAYER_ANIM::DUCK;
			}
			else if (IsTap(KEY::Z)) {
				Update();
				m_EAnim = PLAYER_ANIM::ATTACK;
				m_fTime = 0.f;
			}
			else if (IsTap(KEY::X))
			{
				Update();
				m_EAnim = PLAYER_ANIM::JUMP;
				Vec2 V = GetRigidbody()->GetVelocity();

				if (0.f < V.y)
				{
					GetRigidbody()->AddVelocity(Vec2(0.f, -(V.y + 600.f)));
				}
				else
				{
					GetRigidbody()->AddVelocity(Vec2(0.f, -600.f));
				}
				m_fTime = 0.f;
			}
			else if (IsTap(KEY::SPACE)) {
				Update();
				m_EAnim = PLAYER_ANIM::SHOOT;
				GetRigidbody()->SetVelocity(Vec2(0.f, 0.f));
				m_fTime = 0.f;
			}
			else if (IsTap(KEY::_1)) {
				//���� ü���� �ִ�ü�º��� ���� ���, ��� �����Ұ��
				if ( m_iMeatCount>0 && m_iHP<m_iMaxHp) {
					Update();
					--m_iMeatCount;
					UpdateItem();
					GetRigidbody()->SetVelocity(Vec2(0.f, 0.f));
					m_EAnim = PLAYER_ANIM::EAT;
					m_fTime = 0.f;
				}
			}
			else if (IsTap(KEY::_2)) {
				Update();
				if (m_iMonsterMilkCount > 0 && !m_bMonsterMilk) {
					m_EAnim = PLAYER_ANIM::DRINK;
					m_fTime = 0.f;
					GetRigidbody()->SetVelocity(Vec2(0.f, 0.f));
					--m_iMonsterMilkCount;
					UpdateItem();
				}
			}
			else if (IsTap(KEY::_3)) {
				//Pikeball�� ��ȯ�ȉ������, Pikeball�� 1���̻��� ���
				if (!m_bPikeBall && m_iPikeBallCount>0) {
					Update();
					CSound* pikeball = CResMgr::GetInst()->LoadSound(L"pikeball", L"sound\\player\\vo_a_pike_ball_01 [1].wav");
					pikeball->SetVolume(40);
					pikeball->Play();
					CObj* cPikeBall = new CPikeBall(this);
					Instantiate(cPikeBall, GetPos(), LAYER::PLAYER_PROJECTILE);
					m_bPikeBall = true;
					--m_iPikeBallCount;
					UpdateItem();
				}
			}
	
		}
		break;
		case PLAYER_ANIM::RUN:
		{
			GetRigidbody()->SetVelocityLimit(400.f);
			// �޸��ٰ� ����
			if (GetRigidbody()->GetGround() == false) {
				Update();
				m_EAnim = PLAYER_ANIM::FALL;
			}
			if (IsPressed(KEY::LEFT)) {
				Update();
				m_EDir = PLAYER_DIR::LEFT;
				GetRigidbody()->SetVelocity(Vec2(-400.f, 0.f));
				AdjustCollider(L"Run", Vec2(107.f, 100.f), Vec2(76.f, 2816.f));
				GetAnimator()->Play(L"Run", true);
				//Run_Stop�� �ѹ��̶� ���۵Ǹ� ������ �����ӿ� �����ϱ� reset

				GetAnimator()->AnimationReset(L"Run_Stop");
				GetAnimator()->AnimationReset(L"Run_Stop_R");
			}
			else if (IsPressed(KEY::RIGHT)) {
				Update();
				m_EDir = PLAYER_DIR::RIGHT;
				GetRigidbody()->SetVelocity(Vec2(400.f, 0.f));
				AdjustCollider(L"Run_R", Vec2(107.f, 100.f), Vec2(71.f, 2817.f));
				GetAnimator()->Play(L"Run_R", true);
				GetAnimator()->AnimationReset(L"Run_Stop");
				GetAnimator()->AnimationReset(L"Run_Stop_R");
			}
			if (IsRelease(KEY::LEFT)) {
				GetRigidbody()->SetVelocity(Vec2(0.f, 0.f));
				AdjustCollider(L"Run_Stop", Vec2(107.f, 100.f), Vec2(79.f, 3152.f));
				GetAnimator()->Play(L"Run_Stop", false);
			}
			if (IsRelease(KEY::RIGHT)) {
				GetRigidbody()->SetVelocity(Vec2(0.f, 0.f));
				AdjustCollider(L"Run_Stop_R", Vec2(107.f, 100.f), Vec2(86.f, 3152.f));
				GetAnimator()->Play(L"Run_Stop_R", false);
			}
			//Run_Stop�� �� ����Ǹ� Idle�� ����
			if (GetAnimator()->AnimationFinish(L"Run_Stop")) {
				Update();
				m_EAnim = PLAYER_ANIM::IDLE;
			}
			if (GetAnimator()->AnimationFinish(L"Run_Stop_R")) {
				Update();
				m_EAnim = PLAYER_ANIM::IDLE;
			}
			// �޸��� ���߿� �ɱ�
			if (IsTap(KEY::DOWN)) {
				Update();
				GetRigidbody()->SetVelocity(Vec2(0.f, 0.f));
				m_EAnim = PLAYER_ANIM::DUCK;
			}
			// �޸��� ���߿� ��Ÿ
			if (IsTap(KEY::Z)) {
				Update();
				m_EAnim = PLAYER_ANIM::ATTACK;
			}
			// �޸��� ���߿� ����
			if (IsTap(KEY::X))
			{
				Update();
				m_btick = true;
				m_EAnim = PLAYER_ANIM::JUMP;
				Vec2 V = GetRigidbody()->GetVelocity();

				if (0.f < V.y)
				{
					GetRigidbody()->AddVelocity(Vec2(0.f, -(V.y + 600.f)));
				}
				else
				{
					GetRigidbody()->AddVelocity(Vec2(0.f, -600.f));
				}
			}
			//�޸��� ���߿� �ѽ��
			else if (IsTap(KEY::SPACE)) {
				Update();
				m_EAnim = PLAYER_ANIM::SHOOT;
				GetRigidbody()->SetVelocity(Vec2(0.f, 0.f));
			}

			else if (IsTap(KEY::_1)) {
				//���� ü���� �ִ�ü�º��� ���� ���, ��� �����Ұ��
				if (m_iMeatCount > 0 && m_iHP < m_iMaxHp) {
					Update();
					GetRigidbody()->SetVelocity(Vec2(0.f, 0.f));
					--m_iMeatCount;
					UpdateItem();
					m_EAnim = PLAYER_ANIM::EAT;
				}
			}
			else if (IsTap(KEY::_2)) {
				Update();
				if (m_iMonsterMilkCount > 0 && !m_bMonsterMilk) {
					--m_iMonsterMilkCount;
					UpdateItem();
					m_EAnim = PLAYER_ANIM::DRINK;
					GetRigidbody()->SetVelocity(Vec2(0.f, 0.f));
				}
			}
			else if (IsTap(KEY::_3)) {
				//Pikeball�� ���� ���, Pikeball�� 1���̻��� ���
				if (!m_bPikeBall && m_iPikeBallCount > 0) {
					Update();
					CSound* pikeball = CResMgr::GetInst()->LoadSound(L"pikeball", L"sound\\player\\vo_a_pike_ball_01 [1].wav");
					pikeball->SetVolume(40);
					pikeball->Play();
					CObj* cPikeBall = new CPikeBall(this);
					Instantiate(cPikeBall, GetPos(), LAYER::PLAYER_PROJECTILE);
					m_bPikeBall = true;
					--m_iPikeBallCount;
					UpdateItem();
				}
			}
			
		}
		break;
		case PLAYER_ANIM::DUCK: {
			// �ӵ� ����
			GetRigidbody()->SetVelocityLimit(150.f);

			//�Ʒ� Ű�� ������ ���
			if (IsPressed(KEY::DOWN)||m_bForceDuck == true) {
				//���� �ɾ��ִ� ����
				if (GetAnimator()->AnimationFinish(L"Duck") || GetAnimator()->AnimationFinish(L"Duck_R")) {
					
					// Crawl
					if (IsTap(KEY::LEFT) || IsPressed(KEY::LEFT)) {
						Update();
						m_EDir = PLAYER_DIR::LEFT;
						AdjustCollider(L"Crawl", Vec2(96.f, 57.f), Vec2(36.f, 5211.f));
						GetAnimator()->Play(L"Crawl", true);
						Vec2 vel = GetRigidbody()->GetVelocity();
						GetRigidbody()->SetVelocity(Vec2(-150.f, vel.y));
					}
					else if (IsTap(KEY::RIGHT) || IsPressed(KEY::RIGHT)) {
						Update();
						m_EDir = PLAYER_DIR::RIGHT;
						AdjustCollider(L"Crawl_R", Vec2(96.f, 57.f), Vec2(43.f, 5211.f));
						GetAnimator()->Play(L"Crawl_R", true);
						Vec2 vel = GetRigidbody()->GetVelocity();
						GetRigidbody()->SetVelocity(Vec2(150.f, vel.y));
					}
					// Duck Whip
					else if (IsTap(KEY::Z)) {
						Update();
						m_EAnim = PLAYER_ANIM::ATTACK;
					}
					//Idle Motion
					else {
						GetRigidbody()->SetVelocity(Vec2(0.f, 0.f));
						if (m_EDir == PLAYER_DIR::LEFT) {
							Update();
							AdjustCollider(L"Duck_Idle", Vec2(71.f, 57.f), Vec2(24.f, 4659.f));
							GetAnimator()->Play(L"Duck_Idle", true);
						}
						else if (m_EDir == PLAYER_DIR::RIGHT) {
							Update();
							AdjustCollider(L"Duck_Idle_R", Vec2(71.f, 57.f), Vec2(39.f, 4659.f));
							GetAnimator()->Play(L"Duck_Idle_R", true);
						}
					}
					

				}
				//�ɾ������� �ʴ�.
				else {
					if (m_EDir == PLAYER_DIR::LEFT) {
						Update();
						AdjustCollider(L"Duck", Vec2(61.f, 62.f), Vec2(47.f, 4525.f));
						GetAnimator()->Play(L"Duck", false);
					}
					else if (m_EDir == PLAYER_DIR::RIGHT) {
						Update();
						AdjustCollider(L"Duck_R", Vec2(61.f, 62.f), Vec2(48.f, 4525.f));
						GetAnimator()->Play(L"Duck_R", false);
					}
				}
			}
			
			// Animation Change
			// ���� �ٴ��� �ƴѵ�, �Ʒ� Ű�� �ѹ� ���ų� �̹� �����ִ� �����̴�.
			if (m_bForceDuck == false && (IsRelease(KEY::DOWN)||IsNone(KEY::DOWN)) ) {
				GetAnimator()->AnimationReset(L"Duck_R");
				GetAnimator()->AnimationReset(L"Duck");
				if (m_EDir == PLAYER_DIR::LEFT) {
					if (GetAnimator()->AnimationFinish(L"Standup")) {
						Update();
						m_EAnim = PLAYER_ANIM::IDLE;
					}
					else {
						AdjustCollider(L"Standup", Vec2(51.f, 57.f), Vec2(59.f, 14617.f));
						GetAnimator()->Play(L"Standup", true);
					}					
				}
				else if (m_EDir == PLAYER_DIR::RIGHT) {

					if (GetAnimator()->AnimationFinish(L"Standup_R")) {
						Update();
						m_EAnim = PLAYER_ANIM::IDLE;
					}
					else {
						AdjustCollider(L"Standup_R", Vec2(51.f, 57.f), Vec2(48.f, 14616.f));
						GetAnimator()->Play(L"Standup_R", true);
					}					
				}
			}
			
		}
		break;
		case PLAYER_ANIM::JUMP:
		{
			if (m_btick) {
				srand((UINT)CTimeMgr::GetInst()->ReturnCurCount());
				if (rand() % 3 == 0) {
					CSound* jumpsound = CResMgr::GetInst()->LoadSound(L"Jump_01", L"sound\\player\\vo_s_jump_01 [1].wav");
					jumpsound->SetVolume(25);
					jumpsound->Play();
				}
				else if (rand() % 3 == 1) {
					CSound* jumpsound = CResMgr::GetInst()->LoadSound(L"Jump_02", L"sound\\player\\vo_s_jump_02 [1].wav");
					jumpsound->SetVolume(25);
					jumpsound->Play();
				}
				else if (rand() % 3 == 2) {
					CSound* jumpsound = CResMgr::GetInst()->LoadSound(L"Jump_03", L"sound\\player\\vo_s_jump_05 [1].wav");
					jumpsound->SetVolume(25);
					jumpsound->Play();
				}
				else {
					CSound* jumpsound = CResMgr::GetInst()->LoadSound(L"Jump_03", L"sound\\player\\vo_s_jump_05 [1].wav");
					jumpsound->SetVolume(25);
					jumpsound->Play();
				}
				
				m_btick = false;
			}
			//���߿��� �߰� �¿��̵�
			if (IsPressed(KEY::LEFT)) {
				Update();
				m_EDir = PLAYER_DIR::LEFT;
				GetRigidbody()->AddVelocity(Vec2(-10.f, 0.f));
			}
			else if (IsPressed(KEY::RIGHT)) {
				Update();
				m_EDir = PLAYER_DIR::RIGHT;
				GetRigidbody()->AddVelocity(Vec2(10.f, 0.f));
			}
			// �����ִϸ��̼� ���
			if (m_EDir == PLAYER_DIR::LEFT) {
				if (GetAnimator()->AnimationFinish(L"Jump")) {
					AdjustCollider(L"Jump_Tuck", Vec2(58.f, 104.f), Vec2(47.f, 3857.f));
					GetAnimator()->Play(L"Jump_Tuck", false);
					if (IsTap(KEY::C)) {
						Update();
						m_btick = true;
						m_EAnim = PLAYER_ANIM::HAT;
					}
				}
				else {
					Update();
					AdjustCollider(L"Jump", Vec2(60.f, 110.f), Vec2(39.f, 3676.f));
					GetAnimator()->Play(L"Jump", false);
				}
			}
			else if (m_EDir == PLAYER_DIR::RIGHT) {
				if (GetAnimator()->AnimationFinish(L"Jump_R")) {
					AdjustCollider(L"Jump_Tuck_R", Vec2(58.f, 104.f), Vec2(47.f, 3857.f));
					GetAnimator()->Play(L"Jump_Tuck_R", false);
					if (IsTap(KEY::C)) {
						Update();
						m_btick = true;
						m_EAnim = PLAYER_ANIM::HAT;
					}
				}
				else {
					Update();
					AdjustCollider(L"Jump_R", Vec2(60.f, 110.f), Vec2(39.f, 3676.f));
					GetAnimator()->Play(L"Jump_R", false);
				}
			}

			//���� ���߿� ��Ÿ
			if (IsTap(KEY::Z)) {
				Update();
				m_btick = true;
				m_EAnim = PLAYER_ANIM::ATTACK;
			}
			//���� ���߿� Pistol
			if (IsTap(KEY::SPACE)) {
				Update();
				m_btick = true;
				m_EAnim = PLAYER_ANIM::SHOOT;
			}
			//���� ���߿� scimitar
			if (IsTap(KEY::LSHIFT)) {
				Update();
				m_btick = true;
				m_EAnim = PLAYER_ANIM::SCIMITAR;
			}

		}
		break;
		case PLAYER_ANIM::HAT: {
			GetRigidbody()->SetGravityVelocityLimit(100.f);
			if (m_btick) {
				CSound* hatsound = 	CResMgr::GetInst()->LoadSound(L"Hat_Init", L"sound\\player\\cloth.wav");
				hatsound->SetVolume(30.f);
				hatsound->Play();
				m_btick = false;
			}
			//������ ���
			if (!(GetRigidbody()->GetGround())) {
				// ���� Hat��ư�� ������ ������� �ִϸ��̼� ���
				if (IsPressed(KEY::C)) {
					Update();
					if (m_EDir == PLAYER_DIR::LEFT) {

						if (GetAnimator()->AnimationFinish(L"Hat_Init") || GetAnimator()->AnimationFinish(L"Hat_Init_R")) {
							GetAnimator()->Play(L"Hat_Glide", true);
						}
						else {
							GetAnimator()->Play(L"Hat_Init", false);
						}

					}
					else if (m_EDir == PLAYER_DIR::RIGHT) {

						if (GetAnimator()->AnimationFinish(L"Hat_Init_R") || GetAnimator()->AnimationFinish(L"Hat_Init")) {
							GetAnimator()->Play(L"Hat_Glide_R", true);
						}
						else {
							GetAnimator()->Play(L"Hat_Init_R", false);
						}
					}
				}
				// ������ȯ
				if (IsTap(KEY::LEFT) || IsPressed(KEY::LEFT)) {
					Update();
					m_EDir = PLAYER_DIR::LEFT;
					GetRigidbody()->AddVelocity(Vec2(-20.f, 0.f));
				}
				else if (IsTap(KEY::RIGHT) || IsPressed(KEY::RIGHT)) {
					Update();
					m_EDir = PLAYER_DIR::RIGHT;
					GetRigidbody()->AddVelocity(Vec2(20.f, 0.f));
				}
				// ���߿��� ��Ÿ
				if (IsTap(KEY::Z)) {
					Update();
					m_btick = true;
					m_EAnim = PLAYER_ANIM::ATTACK;
				}
				//���߿��� Pistol
				if (IsTap(KEY::SPACE)) {
					Update();
					m_btick = true;
					GetRigidbody()->SetGravityVelocityLimit(1000.f);
					m_EAnim = PLAYER_ANIM::SHOOT;
				}
				//���߿��� scimitar
				if (IsTap(KEY::LSHIFT)) {
					Update();
					m_btick = true;
					m_EAnim = PLAYER_ANIM::SCIMITAR;
				}
				// ���߿��� HatRemove
				if (IsRelease(KEY::C)) {
					Update();
					//m_btick = true;
					GetAnimator()->AnimationReset(L"Hat_Init");
					GetAnimator()->AnimationReset(L"Hat_Init_R");
					if (m_EDir == PLAYER_DIR::LEFT) {
						GetAnimator()->Play(L"Hat_Remove", false);
					}
					else if (m_EDir == PLAYER_DIR::RIGHT) {
						GetAnimator()->Play(L"Hat_Remove_R", false);
					}
				}
				

				if (GetAnimator()->AnimationFinish(L"Hat_Remove") || GetAnimator()->AnimationFinish(L"Hat_Remove_R")) {
					Update();
					m_btick = true;
					GetAnimator()->AnimationReset(L"Hat_Init");
					GetAnimator()->AnimationReset(L"Hat_Init_R");
					GetAnimator()->AnimationReset(L"Hat_Remove");
					GetAnimator()->AnimationReset(L"Hat_Remove_R");
					m_EAnim = PLAYER_ANIM::FALL;
				}
			}
			//���� ���¿��� ���� ����
			else {
				Update();
				m_btick = true;
				GetAnimator()->AnimationReset(L"Hat_Init");
				GetAnimator()->AnimationReset(L"Hat_Init_R");
				GetAnimator()->AnimationReset(L"Hat_Remove");
				GetAnimator()->AnimationReset(L"Hat_Remove_R");
				m_EAnim = PLAYER_ANIM::LAND;
			}
		}
		break;
		case PLAYER_ANIM::FALL:	{

			GetRigidbody()->SetVelocityLimit(200.f);
			GetRigidbody()->SetGravityVelocityLimit(1000.f);
			GetAnimator()->AnimationReset(L"Jump");
			GetAnimator()->AnimationReset(L"Jump_R");
			// ���� ������ Land
			if (GetRigidbody()->GetGround()) {
				Update();
				m_btick = true;
				m_EAnim = PLAYER_ANIM::LAND;
			}
			//���� �����������̴�.
			else {
				if (m_EDir == PLAYER_DIR::LEFT) {
					Update();
					AdjustCollider(L"Fall", Vec2(78.f, 119.f), Vec2(39.f, 4093.f));
					GetAnimator()->Play(L"Fall", true);
				}
				else if (m_EDir == PLAYER_DIR::RIGHT) {
					Update();
					AdjustCollider(L"Fall_R", Vec2(78.f, 119.f), Vec2(39.f, 4093.f));
					GetAnimator()->Play(L"Fall_R", true);
				}
				if (IsPressed(KEY::LEFT)) {
					Update();
					m_EDir = PLAYER_DIR::LEFT;
					GetRigidbody()->AddVelocity(Vec2(-5.f, 0.f));
				}
				else if (IsPressed(KEY::RIGHT)) {
					Update();
					m_EDir = PLAYER_DIR::RIGHT;
					GetRigidbody()->AddVelocity(Vec2(5.f, 0.f));
				}
				// �������� ���� ����
				if (IsTap(KEY::Z)) {
					Update();
					m_EAnim = PLAYER_ANIM::ATTACK;
				}
				// �������� ���� Pistol
				if (IsTap(KEY::SPACE)) {
					Update();
					m_EAnim = PLAYER_ANIM::SHOOT;
				}
				// �������� ���߿� scimitar
				if (IsTap(KEY::LSHIFT)) {
					Update();
					m_EAnim = PLAYER_ANIM::SCIMITAR;
				}
				// �������� ���� Hat���� ��ȯ
				if (IsTap(KEY::C)) {
					Update();
					m_EAnim = PLAYER_ANIM::HAT;
				}
			}


		}
		break;
		case PLAYER_ANIM::LAND: {
			GetRigidbody()->SetVelocityLimit(300.f);
			GetRigidbody()->SetGravityVelocityLimit(1000.f);
			GetAnimator()->AnimationReset(L"Jump_Tuck");
			GetAnimator()->AnimationReset(L"Jump_Tuck_R");
			if (m_btick) {
				CDust* dust1 = new CDust(0);
				
				//Instantiate(dust1, Vec2(GetPos().x - 60, GetPos().y), LAYER::DEATH_LEFTOVER);
				CDust* dust2 = new CDust(1);
				//Instantiate(dust2, Vec2(GetPos().x - 30, GetPos().y), LAYER::DEATH_LEFTOVER);
				CDust* dust3 = new CDust(2);
				//Instantiate(dust3, Vec2(GetPos().x, GetPos().y), LAYER::DEATH_LEFTOVER);
				CDust* dust4 = new CDust(3);
				//Instantiate(dust4, Vec2(GetPos().x + 30, GetPos().y), LAYER::DEATH_LEFTOVER);
				CDust* dust5 = new CDust(4);
				//Instantiate(dust5, Vec2(GetPos().x + 60, GetPos().y), LAYER::DEATH_LEFTOVER);

				Instantiate(dust1, GetPos(), LAYER::DEATH_LEFTOVER);
				Instantiate(dust2, GetPos(), LAYER::DEATH_LEFTOVER);
				Instantiate(dust3, GetPos(), LAYER::DEATH_LEFTOVER);
				Instantiate(dust4, GetPos(), LAYER::DEATH_LEFTOVER);
				Instantiate(dust5, GetPos(), LAYER::DEATH_LEFTOVER);
				m_btick = false;
			}

			if (IsPressed(KEY::LEFT) || IsTap(KEY::LEFT)) {
				Update();
				m_btick = true;
				m_EDir = PLAYER_DIR::LEFT;
				m_EAnim = PLAYER_ANIM::RUN;
			}
			else if (IsPressed(KEY::RIGHT) || IsTap(KEY::RIGHT)) {
				Update();
				m_btick = true;
				m_EDir = PLAYER_DIR::RIGHT;
				m_EAnim = PLAYER_ANIM::RUN;
			}
			if (m_EDir == PLAYER_DIR::LEFT) {
				Update();
				AdjustCollider(L"Land", Vec2(68.f, 105.f), Vec2(63.f, 4305.f));
				GetAnimator()->Play(L"Land", false);
				if (GetAnimator()->AnimationFinish(L"Land")) {
					m_EAnim = PLAYER_ANIM::IDLE;
				}
			}
			else if (m_EDir == PLAYER_DIR::RIGHT) {
				Update();
				AdjustCollider(L"Land_R", Vec2(71.f, 105.f), Vec2(61.f, 4305.f));
				GetAnimator()->Play(L"Land_R", false);
				if (GetAnimator()->AnimationFinish(L"Land_R")) {
					m_EAnim = PLAYER_ANIM::IDLE;
				}
			}
			// ���� ���߿� ��Ÿ
			if (IsTap(KEY::Z)) {
				Update();
				m_btick = true;
				m_EAnim = PLAYER_ANIM::ATTACK;
			}
			// ���� ���߿� ����
			if (IsTap(KEY::X))
			{
				Update();
				m_btick = true;
				m_EAnim = PLAYER_ANIM::JUMP;
				Vec2 V = GetRigidbody()->GetVelocity();

				if (0.f < V.y)
				{
					GetRigidbody()->AddVelocity(Vec2(0.f, -(V.y + 600.f)));
				}
				else
				{
					GetRigidbody()->AddVelocity(Vec2(0.f, -600.f));
				}
			}
			//���� ���߿� ���
			else if (IsTap(KEY::SPACE)) {
				Update();
				GetRigidbody()->SetVelocity(Vec2(0.f, 0.f));
				m_btick = true;
				m_EAnim = PLAYER_ANIM::SHOOT;
			}
			//���� ���߿� ���ñ�
			else if (IsTap(KEY::_2)) {
				Update();
				if (m_iMonsterMilkCount > 0 && !m_bMonsterMilk) {
					m_iMonsterMilkCount--;
					UpdateItem();
					m_btick = true;
					m_EAnim = PLAYER_ANIM::DRINK;
					GetRigidbody()->SetVelocity(Vec2(0.f, 0.f));
				}
			}
		}
		break;
		case PLAYER_ANIM::ATTACK: {
			//���󿡼� ����
			if (m_EPrevAnim == PLAYER_ANIM::IDLE || m_EPrevAnim == PLAYER_ANIM::RUN || m_EPrevAnim == PLAYER_ANIM::LAND) {
				if (GetAnimator()->AnimationFinish(L"Standing_Whip")) {
					GetAnimator()->AnimationReset(L"Standing_Whip");
					m_btick = true;
					m_bAttack = true;
					m_EAnim = PLAYER_ANIM::IDLE;
				}
				else {
					if (m_EDir == PLAYER_DIR::LEFT) {
						AdjustCollider(L"Standing_Whip", Vec2(64.f, 84.f), Vec2(160.f, 5538.f));
						GetAnimator()->Play(L"Standing_Whip", false);
						//���ο� Collider�� �ν��ؾ��ϹǷ� 1tick ����
						if (m_btick) {
							GetRigidbody()->SetVelocity(Vec2(0.f, 0.f));
							m_btick = false;
						}
						else {
							if (m_bAttack) {
								if (m_fAttvoiceCooldown > 2.0f) {
									srand((UINT)CTimeMgr::GetInst()->ReturnCurCount());
									if (rand() % 2 == 0) {
										CSound* attacksound = CResMgr::GetInst()->LoadSound(L"Attack_01", L"sound\\player\\vo_s_attack_01 [1].wav");
										attacksound->SetVolume(25);
										attacksound->Play();
									}
									else if (rand() % 2 == 1) {
										CSound* attacksound = CResMgr::GetInst()->LoadSound(L"Attack_02", L"sound\\player\\vo_s_attack_02 [1].wav");
										attacksound->SetVolume(25);
										attacksound->Play();
									}
									else {
										CSound* attacksound = CResMgr::GetInst()->LoadSound(L"Attack_02", L"sound\\player\\vo_s_attack_02 [1].wav");
										attacksound->SetVolume(25);
										attacksound->Play();
									}
									m_fAttvoiceCooldown = 0.f;
								}
								CWhip* cWhip = new CWhip(this);
								Instantiate(cWhip, GetCollider()->GetFinalPos(), LAYER::PLAYER_PROJECTILE);
								m_bAttack = false;
							}
							m_btick = true;
						}

					}
				}

				if (GetAnimator()->AnimationFinish(L"Standing_Whip_R")) {
					GetAnimator()->AnimationReset(L"Standing_Whip_R");
					m_btick = true;
					m_bAttack = true;
					m_EAnim = PLAYER_ANIM::IDLE;
				}
				else {
					if (m_EDir == PLAYER_DIR::RIGHT) {
						AdjustCollider(L"Standing_Whip_R", Vec2(64.f, 84.f), Vec2(128.f, 5538.f));
						GetAnimator()->Play(L"Standing_Whip_R", false);
						if (m_btick) {
							GetRigidbody()->SetVelocity(Vec2(0.f, 0.f));
							m_btick = false;
						}
						else {
							if (m_bAttack) {
								if (m_fAttvoiceCooldown > 2.0f) {
									srand((UINT)CTimeMgr::GetInst()->ReturnCurCount());
									if (rand() % 2 == 0) {
										CSound* attacksound = CResMgr::GetInst()->LoadSound(L"Attack_01", L"sound\\player\\vo_s_attack_01 [1].wav");
										attacksound->SetVolume(25);
										attacksound->Play();
									}
									else if (rand() % 2 == 1) {
										CSound* attacksound = CResMgr::GetInst()->LoadSound(L"Attack_02", L"sound\\player\\vo_s_attack_02 [1].wav");
										attacksound->SetVolume(25);
										attacksound->Play();
									}
									else {
										CSound* attacksound = CResMgr::GetInst()->LoadSound(L"Attack_02", L"sound\\player\\vo_s_attack_02 [1].wav");
										attacksound->SetVolume(25);
										attacksound->Play();
									}
									m_fAttvoiceCooldown = 0.f;
								}
								CWhip* cWhip = new CWhip(this);
								Instantiate(cWhip, GetCollider()->GetFinalPos(), LAYER::PLAYER_PROJECTILE);
								m_bAttack = false;
							}
							m_btick = true;
						}
					}
				}
			}
			//���߿��� ����
			if (m_EPrevAnim == PLAYER_ANIM::JUMP || m_EPrevAnim == PLAYER_ANIM::FALL || m_EPrevAnim == PLAYER_ANIM::HAT) {
				// ���� ���߿� ����
				if (!(GetRigidbody()->GetGround())) {

					if (GetAnimator()->AnimationFinish(L"Jump_Whip")) {
						GetAnimator()->AnimationReset(L"Jump_Whip");
						m_btick = true;
						m_bAttack = true;
						m_EAnim = PLAYER_ANIM::FALL;
					}
					else {
						if (m_EDir == PLAYER_DIR::LEFT) {
							AdjustCollider(L"Jump_Whip", Vec2(64.f, 84.f), Vec2(144.f, 5886.f));
							GetAnimator()->Play(L"Jump_Whip", false);
							//���ο� Collider�� �ν��ؾ��ϹǷ� 1tick ����
							if (m_btick) {
								m_btick = false;
							}
							else {
								if (m_bAttack) {
									if (m_fAttvoiceCooldown > 2.0f) {
										srand((UINT)CTimeMgr::GetInst()->ReturnCurCount());
										if (rand() % 2 == 0) {
											CSound* attacksound = CResMgr::GetInst()->LoadSound(L"Attack_01", L"sound\\player\\vo_s_attack_01 [1].wav");
											attacksound->SetVolume(25);
											attacksound->Play();
										}
										else if (rand() % 2 == 1) {
											CSound* attacksound = CResMgr::GetInst()->LoadSound(L"Attack_02", L"sound\\player\\vo_s_attack_02 [1].wav");
											attacksound->SetVolume(25);
											attacksound->Play();
										}
										else {
											CSound* attacksound = CResMgr::GetInst()->LoadSound(L"Attack_02", L"sound\\player\\vo_s_attack_02 [1].wav");
											attacksound->SetVolume(25);
											attacksound->Play();
										}
										m_fAttvoiceCooldown = 0.f;
									}
									CWhip* cWhip = new CWhip(this);
									Instantiate(cWhip, GetCollider()->GetFinalPos(), LAYER::PLAYER_PROJECTILE);
									m_bAttack = false;
								}
								m_btick = true;
							}

						}
					}


					if (GetAnimator()->AnimationFinish(L"Jump_Whip_R")) {
						GetAnimator()->AnimationReset(L"Jump_Whip_R");
						m_btick = true;
						m_bAttack = true;
						m_EAnim = PLAYER_ANIM::FALL;
					}
					else {
						if (m_EDir == PLAYER_DIR::RIGHT) {
							AdjustCollider(L"Jump_Whip_R", Vec2(64.f, 84.f), Vec2(144.f, 5886.f));
							GetAnimator()->Play(L"Jump_Whip_R", false);
							if (m_btick) {
								m_btick = false;
							}
							else {
								if (m_bAttack) {
									if (m_fAttvoiceCooldown > 2.0f) {
										srand((UINT)CTimeMgr::GetInst()->ReturnCurCount());
										if (rand() % 2 == 0) {
											CSound* attacksound = CResMgr::GetInst()->LoadSound(L"Attack_01", L"sound\\player\\vo_s_attack_01 [1].wav");
											attacksound->SetVolume(25);
											attacksound->Play();
										}
										else if (rand() % 2 == 1) {
											CSound* attacksound = CResMgr::GetInst()->LoadSound(L"Attack_02", L"sound\\player\\vo_s_attack_02 [1].wav");
											attacksound->SetVolume(25);
											attacksound->Play();
										}
										else {
											CSound* attacksound = CResMgr::GetInst()->LoadSound(L"Attack_02", L"sound\\player\\vo_s_attack_02 [1].wav");
											attacksound->SetVolume(25);
											attacksound->Play();
										}
										m_fAttvoiceCooldown = 0.f;
									}
									CWhip* cWhip = new CWhip(this);
									Instantiate(cWhip, GetCollider()->GetFinalPos(), LAYER::PLAYER_PROJECTILE);
									m_bAttack = false;
								}
								m_btick = true;
							}
						}
					}
				}
				// �����ϴٰ� ������ ������
				else {
					m_bAttack = true;
					GetAnimator()->AnimationReset(L"Jump_Whip");
					GetAnimator()->AnimationReset(L"Jump_Whip_R");
					m_EAnim = PLAYER_ANIM::LAND;
				}

			}
			//�ɾ��ִµ� ����
			if (m_EPrevAnim == PLAYER_ANIM::DUCK) {
				// �������� ����
				if (GetAnimator()->AnimationFinish(L"Duck_Whip")) {
					GetAnimator()->AnimationReset(L"Duck_Whip");
					m_btick = true;
					m_bAttack = true;
					m_EAnim = PLAYER_ANIM::DUCK;
				}
				else {
					if (m_EDir == PLAYER_DIR::LEFT) {
						AdjustCollider(L"Duck_Whip", Vec2(57.f, 57.f), Vec2(138.f, 5082.f));
						GetAnimator()->Play(L"Duck_Whip", false);
						//���ο� Collider�� �ν��ؾ��ϹǷ� 1tick ����
						if (m_btick) {
							//�����Ҷ��� �̵� ����
							GetRigidbody()->SetVelocity(Vec2(0.f, 0.f));
							m_btick = false;
						}
						else {
							if (m_bAttack) {
								if (m_fAttvoiceCooldown > 2.0f) {
									srand((UINT)CTimeMgr::GetInst()->ReturnCurCount());
									if (rand() % 2 == 0) {
										CSound* attacksound = CResMgr::GetInst()->LoadSound(L"Attack_01", L"sound\\player\\vo_s_attack_01 [1].wav");
										attacksound->SetVolume(25);
										attacksound->Play();
									}
									else if (rand() % 2 == 1) {
										CSound* attacksound = CResMgr::GetInst()->LoadSound(L"Attack_02", L"sound\\player\\vo_s_attack_02 [1].wav");
										attacksound->SetVolume(25);
										attacksound->Play();
									}
									else {
										CSound* attacksound = CResMgr::GetInst()->LoadSound(L"Attack_02", L"sound\\player\\vo_s_attack_02 [1].wav");
										attacksound->SetVolume(25);
										attacksound->Play();
									}
									m_fAttvoiceCooldown = 0.f;
								}
								CWhip* cWhip = new CWhip(this);
								Instantiate(cWhip, GetCollider()->GetFinalPos(), LAYER::PLAYER_PROJECTILE);
								m_bAttack = false;
							}
							m_btick = true;
						}

					}
				}
				// ���������� ����
				if (GetAnimator()->AnimationFinish(L"Duck_Whip_R")) {
					GetAnimator()->AnimationReset(L"Duck_Whip_R");
					m_btick = true;
					m_bAttack = true;
					m_EAnim = PLAYER_ANIM::DUCK;
				}
				else {
					if (m_EDir == PLAYER_DIR::RIGHT) {
						AdjustCollider(L"Duck_Whip_R", Vec2(57.f, 57.f), Vec2(138.f, 5082.f));
						GetAnimator()->Play(L"Duck_Whip_R", false);
						if (m_btick) {
							GetRigidbody()->SetVelocity(Vec2(0.f, 0.f));
							m_btick = false;
						}
						else {
							if (m_bAttack) {
								if (m_fAttvoiceCooldown > 2.0f) {
									srand((UINT)CTimeMgr::GetInst()->ReturnCurCount());
									if (rand() % 2 == 0) {
										CSound* attacksound = CResMgr::GetInst()->LoadSound(L"Attack_01", L"sound\\player\\vo_s_attack_01 [1].wav");
										attacksound->SetVolume(25);
										attacksound->Play();
									}
									else if (rand() % 2 == 1) {
										CSound* attacksound = CResMgr::GetInst()->LoadSound(L"Attack_02", L"sound\\player\\vo_s_attack_02 [1].wav");
										attacksound->SetVolume(25);
										attacksound->Play();
									}
									else {
										CSound* attacksound = CResMgr::GetInst()->LoadSound(L"Attack_02", L"sound\\player\\vo_s_attack_02 [1].wav");
										attacksound->SetVolume(25);
										attacksound->Play();
									}
									m_fAttvoiceCooldown = 0.f;
								}
								CWhip* cWhip = new CWhip(this);
								Instantiate(cWhip, GetCollider()->GetFinalPos(), LAYER::PLAYER_PROJECTILE);
								m_bAttack = false;
							}
							m_btick = true;
						}
					}
				}
			}
		}
		break;
		case PLAYER_ANIM::SHOOT: {

			//���󿡼� ����
			if (m_EPrevAnim == PLAYER_ANIM::IDLE || m_EPrevAnim == PLAYER_ANIM::RUN || m_EPrevAnim == PLAYER_ANIM::LAND) {
				// �������� ��� ������ ������.
				if (GetAnimator()->AnimationFinish(L"Pistol_Blast")) {
					GetAnimator()->AnimationReset(L"Pistol_Pullout");
					GetAnimator()->AnimationReset(L"Pistol_Pullout_R");
					GetAnimator()->AnimationReset(L"Pistol_Blast");
					GetAnimator()->AnimationReset(L"Pistol_Blast_R");
					//�� ����ְ� ����
					m_btick = true;
					m_bAttack = true;
					m_EAnim = PLAYER_ANIM::IDLE;
				}
				//������ �ؾ��Ѵ�.
				else {
					if (m_EDir == PLAYER_DIR::LEFT) {
						//�Ѳ����� �ִϸ��̼��� ������ ���� ��� �ִϸ��̼� ���
						if (GetAnimator()->AnimationFinish(L"Pistol_Pullout")) {
							AdjustCollider(L"Pistol_Blast", Vec2(75.f, 100.f), Vec2(78.f, 12713.f));
							GetAnimator()->Play(L"Pistol_Blast", false);
							//���ο� Collider�ν��� ���� 1tick����
							if (m_btick) {
								m_btick = false;
							}
							else {
								// �ѽ�°� �ѹ���
								if (m_bAttack) {
									if (m_fAttvoiceCooldown > 2.0f) {
										srand((UINT)CTimeMgr::GetInst()->ReturnCurCount());
										if (rand() % 2 == 0) {
											CSound* shootSound = CResMgr::GetInst()->LoadSound(L"Attack_eat_this_1", L"sound\\player\\vo_s_attack_eat_this_01 [1].wav");
											shootSound->SetVolume(25);
											shootSound->Play();
										}
										else if (rand() % 2 == 1) {
											CSound* shootSound = CResMgr::GetInst()->LoadSound(L"Attack_eat_this_2", L"sound\\player\\vo_s_attack_eat_this_02 [1].wav");
											shootSound->SetVolume(25);
											shootSound->Play();
										}
										else {
											CSound* shootSound = CResMgr::GetInst()->LoadSound(L"Attack_eat_this_1", L"sound\\player\\vo_s_attack_eat_this_02 [1].wav");
											shootSound->SetVolume(25);
											shootSound->Play();
										}
										m_fAttvoiceCooldown = 0.f;
									}
									CPistol* pPistol = new CPistol(this);
									pPistol->SetScale(Vec2(20.f, 20.f));
									pPistol->SetSpeed(400.f);
									pPistol->SetDir(180.f);
									Vec2 vPos = Vec2(GetPos().x - GetCollider()->GetScale().x / 2.f - 20.f, GetPos().y - GetCollider()->GetScale().y / 2.f - 20.f);
									Instantiate(pPistol, vPos, LAYER::PLAYER_PROJECTILE);
									m_bAttack = false;
								}
								m_btick = true;
							}

						}
						else {
							//���� �������Ѵ�.
							AdjustCollider(L"Pistol_Pullout", Vec2(75.f, 100.f), Vec2(84.f, 12524.f));
							GetAnimator()->Play(L"Pistol_Pullout", false);
						}

					}
				}
				// ���������� ��� ������ ������.
				if (GetAnimator()->AnimationFinish(L"Pistol_Blast_R")) {
					GetAnimator()->AnimationReset(L"Pistol_Pullout");
					GetAnimator()->AnimationReset(L"Pistol_Pullout_R");
					GetAnimator()->AnimationReset(L"Pistol_Blast");
					GetAnimator()->AnimationReset(L"Pistol_Blast_R");
					//�� ����ְ� ����
					m_btick = true;
					m_bAttack = true;
					m_EAnim = PLAYER_ANIM::IDLE;
				}
				//������ �ؾ��Ѵ�.
				else {
					if (m_EDir == PLAYER_DIR::RIGHT) {
						//�Ѳ����� �ִϸ��̼��� ������ ���� ��� �ִϸ��̼� ���
						if (GetAnimator()->AnimationFinish(L"Pistol_Pullout_R")) {
							AdjustCollider(L"Pistol_Blast_R", Vec2(75.f, 100.f), Vec2(78.f, 12713.f));
							GetAnimator()->Play(L"Pistol_Blast_R", false);
							//���ο� Collider�ν��� ���� 1tick����
							if (m_btick) {
								m_btick = false;
							}
							else {
								// �ѽ�°� �ѹ���
								if (m_bAttack) {
									if (m_fAttvoiceCooldown > 2.0f) {
										srand((UINT)CTimeMgr::GetInst()->ReturnCurCount());
										if (rand() % 2 == 0) {
											CSound* shootSound = CResMgr::GetInst()->LoadSound(L"Attack_eat_this_1", L"sound\\player\\vo_s_attack_eat_this_01 [1].wav");
											shootSound->SetVolume(25);
											shootSound->Play();
										}
										else if (rand() % 2 == 1) {
											CSound* shootSound = CResMgr::GetInst()->LoadSound(L"Attack_eat_this_2", L"sound\\player\\vo_s_attack_eat_this_02 [1].wav");
											shootSound->SetVolume(25);
											shootSound->Play();
										}
										else {
											CSound* shootSound = CResMgr::GetInst()->LoadSound(L"Attack_eat_this_1", L"sound\\player\\vo_s_attack_eat_this_02 [1].wav");
											shootSound->SetVolume(25);
											shootSound->Play();
										}
										m_fAttvoiceCooldown = 0.f;
									}
									CPistol* pPistol = new CPistol(this);
									pPistol->SetScale(Vec2(20.f, 20.f));
									pPistol->SetSpeed(400.f);
									pPistol->SetDir(0.f);
									Vec2 vPos = Vec2(GetPos().x - GetCollider()->GetScale().x / 2.f + 20.f, GetPos().y - GetCollider()->GetScale().y / 2.f - 20.f);
									Instantiate(pPistol, vPos, LAYER::PLAYER_PROJECTILE);
									m_bAttack = false;
								}
								m_btick = true;
							}

						}
						else {
							//���� �������Ѵ�.
							AdjustCollider(L"Pistol_Pullout_R", Vec2(75.f, 100.f), Vec2(84.f, 12524.f));
							GetAnimator()->Play(L"Pistol_Pullout_R", false);
						}

					}
				}
			}
			//���߿��� ����
			if (m_EPrevAnim == PLAYER_ANIM::JUMP || m_EPrevAnim == PLAYER_ANIM::FALL || m_EPrevAnim == PLAYER_ANIM::HAT) {

				// ���� ���߿� ����
				if (!(GetRigidbody()->GetGround())) {

					// �������� ��� ������ ������.
					if (GetAnimator()->AnimationFinish(L"Pistol_Blast_Jump")) {
						GetAnimator()->AnimationReset(L"Pistol_Blast_Jump");
						GetAnimator()->AnimationReset(L"Pistol_Blast_Jump_R");
						//�� ����ְ� ����
						m_btick = true;
						m_bAttack = true;
						m_EAnim = PLAYER_ANIM::FALL;
					}
					//������ �ؾ��Ѵ�.
					else {
						if (m_EDir == PLAYER_DIR::LEFT) {
							AdjustCollider(L"Pistol_Blast_Jump", Vec2(54, 111.f), Vec2(94.f, 12896.f));
							GetAnimator()->Play(L"Pistol_Blast_Jump", false);
							//���ο� Collider�ν��� ���� 1tick����
							if (m_btick) {
								m_btick = false;
							}
							else {
								// �ѽ�°� �ѹ���
								if (m_bAttack) {
									CPistol* pPistol = new CPistol(this);
									pPistol->SetScale(Vec2(20.f, 20.f));
									pPistol->SetSpeed(400.f);
									pPistol->SetDir(180.f);
									Vec2 vPos = Vec2(GetPos().x - GetCollider()->GetScale().x / 2.f, GetPos().y - GetCollider()->GetScale().y / 2.f - 20.f);
									Instantiate(pPistol, vPos, LAYER::PLAYER_PROJECTILE);
									m_bAttack = false;
								}
								m_btick = true;
							}
						}
					}
					// ���������� ��� ������ ������.
					if (GetAnimator()->AnimationFinish(L"Pistol_Blast_Jump_R")) {
						GetAnimator()->AnimationReset(L"Pistol_Blast_Jump");
						GetAnimator()->AnimationReset(L"Pistol_Blast_Jump_R");
						//�� ����ְ� ����
						m_btick = true;
						m_bAttack = true;
						m_EAnim = PLAYER_ANIM::FALL;
					}
					//������ �ؾ��Ѵ�.
					else {
						if (m_EDir == PLAYER_DIR::RIGHT) {
							AdjustCollider(L"Pistol_Blast_Jump_R", Vec2(54, 111.f), Vec2(94.f, 12896.f));
							GetAnimator()->Play(L"Pistol_Blast_Jump_R", false);
							//���ο� Collider�ν��� ���� 1tick����
							if (m_btick) {
								m_btick = false;
							}
							else {
								// �ѽ�°� �ѹ���
								if (m_bAttack) {
									CPistol* pPistol = new CPistol(this);
									pPistol->SetScale(Vec2(20.f, 20.f));
									pPistol->SetSpeed(400.f);
									pPistol->SetDir(0.f);
									Vec2 vPos = Vec2(GetPos().x - GetCollider()->GetScale().x / 2.f, GetPos().y - GetCollider()->GetScale().y / 2.f - 20.f);
									Instantiate(pPistol, vPos, LAYER::PLAYER_PROJECTILE);
									m_bAttack = false;
								}
								m_btick = true;
							}
						}
					}
				}
				// �����ϴٰ� ������ ������
				else {
					m_bAttack = true;
					GetAnimator()->AnimationReset(L"Pistol_Blast_Jump");
					GetAnimator()->AnimationReset(L"Pistol_Blast_Jump_R");
					m_EAnim = PLAYER_ANIM::LAND;
				}

			}
		}
		break;
		case PLAYER_ANIM::SCIMITAR: {
			// 1ƽ���� �ʱ⼳��
			if (m_btick) {
				GetRigidbody()->SetGravityVelocityLimit(1000.f);
				Vec2 CurVel = GetRigidbody()->GetVelocity();
				// ���� �����̸� �ٷ� �������
				if (CurVel.y < 0) {
					GetRigidbody()->SetVelocity(Vec2(0.f, 0.f));
				}
				else {
					GetRigidbody()->SetVelocity(Vec2(0.f, CurVel.y));
				}
				
				CScimitar* cScimitar = new CScimitar(this);
				Instantiate(cScimitar, GetPos(), LAYER::PLAYER_PROJECTILE);
				m_btick = false;
			}
			else {
				//���� �ƴ� ��� ����
				if (!(GetRigidbody()->GetGround())) {
					Update();
					// LSHIFT�� ��� ������ ��� ��������
					if (IsPressed(KEY::LSHIFT)) {
						if (m_EDir == PLAYER_DIR::LEFT) {
							AdjustCollider(L"Down_Thrust", Vec2(57.f, 102.f), Vec2(48.f, 10305.f));
							GetAnimator()->Play(L"Down_Thrust", true);
						}
						else if (m_EDir == PLAYER_DIR::RIGHT) {
							AdjustCollider(L"Down_Thrust_R", Vec2(57.f, 102.f), Vec2(51.f, 10305.f));
							GetAnimator()->Play(L"Down_Thrust_R", true);
							
						}
					}
					// ���߿� �ִµ� LShiftŰ�� ����.
					else if (IsRelease(KEY::LSHIFT) || IsNone(KEY::LSHIFT)) {
						m_btick = true;
						m_EAnim = PLAYER_ANIM::FALL;
					}
				}
				//���� ������
				else {
					Update();
					m_btick = true;
					m_EAnim = PLAYER_ANIM::LAND;
				}
			}


		
		}
		break;
		case PLAYER_ANIM::EAT:
		{
			if (GetAnimator()->AnimationFinish(L"Eat") || GetAnimator()->AnimationFinish(L"Eat_R")) {
				m_iHP += 3;
				
				CObj* pHeal = new CHealEffect(3);
				CSound* healcomplete = CResMgr::GetInst()->LoadSound(L"Meat_Heal", L"sound\\fx\\pickup_heart_large.wav");
				healcomplete->Play();
				Vec2 vPos = Vec2(GetPos().x, GetPos().y - GetCollider()->GetScale().y);
				Instantiate(pHeal, vPos, LAYER::DAMAGE);
				if (m_iHP > m_iMaxHp) m_iHP = m_iMaxHp;
				UpdateHeartContainer();
				GetAnimator()->AnimationReset(L"Eat");
				GetAnimator()->AnimationReset(L"Eat_R");
				m_btick = true;
				m_EAnim = PLAYER_ANIM::IDLE;
			}
			else {
				if (m_btick) {
					CSound* pSound = CResMgr::GetInst()->LoadSound(L"eat", L"sound\\player\\vo_s_eat_05 [1].wav");
					pSound->Play();
					m_btick = false;
				}
				if (m_EDir == PLAYER_DIR::LEFT) {
					Update();
					AdjustCollider(L"Eat", Vec2(56.f, 108.f), Vec2(73.f, 7011.f));
					GetAnimator()->Play(L"Eat", false);
				}
				else if (m_EDir == PLAYER_DIR::RIGHT) {
					Update();
					AdjustCollider(L"Eat_R", Vec2(56.f, 108.f), Vec2(73.f, 7011.f));
					GetAnimator()->Play(L"Eat_R", false);

				}
			}
		}
		break;
		case PLAYER_ANIM::DRINK: {
			
			if (GetAnimator()->AnimationFinish(L"Drink") || GetAnimator()->AnimationFinish(L"Drink_R")) {
				m_bMonsterMilk = true;
				GetAnimator()->AnimationReset(L"Drink");
				GetAnimator()->AnimationReset(L"Drink_R");
				m_EAnim = PLAYER_ANIM::IDLE;
				m_btick = true;
			}
			else {
				// Drink Enter
				if (m_btick) {
					CSound* pSound = CResMgr::GetInst()->LoadSound(L"vo_a_monster_milk_01", L"sound\\player\\vo_a_monster_milk_01 [1].wav");
					pSound->SetVolume(25);
					pSound->Play();
					m_btick = false;
				}
				else {
					if (m_EDir == PLAYER_DIR::LEFT) {
						Update();
						AdjustCollider(L"Drink", Vec2(68.f, 122.f), Vec2(62.f, 7342.f));
						GetAnimator()->Play(L"Drink", false);
					}
					else if (m_EDir == PLAYER_DIR::RIGHT) {
						Update();
						AdjustCollider(L"Drink_R", Vec2(68.f, 122.f), Vec2(62.f, 7342.f));
						GetAnimator()->Play(L"Drink_R", false);

					}
				}
				
				
			}
			
		}
		 break;
		case PLAYER_ANIM::ENTER: {
			if (GetAnimator()->AnimationFinish(L"Enter") || GetAnimator()->AnimationFinish(L"Enter_R")) {
				GetAnimator()->AnimationReset(L"Enter");
				GetAnimator()->AnimationReset(L"Enter_R");
				m_EAnim = PLAYER_ANIM::IDLE;
				m_btick = true;
			}
			else {
				if (m_EDir == PLAYER_DIR::LEFT) {
					Update();
					GetAnimator()->Play(L"Enter", false);
				}
				else if (m_EDir == PLAYER_DIR::RIGHT) {
					Update();
					GetAnimator()->Play(L"Enter_R", false);
				}
			}
		}
		break;
		case PLAYER_ANIM::EXIT: {
			if (GetAnimator()->AnimationFinish(L"Exit") || GetAnimator()->AnimationFinish(L"Exit_R")) {
				GetAnimator()->AnimationReset(L"Exit");
				GetAnimator()->AnimationReset(L"Exit_R");
				m_EAnim = PLAYER_ANIM::IDLE;
				m_btick = true;
			}
			else {
				if (m_EDir == PLAYER_DIR::LEFT) {
					Update();
					AdjustCollider(L"Exit", Vec2(71.f, 123.f), Vec2(40.f, 6660.f));
					GetAnimator()->Play(L"Exit", false);
				}
				else if (m_EDir == PLAYER_DIR::RIGHT) {
					Update();
					AdjustCollider(L"Exit_R", Vec2(71.f, 123.f), Vec2(40.f, 6660.f));
					GetAnimator()->Play(L"Exit_R", false);
				}
			}
		}
		break;
		case PLAYER_ANIM::TWIRL: {
			if (m_btick) {
				m_fTime = 0.f;
				GetRigidbody()->SetGravity(false);
				GetRigidbody()->SetVelocityLimit(1000.f);
				//GetRigidbody()->SetVelocity(Vec2(0.f, -300.f));
				//AdjustCollider(L"Twirl_Loop", Vec2(71.f, 123.f), Vec2(40.f, 6660.f));
				GetAnimator()->Play(L"Twirl_Loop", true);
				CSound* clear = CResMgr::GetInst()->LoadSound(L"Stage_Clear", L"sound\\fx\\Clear.wav");
				clear->Play();
				m_btick = false;
			}
			m_fTime += DT;
		
			if (m_fTime > 1.0f) {
				GetRigidbody()->SetVelocity(Vec2(0.f, 0.f));
			}
			else {
				GetRigidbody()->AddVelocity(Vec2(0.f, -10.f));
			}
			if (m_fTime > 7.0f) {
				CCamera::GetInst()->FadeOut(1.0f);
				m_fTime = 0.f;
				m_btick = true;
				GetRigidbody()->SetGravity(true);
				m_EAnim = PLAYER_ANIM::IDLE;
				ChangeLevel(LEVEL_TYPE::START);
			}
		}
		break;
		case PLAYER_ANIM::NONE: {
			m_EAnim = PLAYER_ANIM::IDLE;
			m_EDir = PLAYER_DIR::LEFT;
		}
		break;
		default:
		break;
		}
	}
	break;
	case PLAYER_STATE::HIT: {
		//���ݵ��� ������ ���� �ٽ� �����Ҽ��ְ� ����
		
		GetRigidbody()->SetVelocityLimit(300.f);
		GetRigidbody()->SetGravityVelocityLimit(1000.f);
		m_bAttack = true;

		//���߿��� ���� ���
		if (m_EAnim == PLAYER_ANIM::JUMP ||
			m_EAnim == PLAYER_ANIM::FALL ||
			m_EAnim == PLAYER_ANIM::HAT ||
			m_EAnim == PLAYER_ANIM::SCIMITAR||
			//�����϶� ������ ���� �ִϸ��̼ǵ� ���� �������
			(m_EAnim == PLAYER_ANIM::ATTACK &&
				(m_EPrevAnim == PLAYER_ANIM::JUMP ||
					m_EPrevAnim == PLAYER_ANIM::FALL ||
					m_EPrevAnim == PLAYER_ANIM::HAT)) ||
			//pistol�߿� �´°͵� ����
			(m_EAnim == PLAYER_ANIM::SHOOT &&
				(m_EPrevAnim == PLAYER_ANIM::JUMP ||
					m_EPrevAnim == PLAYER_ANIM::FALL ||
					m_EPrevAnim == PLAYER_ANIM::HAT))
			) {
			//�ִϸ��̼� ����
			GetAnimator()->AnimationReset(L"Jump_Whip");
			GetAnimator()->AnimationReset(L"Jump_Whip_R");
			GetAnimator()->AnimationReset(L"Pistol_Blast_Jump");
			GetAnimator()->AnimationReset(L"Pistol_Blast_Jump_R");
			GetAnimator()->AnimationReset(L"Jump");
			GetAnimator()->AnimationReset(L"Jump_R");
			if (PLAYER_DIR::LEFT == m_EDir) {
				if (!(GetAnimator()->AnimationFinish(L"KnockDown_1"))) {
					GetAnimator()->Play(L"KnockDown_1", false);
				}
				// ���߿��� �ѹ��� Ƣ�������.
				if (m_bHitAir) {
					CSound* hit = CResMgr::GetInst()->LoadSound(L"Hit_Air", L"sound\\player\\vo_s_hurt_05 [1].wav");
					hit->Play();
					Vec2 V = GetRigidbody()->GetVelocity();
					if (0.f < V.y)
					{
						GetRigidbody()->AddVelocity(Vec2(-(V.x - 200.f), -(V.y + 300.f)));
					}
					else
					{
						GetRigidbody()->SetVelocity(Vec2(200.f, -300.f));
					}
					m_bHitAir = false;
				}

			}
			else if (PLAYER_DIR::RIGHT == m_EDir) {
				if (!(GetAnimator()->AnimationFinish(L"KnockDown_R_1"))) {
					GetAnimator()->Play(L"KnockDown_R_1", false);
				}
				//���߿��� �ѹ��� Ƣ�������.
				if (m_bHitAir) {
					CSound* hit = CResMgr::GetInst()->LoadSound(L"Hit_Air", L"sound\\player\\vo_s_hurt_05 [1].wav");
					hit->Play();
					Vec2 V = GetRigidbody()->GetVelocity();
					if (0.f < V.y)
					{
						GetRigidbody()->AddVelocity(Vec2(-(V.x + 200.f), -(V.y + 300.f)));
					}
					else
					{
						GetRigidbody()->SetVelocity(Vec2(-200.f, -300.f));
					}
					m_bHitAir = false;
				}

			}
			if (GetRigidbody()->GetGround()) {
				//���� �������� �з����� �ʴ´�.

				if (m_btick) {
					CSound* getup = CResMgr::GetInst()->LoadSound(L"Getup", L"sound\\player\\vo_s_land_05 [1].wav");
					getup->Play();
					m_btick = false;
				}
				else {
					if (GetPos() != GetPrevPos()) {
						SetPos(Vec2(GetPrevPos().x, GetPrevPos().y));
					}
				}

				if (GetAnimator()->AnimationFinish(L"KnockDown_1")) {
					
					AdjustCollider(L"KnockDown_2", Vec2(150.f, 70.f), Vec2(1332.f, 14792.f));
					GetAnimator()->Play(L"KnockDown_2", false);
				}
				else if (GetAnimator()->AnimationFinish(L"KnockDown_R_1")) {
					
					AdjustCollider(L"KnockDown_R_2", Vec2(150.f, 70.f), Vec2(1332.f, 14792.f));
					GetAnimator()->Play(L"KnockDown_R_2", false);
				}
				//state ��ȯ & �ִϸ��̼� ���� & �������� ����
				if (GetAnimator()->AnimationFinish(L"KnockDown_2") || GetAnimator()->AnimationFinish(L"KnockDown_R_2")) {
					GetAnimator()->AnimationReset(L"KnockDown_1");
					GetAnimator()->AnimationReset(L"KnockDown_R_1");
					GetAnimator()->AnimationReset(L"KnockDown_2");
					GetAnimator()->AnimationReset(L"KnockDown_R_2");
					m_btick = true;
					m_bInvincible = true;
					m_bHitAir = true;
					m_fInvincibleTime = 0.f;
					m_EState = PLAYER_STATE::NORMAL;
					m_EAnim = PLAYER_ANIM::IDLE;
				}
			}
		}

				//���󿡼� ���� ���
		else if (m_EAnim == PLAYER_ANIM::IDLE ||
				m_EAnim == PLAYER_ANIM::RUN ||
				m_EAnim == PLAYER_ANIM::LAND ||
				m_EAnim == PLAYER_ANIM::EAT||
				m_EAnim == PLAYER_ANIM::DRINK||
				//���� ���� �ǰ�
				(m_EAnim == PLAYER_ANIM::ATTACK &&
				(m_EPrevAnim == PLAYER_ANIM::IDLE ||
				m_EPrevAnim == PLAYER_ANIM::RUN ||
				m_EPrevAnim == PLAYER_ANIM::LAND)) ||
				// Pistol ���� �ǰ�

				(m_EAnim == PLAYER_ANIM::SHOOT &&
				(m_EPrevAnim == PLAYER_ANIM::IDLE ||
				m_EPrevAnim == PLAYER_ANIM::RUN ||
				m_EPrevAnim == PLAYER_ANIM::LAND))
				) {
					//�ִϸ��̼� ����
					GetAnimator()->AnimationReset(L"Standing_Whip");
					GetAnimator()->AnimationReset(L"Standing_Whip_R");
					GetAnimator()->AnimationReset(L"Pistol_Pullout");
					GetAnimator()->AnimationReset(L"Pistol_Pullout_R");
					GetAnimator()->AnimationReset(L"Pistol_Blast");
					GetAnimator()->AnimationReset(L"Pistol_Blast_R");
					GetAnimator()->AnimationReset(L"Eat");
					GetAnimator()->AnimationReset(L"Eat_R");
					GetAnimator()->AnimationReset(L"Drink");
					GetAnimator()->AnimationReset(L"Drink_R");
					if (m_btick) {
						CSound* hitsound = CResMgr::GetInst()->LoadSound(L"Hit_Ground", L"sound\\player\\vo_s_hurt_02 [1].wav");
						hitsound->Play();
						m_btick = false;
					}

					if (PLAYER_DIR::LEFT == m_EDir) {
						GetAnimator()->Play(L"Standing_Get_Hit", false);

					}
					else if (PLAYER_DIR::RIGHT == m_EDir) {
						GetAnimator()->Play(L"Standing_Get_Hit_R", false);
					}
					// State ��ȯ
					if (GetAnimator()->AnimationFinish(L"Standing_Get_Hit") || GetAnimator()->AnimationFinish(L"Standing_Get_Hit_R")) {
						GetAnimator()->AnimationReset(L"Standing_Get_Hit");
						GetAnimator()->AnimationReset(L"Standing_Get_Hit_R");
						m_bInvincible = true;
						m_fInvincibleTime = 0.f;
						m_fTime = 0.f;
						m_btick = true;
						m_bHitAir = true;
						m_EState = PLAYER_STATE::NORMAL;
						m_EAnim = PLAYER_ANIM::IDLE;
					}
					
				}

			//��ũ���� ���� ���
		else if (m_EAnim == PLAYER_ANIM::DUCK ||
			//���� ���� �ǰ�
				(m_EAnim == PLAYER_ANIM::ATTACK &&
				 m_EPrevAnim == PLAYER_ANIM::DUCK)) {

				//�ִϸ��̼� ����
				GetAnimator()->AnimationReset(L"Duck_Whip");
				GetAnimator()->AnimationReset(L"Duck_Whip_R");
				if (m_btick) {
					CSound* hitsound = CResMgr::GetInst()->LoadSound(L"Hit_Duck", L"sound\\player\\vo_s_hurt_03 [1].wav");
					hitsound->Play();
					m_btick = false;
				}
				
				if (PLAYER_DIR::LEFT == m_EDir) {
					GetAnimator()->Play(L"Duck_Get_Hit2", false);

				}
				else if (PLAYER_DIR::RIGHT == m_EDir) {
					GetAnimator()->Play(L"Duck_Get_Hit2_R", false);
				}
				// State ��ȯ
				if (GetAnimator()->AnimationFinish(L"Duck_Get_Hit2") || GetAnimator()->AnimationFinish(L"Duck_Get_Hit2_R")) {
					GetAnimator()->AnimationReset(L"Duck_Get_Hit2");
					GetAnimator()->AnimationReset(L"Duck_Get_Hit2_R");
					m_bInvincible = true;
					m_fInvincibleTime = 0.f;
					m_fTime = 0.f;
					m_bHitAir = true;
					m_EState = PLAYER_STATE::NORMAL;
					m_EAnim = PLAYER_ANIM::DUCK;
				}
			}
	}
		break;
	case PLAYER_STATE::NONE: {
		m_EState = PLAYER_STATE::NORMAL;
		m_EAnim = PLAYER_ANIM::NONE;
	}
	break;
	default:
		break;
	break;
	}

	// ��������
	Vec2 Velocity = GetRigidbody()->GetVelocity();
	if (!(GetRigidbody()->GetGround()) 
		&& (Velocity.y>0.f)
		&& m_EAnim != PLAYER_ANIM::HAT 
		&& m_EAnim != PLAYER_ANIM::NONE
		&& m_EAnim != PLAYER_ANIM::ATTACK
		&& m_EAnim != PLAYER_ANIM::SHOOT
		&& m_EAnim != PLAYER_ANIM::SCIMITAR
		&& m_EAnim != PLAYER_ANIM::TWIRL
		&& m_EAnim != PLAYER_ANIM::ENTER
		&& m_EAnim != PLAYER_ANIM::EXIT) {
		m_btick = true;
		m_EAnim = PLAYER_ANIM::FALL;
	}
	//�����ǰ�
	if (IsTap(KEY::R)) {
		if (m_EState != PLAYER_STATE::HIT&&m_bInvincible==false) {
			m_EState = PLAYER_STATE::HIT;
			--m_iHP;
			UpdateHeartContainer();
		}
	}
	//��������
	if (IsTap(KEY::Q)) {
		m_bforceinvincible = !m_bforceinvincible;
	}
	
	
	// virtual�� �����Ǿ��ֱ� ������ player�� tick�� ���� ȣ��ȴ�.
	// �θ� ������Ʈ�� Tick �� �����Ų��(Component Tick ȣ��)
	
	CObj::tick();
	
	
}

void CPlayer::render(HDC _dc)
{
	
	// �θ� ������Ʈ�� render �� �����Ų��(Component render ȣ��)
	CObj::render(_dc);
	
}





void CPlayer::Update() {
	//���� ���� ������Ʈ
	m_EPrevAnim = m_EAnim;
	m_EPrevState = m_EState;
	m_EPrevDir = m_EDir;
}
#include "pch.h"
#include "CSquidBaronDeath.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CTimeMgr.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CExplosion.h"
#include "CPlayer.h"


CSquidBaronDeath::CSquidBaronDeath()
	: m_pAtlas(nullptr)
	, m_fTime(0.f)
	, m_iExplosionCount(0)
	, m_vScale(Vec2(162.f, 195.f))
	, m_bIntensify(false)
{
	CreateAnimator();
	GetAnimator()->SetFloorPlay(true);
	GetAnimator()->LoadAnimation(L"animation\\monster\\SquidBaron_Die.anim");
	GetAnimator()->Play(L"SquidBaron_Die", true);
}

CSquidBaronDeath::~CSquidBaronDeath()
{
}

void CSquidBaronDeath::tick()
{
	//srand((UINT)time(NULL));
	//srand((UINT)CTimeMgr::GetInst()->ReturnCurCount());
	int pos = rand() % 4;
	int add = rand() % 100;
	m_fTime += DT;
	if (m_bIntensify == false) {
		if (m_fTime > 0.5f) {
			//왼쪽하단
			if (pos == 0) {
				Vec2 vPos = Vec2(GetPos().x - add, GetPos().y - m_vScale.y / 2 + add);
				CObj* cExplosion = new CExplosion(m_iExplosionCount%3);
				Instantiate(cExplosion, vPos, LAYER::DEATH_LEFTOVER);
			}
			//왼쪽상단
			else if (pos == 1) {
				Vec2 vPos = Vec2(GetPos().x - add, GetPos().y - m_vScale.y / 2 - add);
				CObj* cExplosion = new CExplosion(m_iExplosionCount % 3);
				Instantiate(cExplosion, vPos, LAYER::DEATH_LEFTOVER);
			}
			//우측상단
			else if (pos == 2) {
				Vec2 vPos = Vec2(GetPos().x + add, GetPos().y - m_vScale.y / 2 - add);
				CObj* cExplosion = new CExplosion(m_iExplosionCount % 3);
				Instantiate(cExplosion, vPos, LAYER::DEATH_LEFTOVER);
			}
			//우측하단
			else if (pos == 3) {
				Vec2 vPos = Vec2(GetPos().x + add, GetPos().y - m_vScale.y / 2 + add);
				CObj* cExplosion = new CExplosion(m_iExplosionCount % 3);
				Instantiate(cExplosion, vPos, LAYER::DEATH_LEFTOVER);
			}
			m_fTime = 0.f;
			++m_iExplosionCount;
		}
		if (m_iExplosionCount > 10) {
			m_bIntensify = true;
		}
	}
	else if (m_bIntensify == true) {
		if (m_fTime > 0.2f) {
			//왼쪽하단
			if (pos == 0) {
				Vec2 vPos = Vec2(GetPos().x - add, GetPos().y - m_vScale.y / 2 + add);
				CObj* cExplosion = new CExplosion(m_iExplosionCount % 3);
				Instantiate(cExplosion, vPos, LAYER::DEATH_LEFTOVER);
			}
			//왼쪽상단
			else if (pos == 1) {
				Vec2 vPos = Vec2(GetPos().x - add, GetPos().y - m_vScale.y / 2 - add);
				CObj* cExplosion = new CExplosion(m_iExplosionCount % 3);
				Instantiate(cExplosion, vPos, LAYER::DEATH_LEFTOVER);
			}
			//우측상단
			else if (pos == 2) {
				Vec2 vPos = Vec2(GetPos().x + add, GetPos().y - m_vScale.y / 2 - add);
				CObj* cExplosion = new CExplosion(m_iExplosionCount % 3);
				Instantiate(cExplosion, vPos, LAYER::DEATH_LEFTOVER);
			}
			//우측하단
			else if (pos == 3) {
				Vec2 vPos = Vec2(GetPos().x + add, GetPos().y - m_vScale.y / 2 + add);
				CObj* cExplosion = new CExplosion(m_iExplosionCount % 3);
				Instantiate(cExplosion, vPos, LAYER::DEATH_LEFTOVER);
			}
			m_fTime = 0.f;
			++m_iExplosionCount;
		}
		if (m_iExplosionCount > 30) {
			const vector<CObj*>& player = CLevelMgr::GetInst()->GetCurLevel()->GetLayer(LAYER::PLAYER);
			((CPlayer*)player[0])->SetAnim(PLAYER_ANIM::TWIRL);
			((CPlayer*)player[0])->SetbTick(true);
			SetDead();
		}
	}
	CObj::tick();
}

void CSquidBaronDeath::render(HDC _dc)
{
	CObj::render(_dc);
}




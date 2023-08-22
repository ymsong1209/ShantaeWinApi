#include "pch.h"
#include "CSquidBaronFood.h"
#include "CSquidBaron.h"
#include "CAnimator.h"
#include "CCollider.h"
#include "CResMgr.h"
#include "CHealEffect.h"
#include "CSound.h"
CSquidBaronFood::CSquidBaronFood(CSquidBaron* _pOwner)
	:m_pOwner(_pOwner)
{
	CreateAnimator();
	GetAnimator()->SetFloorPlay(true);
	GetAnimator()->LoadAnimation(L"animation\\monster\\SquidBaron_Food.anim");
	CSound* foodSpawn = CResMgr::GetInst()->LoadSound(L"foodspawn", L"sound\\monster\\baron_foodspawn.wav");
	foodSpawn->Play();
}

CSquidBaronFood::~CSquidBaronFood()
{
}
void CSquidBaronFood::tick()
{
	if (m_pOwner->IsDead())
	{
		SetDead();
	}
	else {
		if (GetAnimator()->AnimationFinish(L"SquidBaron_Food")) {
			++(m_pOwner->GetMonInfo().m_iGobbleCount);
			CObj* pHeal = new CHealEffect(6);
			Vec2 vPos = Vec2(m_pOwner->GetPos().x, m_pOwner->GetPos().y - m_pOwner->GetCollider()->GetScale().y);
			Instantiate(pHeal, vPos, LAYER::DAMAGE);
			m_pOwner->GetMonInfo().m_iHP += 6;
			if (m_pOwner->GetMonInfo().m_iHP > m_pOwner->GetMonInfo().m_iMaxHP) {
				m_pOwner->GetMonInfo().m_iHP = m_pOwner->GetMonInfo().m_iMaxHP;
			}

			if (m_pOwner->GetMonInfo().m_iGobbleCount < 4) {
				GetAnimator()->AnimationReset(L"SquidBaron_Food");
			}
			else {
				SetDead();
			}
		}
		else {
			GetAnimator()->Play(L"SquidBaron_Food", false);
		}
	}
	
	CObj::tick();
}

void CSquidBaronFood::render(HDC _dc)
{
	CObj::render(_dc);
}



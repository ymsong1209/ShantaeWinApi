#include "pch.h"
#include "CDeadState.h"
#include "CMonster.h"
#include "CCollider.h"
#include "CHeart.h"
#include "CGem.h"
#include "CTimeMgr.h"

CDeadState::CDeadState()
{
}

CDeadState::~CDeadState()
{
}

void CDeadState::finaltick()
{
	CMonster* pMon = dynamic_cast<CMonster*>(GetOwnerObj());
	pMon->dead();
	
	
}

void CDeadState::Enter()
{
	CMonster* pMon = dynamic_cast<CMonster*>(GetOwnerObj());
	//srand((UINT)CTimeMgr::GetInst()->ReturnCurCount());
	srand((UINT)time(NULL));
	int num = rand() % 10;
	Vec2 spawnVec = Vec2(pMon->GetPos().x, pMon->GetPos().y - pMon->GetCollider()->GetScale().y);
	if (5 <=num && num<10) {
		CObj* cGem = new CGem(pMon->GetMonInfo().m_iGemValue);
		Instantiate(cGem, spawnVec, LAYER::FIELD_OBJ);
	}
	else if (3<=num && num<5) {
		CObj* cheart = new CHeart;
		Instantiate(cheart, spawnVec, LAYER::FIELD_OBJ);
	}
	else if (0 <= num && num < 3) {

	}
	else {
		CObj* cGem = new CGem(pMon->GetMonInfo().m_iGemValue);
		Instantiate(cGem, spawnVec, LAYER::FIELD_OBJ);
	}
	
	pMon->dead_enter();
}

void CDeadState::Exit()
{
}



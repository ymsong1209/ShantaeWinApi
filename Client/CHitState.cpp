#include "pch.h"
#include "CHitState.h"
#include "CMonster.h"

CHitState::CHitState()
{
}

CHitState::~CHitState()
{
}

void CHitState::finaltick()
{
	CMonster* pMon = dynamic_cast<CMonster*>(GetOwnerObj());
	pMon->hit();
}


void CHitState::Enter()
{
	CMonster* pMon = dynamic_cast<CMonster*>(GetOwnerObj());
	pMon->hit_enter();
}

void CHitState::Exit()
{
	CMonster* pMon = dynamic_cast<CMonster*>(GetOwnerObj());
	pMon->hit_exit();
}
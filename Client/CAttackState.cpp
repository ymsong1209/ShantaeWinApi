#include "pch.h"
#include "CAttackState.h"
#include "CMonster.h"

CAttackState::CAttackState()
{
}

CAttackState::~CAttackState()
{
}

void CAttackState::finaltick()
{
	CMonster* pMon = dynamic_cast<CMonster*>(GetOwnerObj());
	pMon->attack();
	
}

void CAttackState::Enter()
{
	CMonster* pMon = dynamic_cast<CMonster*>(GetOwnerObj());
	pMon->attack_enter();
}

void CAttackState::Exit()
{
	CMonster* pMon = dynamic_cast<CMonster*>(GetOwnerObj());
	pMon->attack_exit();
}



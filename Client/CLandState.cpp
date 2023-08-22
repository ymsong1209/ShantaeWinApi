#include "pch.h"
#include "CLandState.h"
#include "CMonster.h"
#include "CRigidbody.h"

CLandState::CLandState()
{
}

CLandState::~CLandState()
{
}

void CLandState::finaltick()
{
	CMonster* pMon = dynamic_cast<CMonster*>(GetOwnerObj());
	pMon->land();
}


void CLandState::Enter()
{
	CMonster* pMon = dynamic_cast<CMonster*>(GetOwnerObj());
	pMon->land_enter();
}

void CLandState::Exit()
{
	CMonster* pMon = dynamic_cast<CMonster*>(GetOwnerObj());
	pMon->land_exit();
}
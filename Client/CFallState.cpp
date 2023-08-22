#include "pch.h"
#include "CFallState.h"
#include "CMonster.h"
#include "CRigidbody.h"

CFallState::CFallState()
{
}

CFallState::~CFallState()
{
}

void CFallState::finaltick()
{
	CMonster* pMon = dynamic_cast<CMonster*>(GetOwnerObj());
	pMon->fall();
	if (pMon->GetRigidbody()->GetGround() == true && pMon->GetRigidbody()->GetGravityUse() == true) {
		ChangeState(L"Land");
	}
}


void CFallState::Enter()
{
	CMonster* pMon = dynamic_cast<CMonster*>(GetOwnerObj());
	pMon->fall_enter();
}

void CFallState::Exit()
{
	CMonster* pMon = dynamic_cast<CMonster*>(GetOwnerObj());
	pMon->fall_exit();
}
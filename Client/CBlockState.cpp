#include "pch.h"
#include "CBlockState.h"
#include "CMonster.h"
#include "CRigidbody.h"

CBlockState::CBlockState()
{
}

CBlockState::~CBlockState()
{
}

void CBlockState::finaltick()
{
	CMonster* pMon = dynamic_cast<CMonster*>(GetOwnerObj());
	pMon->block();
}


void CBlockState::Enter()
{
	CMonster* pMon = dynamic_cast<CMonster*>(GetOwnerObj());
	pMon->block_enter();
}

void CBlockState::Exit()
{
	CMonster* pMon = dynamic_cast<CMonster*>(GetOwnerObj());
	pMon->block_exit();
}
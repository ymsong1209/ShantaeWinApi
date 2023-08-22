#include "pch.h"
#include "CCameraBlock.h"
#include "CCamera.h"
#include "CCollider.h"
#include "CPlayer.h"

CCameraBlock::CCameraBlock()
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(300.f, 100.f));
}

CCameraBlock::~CCameraBlock()
{
}



void CCameraBlock::BeginOverlap(CCollider* _pOther)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther->GetOwner());
	if (nullptr != pPlayer) {
		pPlayer->SetCameraFollow(!(pPlayer->ReturnCameraFollow()));
	}
	
}

void CCameraBlock::OnOverlap(CCollider* _pOther)
{
	
}

void CCameraBlock::EndOverlap(CCollider* _pOther)
{
	
}



#include "pch.h"
#include "CForceRespawn.h"
#include "CCollider.h"
#include "CPlayer.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CCamera.h"

CForceRespawn::CForceRespawn(Vec2 _vSpawnPos, Vec2 _vSize)
	:m_vSpawnPos(_vSpawnPos)
{
	CreateCollider();
	GetCollider()->SetScale(_vSize);

}

CForceRespawn::~CForceRespawn()
{
}

void CForceRespawn::tick()
{
	CObj::tick();
}

void CForceRespawn::BeginOverlap(CCollider* _pOther)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther->GetOwner());
	if (nullptr != pPlayer) {
		//CLevel* Curlevel = CLevelMgr::GetInst()->GetCurLevel();
		CCamera::GetInst()->FadeIn(2.f);
		pPlayer->SetPos(m_vSpawnPos);
	}

}

void CForceRespawn::OnOverlap(CCollider* _pOther)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther->GetOwner());
	if (nullptr != pPlayer) {
		pPlayer->SetPos(m_vSpawnPos);
	}
}

void CForceRespawn::render(HDC _dc)
{
	CObj::render(_dc);
}


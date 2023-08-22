#include "pch.h"
#include "CLevelChangeCollide.h"
#include "CPlayer.h"
#include "CCollider.h"
#include "CTimeMgr.h"

CLevelChangeCollide::CLevelChangeCollide(LEVEL_TYPE _layer, Vec2 _vSize)
	: m_ELayer(_layer)
	, m_vSize(_vSize)
	, m_fTime(0.f)
	, m_bLevelChange(false)
{
	CreateCollider();
	GetCollider()->SetScale(m_vSize);
}

CLevelChangeCollide::~CLevelChangeCollide()
{
}

void CLevelChangeCollide::tick()
{
	if (m_bLevelChange) {
		m_fTime += DT;
		if (m_fTime > 0.9f) {
			ChangeLevel(m_ELayer);
		}
	}
	CObj::tick();
}

void CLevelChangeCollide::BeginOverlap(CCollider* _pOther)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther->GetOwner());
	if (nullptr != pPlayer) {
		if (m_bLevelChange == false) {
			CCamera::GetInst()->FadeOut(1.f);
			m_bLevelChange = true;
		}
	}
}

void CLevelChangeCollide::OnOverlap(CCollider* _pOther)
{
}

void CLevelChangeCollide::render(HDC _dc)
{
	CObj::render(_dc);
}




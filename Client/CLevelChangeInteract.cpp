#include "pch.h"
#include "CLevelChangeInteract.h"
#include "CCollider.h"
#include "CLevelMgr.h"
#include "CTimeMgr.h"
#include "CLevel.h"
#include "CPlayer.h"


CLevelChangeInteract::CLevelChangeInteract(LEVEL_TYPE _layer, Vec2 _vSize)
	: m_ELayer(_layer)
	, m_fTime(0.f)
	, m_bLevelChange(false)
	, m_vSize(_vSize)
{
	CreateCollider();
	GetCollider()->SetScale(m_vSize);
}

CLevelChangeInteract::~CLevelChangeInteract()
{
}

void CLevelChangeInteract::tick()
{
	if (m_bLevelChange) {
		m_fTime += DT;
		if (m_fTime > 1.0) {
			ChangeLevel(m_ELayer);
		}
	}
	CObj::tick();
}



void CLevelChangeInteract::render(HDC _dc)
{
	CObj::render(_dc);
}

void CLevelChangeInteract::LevelChange()
{
	const vector<CObj*>& vecPlayer = CLevelMgr::GetInst()->GetCurLevel()->GetLayer(LAYER::PLAYER);
	m_bLevelChange = true;
	((CPlayer*)vecPlayer[0])->SetSpawnChange(true);
	((CPlayer*)vecPlayer[0])->SetSpawnPos(((CPlayer*)vecPlayer[0])->GetPos());
	CCamera::GetInst()->FadeOut(1.0f);
}



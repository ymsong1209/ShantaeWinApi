#include "pch.h"
#include "CSquidBanner.h"
#include "CSquidBaron.h"
#include "CAnimator.h"
#include "CResMgr.h"
#include "CTimeMgr.h"
#include "CTexture.h"
#include "CFSM.h"

CSquidBanner::CSquidBanner(CSquidBaron* _pOwner)
	: m_pAtlas(nullptr)
	, m_pOwner(_pOwner)
	, m_fSpeed(800.f)
{
	m_pAtlas = CResMgr::GetInst()->LoadTexture(L"SquidBaron_L", L"texture\\monster\\SquidBaron_L.bmp");
}

CSquidBanner::~CSquidBanner()
{
}

void CSquidBanner::tick()
{
	Vec2 vPos = GetPos();
	vPos.x -= DT * m_fSpeed;
	SetPos(vPos);
	if (vPos.x < -1400.f) {
		(m_pOwner->GetAI())->ChangeState(L"ArmorUp");
		SetDead();
	}
	CObj::tick();
}

void CSquidBanner::render(HDC _dc)
{
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vScale = Vec2(2403.f,267.f);
	TransparentBlt(_dc
		, int(vPos.x - vScale.x / 2)
		, int(vPos.y - vScale.y / 2)
		, int(vScale.x)
		, int(vScale.y)
		, m_pAtlas->GetDC()
		, 3
		, 66
		, int(vScale.x)
		, int(vScale.y)
		, RGB(0, 248, 0));
	CObj::render(_dc);
}
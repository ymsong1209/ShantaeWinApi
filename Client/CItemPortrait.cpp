#include "pch.h"
#include "CItemPortrait.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CPlayer.h"
#include "CMoneyNum.h"

CItemPortrait::CItemPortrait(CPlayer* _pOwner)
	: m_pAtlas(nullptr)
	, m_vSize{}
	, m_pOwner(_pOwner)
{
	m_pAtlas = CResMgr::GetInst()->LoadTexture(L"ItemPortrait", L"texture\\fx\\ItemPortrait.bmp");
	m_vSize = Vec2(363.f, 122.f);

}

CItemPortrait::~CItemPortrait()
{
}

void CItemPortrait::tick()
{
	CObj::tick();
}

void CItemPortrait::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	TransparentBlt(_dc
		, int(vPos.x)
		, int(vPos.y)
		, int(m_vSize.x)
		, int(m_vSize.y)
		, m_pAtlas->GetDC()
		, 0
		, 0
		, int(m_vSize.x)
		, int(m_vSize.y)
		, RGB(0, 248, 0));
	CObj::render(_dc);
}
#include "pch.h"
#include "CMoneyUI.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CPlayer.h"
#include "CMoneyNum.h"

CMoneyUI::CMoneyUI(CPlayer* _pOwner)
	: m_pAtlas(nullptr)
	, m_vSize{}
	, m_pOwner(_pOwner)
{
	m_pAtlas = CResMgr::GetInst()->LoadTexture(L"Money", L"texture\\fx\\Money.bmp");
	m_vSize = Vec2(409.f,104.f);
	
}

CMoneyUI::~CMoneyUI()
{
}

void CMoneyUI::tick()
{
	CObj::tick();
}

void CMoneyUI::render(HDC _dc)
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




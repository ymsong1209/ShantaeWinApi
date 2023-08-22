#include "pch.h"
#include "CItemNum.h"
#include "CResMgr.h"
#include "CTexture.h"

CItemNum::CItemNum(int _iNum)
	: m_pAtlas(nullptr)
	, m_iNum(_iNum)
	, m_vLeftTop(Vec2(5.f, 5.f))
	, m_vSize(Vec2(35.f, 40.f))
	, m_vSpace(Vec2(5.f, 0.f))
{
	m_pAtlas = CResMgr::GetInst()->LoadTexture(L"number3", L"texture\\fx\\number3.bmp");
}

CItemNum::~CItemNum()
{
}

void CItemNum::tick()
{
	CObj::tick();
}

void CItemNum::render(HDC _dc)
{
	Vec2 vPos = GetPos();

	if (m_iNum != 0) {
		//좌상단이 원점 => 좌상단->우하단으로 출력
		TransparentBlt(_dc
			, int(vPos.x)
			, int(vPos.y)
			, int(m_vSize.x)
			, int(m_vSize.y)
			, m_pAtlas->GetDC()
			//, int(m_vLeftTop.x)
			, int(m_vLeftTop.x + (m_iNum - 1) * (m_vSize.x + m_vSpace.x))
			, int(m_vLeftTop.y)
			, int(m_vSize.x)
			, int(m_vSize.y)
			, RGB(0, 248, 0));
	}
	else if (m_iNum == 0) {
		//좌상단이 원점 => 좌상단->우하단으로 출력
		TransparentBlt(_dc
			, int(vPos.x)
			, int(vPos.y)
			, int(m_vSize.x)
			, int(m_vSize.y)
			, m_pAtlas->GetDC()
			, int(365)
			, int(5)
			, int(m_vSize.x)
			, int(m_vSize.y)
			, RGB(0, 248, 0));
	}

	CObj::render(_dc);
}
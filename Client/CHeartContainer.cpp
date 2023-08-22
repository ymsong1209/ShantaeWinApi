#include "pch.h"
#include "CHeartContainer.h"
#include "CResMgr.h"
#include "CTexture.h"

CHeartContainer::CHeartContainer(int _heartNum)
	: m_pAtlas(nullptr)
	, m_iHeartNum(_heartNum)
	, m_vSize(Vec2(68.f,68.f))
	, m_vLeftTop{}
{
	m_pAtlas = CResMgr::GetInst()->LoadTexture(L"Heart", L"texture\\fx\\heart.bmp");
	m_vLeftTop = Vec2(m_vSize.x * m_iHeartNum , 0.f);
}

CHeartContainer::~CHeartContainer()
{
}

void CHeartContainer::tick()
{
	CObj::tick();
}

void CHeartContainer::render(HDC _dc)
{
	Vec2 vPos = GetPos();

	//좌상단이 원점 => 좌상단->우하단으로 출력
	TransparentBlt(_dc
		, int(vPos.x)
		, int(vPos.y)
		, int(m_vSize.x)
		, int(m_vSize.y)
		, m_pAtlas->GetDC()
		, int(m_vLeftTop.x)
		, int(m_vLeftTop.y)
		, int(m_vSize.x)
		, int(m_vSize.y)
		, RGB(0, 248, 0));
	CObj::render(_dc);
}

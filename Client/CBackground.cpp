#include "pch.h"
#include "CBackground.h"
#include "CTile.h"

#include "CResMgr.h"
#include "CTexture.h"

CBackground::CBackground(CTexture* m_pAtlas, Vec2 _vSize)
	: m_pAtlas(m_pAtlas)
	, m_vSize(_vSize)
	
{

}

CBackground::~CBackground()
{
}

void CBackground::tick()
{
	CObj::tick();
}

void CBackground::render(HDC _dc)
{
	//0,0부터 좌하단으로 
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(Vec2(0.f,0.f));
	TransparentBlt(_dc
		, (int)vPos.x
		, (int)vPos.y
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

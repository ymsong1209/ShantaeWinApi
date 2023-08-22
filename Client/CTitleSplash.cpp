#include "pch.h"
#include "CTitleSplash.h"
#include "CResMgr.h"
#include "CTimeMgr.h"
#include "CTexture.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CSound.h"


CTitleSplash::CTitleSplash()
	: m_pAtlas(nullptr)
	, m_fTime(0.f)
	, m_sound(nullptr)
	, m_bTime(false)
	, m_vSize(Vec2(504.f,462.f))
{
	m_pAtlas = CResMgr::GetInst()->LoadTexture(L"Logo", L"texture\\SplashScreens\\logo.bmp");
	m_sound = CResMgr::GetInst()->LoadSound(L"menu_confirm", L"sound\\fx\\menu_confirm.wav");
}

CTitleSplash::~CTitleSplash()
{
}

void CTitleSplash::tick()
{
	m_fTime += DT;
	if (m_bTime) {
		if (m_fTime > 1.0f) {
			ChangeLevel(LEVEL_TYPE::NORMAL_STAGE_01);
			m_fTime = 0.f;
		}
	}
	else if (!(m_bTime)) {
		if (m_fTime > 1.0f) {
			m_fTime = 1.0f;
		}
	}
	CObj::tick();
}

void CTitleSplash::render(HDC _dc)
{
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());
	TransparentBlt(_dc
		, int(vPos.x - m_vSize.x / 2.f)
		, int(vPos.y - m_vSize.y / 2.f)
		, int(m_vSize.x)
		, int(m_vSize.y)
		, m_pAtlas->GetDC()
		, int(0)
		, int(0)
		, int(m_vSize.x)
		, int(m_vSize.y)
		, RGB(0, 248, 0));
	/*if (m_bTime == true) {
		
	}
	else if (m_bTime == false) {
		
		BLENDFUNCTION tBlend = {};

		tBlend.AlphaFormat = AC_SRC_ALPHA;
		tBlend.BlendFlags = 0;
		tBlend.BlendOp = AC_SRC_OVER;
		tBlend.SourceConstantAlpha = (int)(255.f * m_fTime);

		AlphaBlend(_dc
			, int(vPos.x - m_vSize.x / 2.f)
			, int(vPos.y - m_vSize.y / 2.f)
			, int(m_vSize.x)
			, int(m_vSize.y)
			, m_pAtlas->GetDC()
			, int(0)
			, int(0)
			, int(m_vSize.x)
			, int(m_vSize.y)
			, tBlend);
	}*/
	
	CObj::render(_dc);
}

void CTitleSplash::transferlevel()
{
	m_sound->Play();
	m_bTime = true;
	m_fTime = 0.f;
	CCamera::GetInst()->FadeOut(1.f);
}




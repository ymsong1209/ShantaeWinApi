#include "pch.h"
#include "CHealEffect.h"
#include "CResMgr.h"
#include "CTimeMgr.h"
#include "CTexture.h"


CHealEffect::CHealEffect(int _Heal)
	: m_fTime(0.f)
	, m_iHeal(_Heal)
	, m_pAtlas(nullptr)
{
	m_pAtlas = CResMgr::GetInst()->LoadTexture(L"numbers", L"texture\\fx\\number.bmp");
}

CHealEffect::~CHealEffect()
{
}


void CHealEffect::tick()
{
	Vec2 vPos = GetPos();
	SetPos(Vec2(vPos.x, vPos.y - 0.1f));
	m_fTime += DT;
	if (m_fTime > 1.f) {
		SetDead();
	}
}

void CHealEffect::render(HDC _dc)
{
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());
	if (m_iHeal == 1) {
		BLENDFUNCTION tBlend = {};

		tBlend.AlphaFormat = AC_SRC_ALPHA;
		tBlend.BlendFlags = 0;
		tBlend.BlendOp = AC_SRC_OVER;
		tBlend.SourceConstantAlpha = (int)(255.f * (1.f - m_fTime));

		AlphaBlend(_dc
			, int(vPos.x - 14 / 2.f)
			, int(vPos.y - 25 / 2.f)
			, 14
			, 25
			, m_pAtlas->GetDC()
			, 48
			, 267
			, 14
			, 25
			, tBlend);
	}
	else if (m_iHeal == 2) {
		BLENDFUNCTION tBlend = {};

		tBlend.AlphaFormat = AC_SRC_ALPHA;
		tBlend.BlendFlags = 0;
		tBlend.BlendOp = AC_SRC_OVER;
		tBlend.SourceConstantAlpha = (int)(255.f * (1.f - m_fTime));

		AlphaBlend(_dc
			, int(vPos.x - 19 / 2.f)
			, int(vPos.y - 24 / 2.f)
			, 19
			, 24
			, m_pAtlas->GetDC()
			, 62
			, 268
			, 19
			, 24
			, tBlend);
	}
	else if (m_iHeal == 3) {
		BLENDFUNCTION tBlend = {};

		tBlend.AlphaFormat = AC_SRC_ALPHA;
		tBlend.BlendFlags = 0;
		tBlend.BlendOp = AC_SRC_OVER;
		tBlend.SourceConstantAlpha = (int)(255.f * (1.f - m_fTime));

		AlphaBlend(_dc
			, int(vPos.x - 19 / 2.f)
			, int(vPos.y - 24 / 2.f)
			, 19
			, 24
			, m_pAtlas->GetDC()
			, 82
			, 268
			, 19
			, 24
			, tBlend);
	}
	else if (m_iHeal == 4) {
		BLENDFUNCTION tBlend = {};

		tBlend.AlphaFormat = AC_SRC_ALPHA;
		tBlend.BlendFlags = 0;
		tBlend.BlendOp = AC_SRC_OVER;
		tBlend.SourceConstantAlpha = (int)(255.f * (1.f - m_fTime));

		AlphaBlend(_dc
			, int(vPos.x - 18 / 2.f)
			, int(vPos.y - 24 / 2.f)
			, 18
			, 24
			, m_pAtlas->GetDC()
			, 102
			, 268
			, 18
			, 24
			, tBlend);
	}
	else if (m_iHeal == 5) {
		BLENDFUNCTION tBlend = {};

		tBlend.AlphaFormat = AC_SRC_ALPHA;
		tBlend.BlendFlags = 0;
		tBlend.BlendOp = AC_SRC_OVER;
		tBlend.SourceConstantAlpha = (int)(255.f * (1.f - m_fTime));

		AlphaBlend(_dc
			, int(vPos.x - 19 / 2.f)
			, int(vPos.y - 24 / 2.f)
			, 19
			, 24
			, m_pAtlas->GetDC()
			, 122
			, 268
			, 19
			, 24
			, tBlend);
	}
	else if (m_iHeal == 6) {
		BLENDFUNCTION tBlend = {};

		tBlend.AlphaFormat = AC_SRC_ALPHA;
		tBlend.BlendFlags = 0;
		tBlend.BlendOp = AC_SRC_OVER;
		tBlend.SourceConstantAlpha = (int)(255.f * (1.f - m_fTime));

		AlphaBlend(_dc
			, int(vPos.x - 20 / 2.f)
			, int(vPos.y - 26 / 2.f)
			, 20
			, 26
			, m_pAtlas->GetDC()
			, 141
			, 267
			, 20
			, 26
			, tBlend);
	}
	else if (m_iHeal == 7) {
		BLENDFUNCTION tBlend = {};

		tBlend.AlphaFormat = AC_SRC_ALPHA;
		tBlend.BlendFlags = 0;
		tBlend.BlendOp = AC_SRC_OVER;
		tBlend.SourceConstantAlpha = (int)(255.f * (1.f - m_fTime));

		AlphaBlend(_dc
			, int(vPos.x - 20 / 2.f)
			, int(vPos.y - 24 / 2.f)
			, 20
			, 24
			, m_pAtlas->GetDC()
			, 161
			, 267
			, 20
			, 24
			, tBlend);
	}
	else if (m_iHeal == 8) {
		BLENDFUNCTION tBlend = {};

		tBlend.AlphaFormat = AC_SRC_ALPHA;
		tBlend.BlendFlags = 0;
		tBlend.BlendOp = AC_SRC_OVER;
		tBlend.SourceConstantAlpha = (int)(255.f * (1.f - m_fTime));

		AlphaBlend(_dc
			, int(vPos.x - 19 / 2.f)
			, int(vPos.y - 25 / 2.f)
			, 19
			, 25
			, m_pAtlas->GetDC()
			, 182
			, 267
			, 19
			, 25
			, tBlend);
	}
	else if (m_iHeal == 9) {
		BLENDFUNCTION tBlend = {};

		tBlend.AlphaFormat = AC_SRC_ALPHA;
		tBlend.BlendFlags = 0;
		tBlend.BlendOp = AC_SRC_OVER;
		tBlend.SourceConstantAlpha = (int)(255.f * (1.f - m_fTime));

		AlphaBlend(_dc
			, int(vPos.x - 19 / 2.f)
			, int(vPos.y - 25 / 2.f)
			, 19
			, 25
			, m_pAtlas->GetDC()
			, 202
			, 267
			, 19
			, 25
			, tBlend);
	}
	
}
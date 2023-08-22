#include "pch.h"
#include "CDamage.h"
#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CTexture.h"

CDamage::CDamage(int _iDmg, bool _isExtraDmg)
	: m_fTime(0.f)
	, m_iDmg(_iDmg)
	, m_bExtraDmg(_isExtraDmg)
	, m_pAtlas(nullptr)
{
	m_pAtlas = CResMgr::GetInst()->LoadTexture(L"numbers", L"texture\\fx\\number.bmp");
}

CDamage::~CDamage()
{
}

void CDamage::tick()
{
	Vec2 vPos = GetPos();
	SetPos(Vec2(vPos.x, vPos.y - 0.1f));
	m_fTime += DT;
	if (m_fTime > 1.f) {
		SetDead();
	}
}

void CDamage::render(HDC _dc)
{
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());
	
	//일반 대미지일시
	if (m_bExtraDmg == false) {
		if (m_iDmg == 0) {
			BLENDFUNCTION tBlend = {};

			tBlend.AlphaFormat = AC_SRC_ALPHA;
			tBlend.BlendFlags = 0;
			tBlend.BlendOp = AC_SRC_OVER;
			tBlend.SourceConstantAlpha = (int)(255.f * (1.f - m_fTime));

			AlphaBlend(_dc
				, int(vPos.x - 18 / 2.f)
				, int(vPos.y - 25 / 2.f)
				, 18
				, 25
				, m_pAtlas->GetDC()
				, 40
				, 242
				, 18
				, 25
				, tBlend);
		}
		else if (m_iDmg == 1) {
			BLENDFUNCTION tBlend = {};

			tBlend.AlphaFormat = AC_SRC_ALPHA;
			tBlend.BlendFlags = 0;
			tBlend.BlendOp = AC_SRC_OVER;
			tBlend.SourceConstantAlpha = (int)(255.f * (1.f - m_fTime));

			AlphaBlend(_dc
				, int(vPos.x - 13 / 2.f)
				, int(vPos.y - 25 / 2.f)
				, 13
				, 25
				, m_pAtlas->GetDC()
				, 58
				, 242
				, 13
				, 25
				, tBlend);
		}
		else if (m_iDmg == 2) {
			BLENDFUNCTION tBlend = {};

			tBlend.AlphaFormat = AC_SRC_ALPHA;
			tBlend.BlendFlags = 0;
			tBlend.BlendOp = AC_SRC_OVER;
			tBlend.SourceConstantAlpha = (int)(255.f * (1.f - m_fTime));

			AlphaBlend(_dc
				, int(vPos.x - 20 / 2.f)
				, int(vPos.y - 25 / 2.f)
				, 20
				, 25
				, m_pAtlas->GetDC()
				, 71
				, 243
				, 20
				, 25
				, tBlend);
		}
		else if (m_iDmg == 3) {
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
				, 92
				, 242
				, 20
				, 26
				, tBlend);
		}
		else if (m_iDmg == 4) {
			BLENDFUNCTION tBlend = {};

			tBlend.AlphaFormat = AC_SRC_ALPHA;
			tBlend.BlendFlags = 0;
			tBlend.BlendOp = AC_SRC_OVER;
			tBlend.SourceConstantAlpha = (int)(255.f * (1.f - m_fTime));

			AlphaBlend(_dc
				, int(vPos.x - 21 / 2.f)
				, int(vPos.y - 25 / 2.f)
				, 21
				, 25
				, m_pAtlas->GetDC()
				, 111
				, 243
				, 21
				, 25
				, tBlend);
		}
		else if (m_iDmg == 5) {
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
				, 132
				, 242
				, 19
				, 25
				, tBlend);
		}
		else if (m_iDmg == 6) {
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
			, 152
			, 242
			, 19
			, 25
			, tBlend);
		}
		else if (m_iDmg == 7) {
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
			, 172
			, 242
			, 20
			, 24
			, tBlend);
		}
		else if (m_iDmg == 8) {
		BLENDFUNCTION tBlend = {};

		tBlend.AlphaFormat = AC_SRC_ALPHA;
		tBlend.BlendFlags = 0;
		tBlend.BlendOp = AC_SRC_OVER;
		tBlend.SourceConstantAlpha = (int)(255.f * (1.f - m_fTime));

		AlphaBlend(_dc
			, int(vPos.x - 21 / 2.f)
			, int(vPos.y - 25 / 2.f)
			, 19
			, 25
			, m_pAtlas->GetDC()
			, 191
			, 242
			, 21
			, 25
			, tBlend);
		}
		else if (m_iDmg == 9) {
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
			, 212
			, 242
			, 19
			, 25
			, tBlend);
		}
	}
	else if (m_bExtraDmg == true) {
		if (m_iDmg == 0) {
			/*BLENDFUNCTION tBlend = {};

			tBlend.AlphaFormat = AC_SRC_ALPHA;
			tBlend.BlendFlags = 0;
			tBlend.BlendOp = AC_SRC_OVER;
			tBlend.SourceConstantAlpha = (int)(255.f * (1.f - m_fTime));

			AlphaBlend(_dc
				, int(vPos.x - 12 / 2.f)
				, int(vPos.y - 24 / 2.f)
				, 18
				, 23
				, m_pAtlas->GetDC()
				, 57
				, 215
				, 18
				, 23
				, tBlend);*/
		}
		else if (m_iDmg == 1) {
			BLENDFUNCTION tBlend = {};

			tBlend.AlphaFormat = AC_SRC_ALPHA;
			tBlend.BlendFlags = 0;
			tBlend.BlendOp = AC_SRC_OVER;
			tBlend.SourceConstantAlpha = (int)(255.f * (1.f - m_fTime));

			AlphaBlend(_dc
				, int(vPos.x - 12 / 2.f)
				, int(vPos.y - 24 / 2.f)
				, 12
				, 24
				, m_pAtlas->GetDC()
				, 76
				, 214
				, 12
				, 24
				, tBlend);
		}
		else if (m_iDmg == 2) {
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
				, 89
				, 214
				, 19
				, 25
				, tBlend);
		}
		else if (m_iDmg == 3) {
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
				, 109
				, 214
				, 19
				, 25
				, tBlend);
		}
		else if (m_iDmg == 4) {
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
				, 128
				, 214
				, 20
				, 26
				, tBlend);
		}
		else if (m_iDmg == 5) {
			BLENDFUNCTION tBlend = {};

			tBlend.AlphaFormat = AC_SRC_ALPHA;
			tBlend.BlendFlags = 0;
			tBlend.BlendOp = AC_SRC_OVER;
			tBlend.SourceConstantAlpha = (int)(255.f * (1.f - m_fTime));

			AlphaBlend(_dc
				, int(vPos.x - 20 / 2.f)
				, int(vPos.y - 25 / 2.f)
				, 20
				, 25
				, m_pAtlas->GetDC()
				, 148
				, 214
				, 20
				, 25
				, tBlend);
		}
		else if (m_iDmg == 6) {
			BLENDFUNCTION tBlend = {};

			tBlend.AlphaFormat = AC_SRC_ALPHA;
			tBlend.BlendFlags = 0;
			tBlend.BlendOp = AC_SRC_OVER;
			tBlend.SourceConstantAlpha = (int)(255.f * (1.f - m_fTime));

			AlphaBlend(_dc
				, int(vPos.x - 20 / 2.f)
				, int(vPos.y - 25 / 2.f)
				, 20
				, 25
				, m_pAtlas->GetDC()
				, 168
				, 214
				, 20
				, 25
				, tBlend);
		}
		else if (m_iDmg == 7) {
			BLENDFUNCTION tBlend = {};

			tBlend.AlphaFormat = AC_SRC_ALPHA;
			tBlend.BlendFlags = 0;
			tBlend.BlendOp = AC_SRC_OVER;
			tBlend.SourceConstantAlpha = (int)(255.f * (1.f - m_fTime));

			AlphaBlend(_dc
				, int(vPos.x - 20 / 2.f)
				, int(vPos.y - 25 / 2.f)
				, 20
				, 25
				, m_pAtlas->GetDC()
				, 188
				, 214
				, 20
				, 25
				, tBlend);
		}
		else if (m_iDmg == 8) {
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
				, 208
				, 214
				, 20
				, 26
				, tBlend);
		}
		else if (m_iDmg == 9) {
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
				, 229
				, 214
				, 19
				, 25
				, tBlend);
		}
	}
}
	
	

	


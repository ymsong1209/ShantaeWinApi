#include "pch.h"
#include "CDust.h"
#include "CResMgr.h"
#include "CCollider.h"
#include "CTexture.h"
#include "CPlatform.h"
#include "CWall.h"
#include "CCeiling.h"
#include "CRigidbody.h"
#include "CTimeMgr.h"

CDust::CDust(int _particleNum)
	: m_pAtlas(nullptr)
	, m_iParticleNum(_particleNum)
	, m_vLeftTop{}
	, m_vSize{}
	, m_fTime(0.f)
	, m_bFade(true)
{
	m_pAtlas = CResMgr::GetInst()->LoadTexture(L"fx_L", L"texture\\fx\\fx_L.bmp");
	
	CreateRigidbody();
	GetRigidbody()->SetGravity(false);

	if (m_iParticleNum == 0) {
		m_vLeftTop = Vec2(3.f, 4146.f);
		m_vSize = Vec2(54.f, 36.f);
		GetRigidbody()->SetVelocity(Vec2(-100.f, 0.f));
	}
	else if (m_iParticleNum == 1) {
		m_vLeftTop = Vec2(60.f, 4146.f);
		m_vSize = Vec2(54.f, 36.f);
		GetRigidbody()->SetVelocity(Vec2(-80.f, 0.f));
	}
	else if (m_iParticleNum == 2) {
		m_vLeftTop = Vec2(117.f, 4146.f);
		m_vSize = Vec2(54.f, 36.f);
		GetRigidbody()->SetVelocity(Vec2(0.f, 0.f));
	}
	else if (m_iParticleNum == 3) {
		m_vLeftTop = Vec2(174.f, 4146.f);
		m_vSize = Vec2(54.f, 36.f);
		GetRigidbody()->SetVelocity(Vec2(80.f, 0.f));
	}
	else if (m_iParticleNum == 4) {
		m_vLeftTop = Vec2(231.f, 4146.f);
		m_vSize = Vec2(54.f, 36.f);
		GetRigidbody()->SetVelocity(Vec2(100.f, 0.f));
	}
	else {
		m_vLeftTop = Vec2(231.f, 4146.f);
		m_vSize = Vec2(54.f, 36.f);
	}
	//GetCollider()->SetScale(m_vSize);

}

CDust::~CDust()
{
}


void CDust::tick()
{
	m_fTime += DT;

	if (m_bFade == true) {
		if (m_fTime > 1.0f) {
			SetDead();
		}
	}
	else {
		if (m_fTime > 3.0) {
			m_bFade = true;
			m_fTime = 0.f;
		}
	}
	CObj::tick();
}

void CDust::render(HDC _dc)
{
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());
	if (m_bFade == false) {
		TransparentBlt(_dc
			, int(vPos.x - m_vSize.x / 2.f)
			, int(vPos.y - m_vSize.y / 2.f)
			, int(m_vSize.x)
			, int(m_vSize.y)
			, m_pAtlas->GetDC()
			, int(m_vLeftTop.x)
			, int(m_vLeftTop.y)
			, int(m_vSize.x)
			, int(m_vSize.y)
			, RGB(0, 248, 0));
	}
	else if (m_bFade == true) {

		BLENDFUNCTION tBlend = {};

		tBlend.AlphaFormat = AC_SRC_ALPHA;
		tBlend.BlendFlags = 0;
		tBlend.BlendOp = AC_SRC_OVER;
		tBlend.SourceConstantAlpha = (int)(255.f * (1 - m_fTime));

		AlphaBlend(_dc
			, int(vPos.x - m_vSize.x / 2.f)
			, int(vPos.y - m_vSize.y / 2.f)
			, int(m_vSize.x)
			, int(m_vSize.y)
			, m_pAtlas->GetDC()
			, int(m_vLeftTop.x)
			, int(m_vLeftTop.y)
			, int(m_vSize.x)
			, int(m_vSize.y)
			, tBlend);
	}

	CObj::render(_dc);
}

void CDust::BeginOverlap(CCollider* _pOther)
{
	/*CPlatform* cPlatform = dynamic_cast<CPlatform*>(_pOther->GetOwner());
	if (nullptr != cPlatform) {
		if (GetRigidbody()->GetGround() == false) {
			Vec2 vel = GetRigidbody()->GetVelocity();
			if (0.f <= vel.y && vel.y < 5.f) {
				GetRigidbody()->SetGround(true);
				GetRigidbody()->SetVelocity(Vec2(0.f, 0.f));
			}
			else {
				if (vel.y > 0.f) {
					GetRigidbody()->SetVelocity(Vec2(vel.x * 0.5f, -vel.y * 0.5f));
				}
			}
		}
	}

	CWall* cWall = dynamic_cast<CWall*>(_pOther->GetOwner());
	if (nullptr != cWall) {
		Vec2 vel = GetRigidbody()->GetVelocity();
		GetRigidbody()->SetVelocity(Vec2(0.f, vel.y));
	}*/
}

void CDust::OnOverlap(CCollider* _pOther)
{
	/*CPlatform* cPlatform = dynamic_cast<CPlatform*>(_pOther->GetOwner());
	if (nullptr != cPlatform) {
		if (GetRigidbody()->GetGround() == false) {
			Vec2 vel = GetRigidbody()->GetVelocity();
			if (0.f <= vel.y && vel.y < 5.f) {
				GetRigidbody()->SetGround(true);
				GetRigidbody()->SetVelocity(Vec2(0.f, 0.f));
			}
			else {
				if (vel.y > 0.f) {
					GetRigidbody()->SetVelocity(Vec2(vel.x * 0.5f, -vel.y * 0.5f));
				}
			}
		}


	}*/
}
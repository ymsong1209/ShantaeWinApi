#include "pch.h"
#include "CPotParticle.h"
#include "CResMgr.h"
#include "CCollider.h"
#include "CTexture.h"
#include "CPlatform.h"
#include "CWall.h"
#include "CCeiling.h"
#include "CRigidbody.h"
#include "CTimeMgr.h"

CPotParticle::CPotParticle(int _particleNum)
	: m_pAtlas(nullptr)
	, m_iParticleNum(_particleNum)
	, m_vLeftTop{}
	, m_vSize{}
	, m_fTime(0.f)
	, m_bFade(false)
{
	m_pAtlas = CResMgr::GetInst()->LoadTexture(L"Objects", L"texture\\objects\\Objects.bmp");
	CreateCollider();
	CreateRigidbody();
	GetRigidbody()->SetGravity(true);
	GetRigidbody()->SetGravityAccel(800.f);
	GetRigidbody()->SetGravityVelocityLimit(1000.f);
		
	if (m_iParticleNum == 0) {
		m_vLeftTop = Vec2(15.f, 85.f);
		m_vSize = Vec2(20.f, 30.f);
	}
	else if (m_iParticleNum == 1) {
		m_vLeftTop = Vec2(157.f, 90.f);
		m_vSize = Vec2(30.f, 20.f);
	}
	else if (m_iParticleNum == 2) {
		m_vLeftTop = Vec2(277.f, 87.f);
		m_vSize = Vec2(20.f, 25.f);
	}
	else {
		m_vLeftTop = Vec2(202.f, 125.f);
		m_vSize = Vec2(18.f, 17.f);
	}
	GetCollider()->SetScale(m_vSize);

}

CPotParticle::~CPotParticle()
{
}


void CPotParticle::tick()
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

void CPotParticle::render(HDC _dc)
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
	else if( m_bFade == true) {
		
		BLENDFUNCTION tBlend = {};

		tBlend.AlphaFormat = AC_SRC_ALPHA;
		tBlend.BlendFlags = 0;
		tBlend.BlendOp = AC_SRC_OVER;
		tBlend.SourceConstantAlpha = (int)(255.f *(1 - m_fTime));

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

void CPotParticle::BeginOverlap(CCollider* _pOther)
{
	CPlatform* cPlatform = dynamic_cast<CPlatform*>(_pOther->GetOwner());
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
	}
}

void CPotParticle::OnOverlap(CCollider* _pOther)
{
	CPlatform* cPlatform = dynamic_cast<CPlatform*>(_pOther->GetOwner());
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
}




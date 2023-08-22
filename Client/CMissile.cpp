#include "pch.h"
#include "CMissile.h"
#include "CTimeMgr.h"
#include "CCollider.h"

CMissile::CMissile()
	:	m_fSpeed(200.f)
	,	m_fDegree(80.f)
	,	m_fTime(0.f)
	
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(20.f, 20.f));
}

CMissile::~CMissile()
{
}
void CMissile::tick()
{
	Vec2 vPos = GetPos();
	//vPos.y -= m_fSpeed * DT;
	//대각선으로 쏘기
	float fRadian = (m_fDegree * PI) / 180.f;
	vPos.x += m_fSpeed * cosf(fRadian) * DT;
	vPos.y -= m_fSpeed * sinf(fRadian) * DT;

	SetPos(vPos);
	m_fTime += DT;
	if (1.f < m_fTime) {
		SetDead();
	}
	CObj::tick();
}

void CMissile::render(HDC _dc)
{
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vSize = GetScale();
	Ellipse(_dc, (int)(vPos.x - vSize.x / 2.f)
		, (int)(vPos.y - vSize.y / 2.f)
		, (int)(vPos.x + vSize.x / 2.f)
		, (int)(vPos.y + vSize.y / 2.f));
	CObj::render(_dc);
}

void CMissile::BeginOverlap(CCollider* _pOther)
{
	//SetDead();
}
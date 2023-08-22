#include "pch.h"
#include "CPikeBall.h"
#include "CTexture.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"
#include "CPlayer.h"
#include "CResMgr.h"
#include "CTimeMgr.h"
#include "CCamera.h"


CPikeBall::CPikeBall(CPlayer* _pOwner)
	: m_pOwner(_pOwner)
	, m_fSpeed(200.f)
	, m_fTime(0.f)
	, m_iDamage(5)
	, m_fDistance(100.f)
	, m_pAtlas(nullptr)
{
	CreateCollider();
	CreateAnimator();
	GetCollider()->SetScale(Vec2(51.f, 51.f));
	m_pAtlas = CResMgr::GetInst()->LoadTexture(L"fx_L", L"texture\\fx\\fx_L.bmp");
}

CPikeBall::~CPikeBall()
{
}
void CPikeBall::tick()
{
	m_fTime += DT;
	if (m_fTime > 10.f) {
		m_pOwner->SetIsPikeBall(false);
		SetDead();
	}
	//vPos = PlayerÁß½É ÁÂÇ¥
	Vec2 vPos = Vec2(m_pOwner->GetPos().x, m_pOwner->GetPos().y - m_pOwner->GetCollider()->GetScale().y / 2);
	float fRadian = (m_fTime * PI) / 180.f * m_fSpeed;
	vPos.x += m_fDistance * cosf(fRadian) ;
	vPos.y -= m_fDistance * sinf(fRadian);
	SetPos(vPos);

	CObj::tick();
}

void CPikeBall::render(HDC _dc)
{
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vScale = GetCollider()->GetScale();
	TransparentBlt(_dc
		, int(vPos.x - vScale.x /2)
		, int(vPos.y - vScale.y / 2)
		, int(vScale.x)
		, int(vScale.y)
		, m_pAtlas->GetDC()
		, 3
		, 7626
		, int(vScale.x)
		, int(vScale.y)
		, RGB(0, 248, 0));

	CObj::render(_dc);
}

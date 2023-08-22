#include "pch.h"
#include "CImpact_Small.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CResMgr.h"
#include "CTexture.h"


CImpact_Small::CImpact_Small()
	:m_pAtlas(nullptr)
{
	CreateAnimator();
	m_pAtlas = CResMgr::GetInst()->LoadTexture(L"fx_L", L"texture\\monster\\fx_L.bmp");
	/*GetAnimator()->CreateAnimation(L"Impact_Small", m_pAtlas, Vec2(3.f, 3969.f), Vec2(123.f, 114.f), Vec2(0.f, 0.f), Vec2(3.f, 3.f), 5, 1, 5, 0.05f);
	GetAnimator()->FindAnimation(L"Impact_Small")->Save(L"animation\\fx\\Impact_Small.anim");*/
	GetAnimator()->LoadAnimation(L"animation\\fx\\Impact_Small.anim");
	GetAnimator()->Play(L"Impact_Small", false);
}

CImpact_Small::~CImpact_Small()
{
}
void CImpact_Small::tick()
{
	if (GetAnimator()->AnimationFinish(L"Impact_Small")) SetDead();
	CObj::tick();
}

void CImpact_Small::render(HDC _dc)
{
	CObj::render(_dc);
}

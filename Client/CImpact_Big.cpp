#include "pch.h"
#include "CImpact_Big.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CResMgr.h"
#include "CTexture.h"


CImpact_Big::CImpact_Big()
	:m_pAtlas(nullptr)
{
	CreateAnimator();
	m_pAtlas = CResMgr::GetInst()->LoadTexture(L"fx_L", L"texture\\monster\\fx_L.bmp");
	/*GetAnimator()->CreateAnimation(L"Impact_Big", m_pAtlas, Vec2(3.f, 3720.f), Vec2(204.f, 186.f), Vec2(0.f, 0.f), Vec2(3.f, 3.f), 6, 1, 6, 0.05f);
	GetAnimator()->FindAnimation(L"Impact_Big")->Save(L"animation\\fx\\Impact_Big.anim");*/
	GetAnimator()->LoadAnimation(L"animation\\fx\\Impact_Big.anim");
	GetAnimator()->Play(L"Impact_Big", false);
}

CImpact_Big::~CImpact_Big()
{
}
void CImpact_Big::tick()
{
	if (GetAnimator()->AnimationFinish(L"Impact_Big")) SetDead();
	CObj::tick();
}

void CImpact_Big::render(HDC _dc)
{
	CObj::render(_dc);
}


#include "pch.h"
#include "CBathWoman.h"
#include "CResMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CTexture.h"

CBathWoman::CBathWoman()
{
	CreateAnimator();
	CTexture* BathWoman = CResMgr::GetInst()->LoadTexture(L"BathWoman_npc", L"texture\\npc\\BathWoman.bmp");
	GetAnimator()->CreateAnimation(L"BathWoman", BathWoman, Vec2(4.f, 84.f), Vec2(92.f, 184.f), Vec2(0.f, 0.f), Vec2(4.f, 0.f), 11, 1, 11, 0.1f);
	GetAnimator()->FindAnimation(L"BathWoman")->Save(L"animation\\npc\\BathWoman.anim");
	GetAnimator()->LoadAnimation(L"animation\\npc\\BathWoman.anim");
	GetAnimator()->Play(L"BathWoman", true);
}

CBathWoman::~CBathWoman()
{
}
void CBathWoman::tick()
{
	CObj::tick();
}

void CBathWoman::render(HDC _dc)
{
	CObj::render(_dc);
}





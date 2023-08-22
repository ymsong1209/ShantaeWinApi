#include "pch.h"
#include "CSquidHeart.h"
#include "CPlayer.h"
#include "CPlatform.h"
#include "CCollider.h"

#include "CAnimator.h"
#include "CAnimation.h"
#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CPathMgr.h"
#include "CSound.h"

CSquidHeart::CSquidHeart()
{
	CreateCollider();
	CreateAnimator();
	m_sound = CResMgr::GetInst()->LoadSound(L"SquidHeart", L"sound\\fx\\pickup_heart_container.wav");
	CTexture* Object = CResMgr::GetInst()->LoadTexture(L"Objects", L"texture\\objects\\Objects.bmp");
	/*GetAnimator()->CreateAnimation(L"SquidHeart", Object, Vec2(5.f, 765.f), Vec2(60.f, 57.f), Vec2(0.f, 0.f), Vec2(5.f, 0.f), 5, 1, 5, 0.1f);
	GetAnimator()->FindAnimation(L"SquidHeart")->Save(L"animation\\object\\SquidHeart.anim");*/
	GetAnimator()->LoadAnimation(L"animation\\object\\SquidHeart.anim");
	GetCollider()->SetScale(Vec2(60.f, 57.f));

}

CSquidHeart::~CSquidHeart()
{
}

void CSquidHeart::tick()
{
	
	GetAnimator()->Play(L"SquidHeart", true);

	CObj::tick();
}

void CSquidHeart::render(HDC _dc)
{
	CObj::render(_dc);
}

void CSquidHeart::BeginOverlap(CCollider* _pOther)
{
	CPlayer* cPlayer = dynamic_cast<CPlayer*>(_pOther->GetOwner());
	if (nullptr != cPlayer) {
		m_sound->Play();
		cPlayer->SetSquidHeart(cPlayer->ReturnSquidHeart() + 1);
		SetDead();
	}
}
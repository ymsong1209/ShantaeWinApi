#include "pch.h"
#include "CSquidSmith.h"
#include "CResMgr.h"
#include "CPlayer.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CSound.h"

CSquidSmith::CSquidSmith()
	: m_pAtlas(nullptr)
	, m_bForge(false)
{
	m_pAtlas = CResMgr::GetInst()->LoadTexture(L"SquidSmith_npc", L"texture\\npc\\SquidSmith.bmp");
	CreateAnimator();
	GetAnimator()->SetFloorPlay(true);
	/*GetAnimator()->CreateAnimation(L"SquidSmith_Slam", m_pAtlas, Vec2(3.f, 516.f), Vec2(426.f, 384.f), Vec2(55.f, 0.f), Vec2(3.f, 12.f), 69, 10, 7, 0.1f);
	GetAnimator()->FindAnimation(L"SquidSmith_Slam")->Save(L"animation\\npc\\SquidSmith_Slam.anim");*/
	GetAnimator()->LoadAnimation(L"animation\\npc\\SquidSmith_Idle.anim");
	GetAnimator()->LoadAnimation(L"animation\\npc\\SquidSmith_Slam.anim");
	GetAnimator()->Play(L"SquidSmith_Idle", true);
	
	CreateCollider();
	GetCollider()->SetScale(Vec2(506.f,206.f));
	GetCollider()->SetOffsetPos(Vec2(0.f, -50.f));
}

CSquidSmith::~CSquidSmith()
{
}


//GetAnimator()->CreateAnimation(L"SquidSmith_Idle", pSquidSmithTex, Vec2(3.f, 63.f), Vec2(102.f, 159.f), Vec2(0.f, 0.f), Vec2(3.f, 0.f), 8, 1, 8, 0.1f);
//
//GetAnimator()->FindAnimation(L"SquidSmith_Idle")->Save(L"animation\\npc\\SquidSmith\\SquidSmith_Idle.anim");
//
//


void CSquidSmith::Slam()
{
	GetAnimator()->Play(L"SquidSmith_Slam", false);
	m_bForge = true;
}

void CSquidSmith::tick()
{
	if (GetAnimator()->AnimationFinish(L"SquidSmith_Slam")) {
		const vector<CObj*>& vecPlayer =CLevelMgr::GetInst()->GetCurLevel()->GetLayer(LAYER::PLAYER);
		((CPlayer*)vecPlayer[0])->SetSquidHeart(((CPlayer*)vecPlayer[0])->ReturnSquidHeart() - 4);
		((CPlayer*)vecPlayer[0])->SetMaxHP(((CPlayer*)vecPlayer[0])->ReturnMaxHP() + 4);
		((CPlayer*)vecPlayer[0])->SetHP(((CPlayer*)vecPlayer[0])->ReturnMaxHP());
		((CPlayer*)vecPlayer[0])->UpdateHeartContainer();

		((CPlayer*)vecPlayer[0])->SetMoney(((CPlayer*)vecPlayer[0])->ReturnMoney() - 100);
		((CPlayer*)vecPlayer[0])->UpdateMoney();
		GetAnimator()->AnimationReset(L"SquidSmith_Slam");
		CSound* sound = CResMgr::GetInst()->LoadSound(L"PowerUp", L"sound\\player\\vo_s_power_up_02 [1].wav");
		sound->Play();
		GetAnimator()->Play(L"SquidSmith_Idle",true);
		m_bForge = false;
	}
	CObj::tick();
}

void CSquidSmith::render(HDC _dc)
{
	CObj::render(_dc);
}

void CSquidSmith::OnOverlap(CCollider* _pOther)
{
	//CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther->GetOwner());
	
}





#include "pch.h"
#include "CCamera.h"
#include "CGalaga.h"
#include "CEngine.h"
#include "CObj.h"
#include "CGalagaPlayer.h"
#include "CGalagaMonster.h"
#include "CGallagBackground.h"
#include "CCollisionMgr.h"
#include "CTimeMgr.h"
#include "CLevel.h"

CObj* pObj;
CGalaga::CGalaga()
	:m_time(0)
{
}

CGalaga::~CGalaga()
{
}

void CGalaga::init()
{
	// Player 생성
	CObj* pObj = new CGalagaPlayer;
	pObj->SetPos(Vec2(375.f, 500.f));
	pObj->SetScale(Vec2(64.f, 64.f));
	CGalagaPlayer* player1 = (CGalagaPlayer*)pObj;
	player1->SetSpeed(400.f);
	AddObject((CObj*)player1, LAYER::PLAYER);

	//해상도 : 750 / 900
	CObj* pBackground = new CGallagBackground;
	pBackground->SetPos(Vec2(375.f, 175.f));
	pBackground->SetScale(Vec2(750.f, 1500.f));
	AddObject(pBackground, LAYER::BACKGROUND);

	CObj* pBackground2 = new CGallagBackground;
	pBackground2->SetPos(Vec2(375.f, -662.5f));
	pBackground2->SetScale(Vec2(750.f, 1600.f));
	AddObject(pBackground2, LAYER::BACKGROUND);



	// Level 의 충돌 설정
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::MONSTER);
	//CCollisionMgr::GetInst()->LayerCheck(LAYER::MONSTER, LAYER::MONSTER);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::MONSTER_PROJECTILE);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER_PROJECTILE, LAYER::MONSTER);

	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	CCamera::GetInst()->SetLook(vResolution / 2.f);
	

}

void CGalaga::tick()
{
	int random =  rand()%750;
	float trand = rand() % 5 + 1.f;
	m_time += DT;
	if (m_time > trand) {
		CGalagaMonster* pMonster = new CGalagaMonster;
		pMonster->SetPos(Vec2((float)random, 200.f));
		pMonster->SetScale(Vec2(150.f, 150.f));
		if (ReturnPlayer() != nullptr) {
			pMonster->SetTarget(ReturnPlayer());
		}
		
		AddObject(pMonster, LAYER::MONSTER);
		m_time = 0;
	}
	CLevel::tick();
}

void CGalaga::render(HDC _dc)
{
	
	
	CLevel::render(_dc);
}

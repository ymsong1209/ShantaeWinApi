#include "pch.h"
#include "CDebugLevel.h"
#include "CEngine.h"
#include "CObj.h"

#include "CCamera.h"
#include "CResMgr.h"
#include "CCollisionMgr.h"
#include "CCollider.h"
#include "CKeyMgr.h"


#include "CPlayer.h"
#include "CForce.h"
#include "CPlatform.h"
#include "CCeiling.h"
#include "CWall.h"
#include "CForceDuck.h"
#include "CCameraBlock.h"
#include "CCeiling.h"

#include "CItem.h"
#include "CPot.h"
#include "CHeart.h"
#include "CGem.h"
#include "CSquidHeart.h"
#include "CDamage.h"
#include "CExplosion.h"

#include "CMonster.h"
#include "CBat.h"
#include "CScareCrow.h"
#include "CCactus.h"
#include "CScorpGal.h"
#include "CSquidBaron.h"
CDebugLevel::CDebugLevel()
{


}

CDebugLevel::~CDebugLevel()
{
}


void CDebugLevel::init()
{
	/*LoadBackground(L"outskirts2_enlarge", L"texture\\background\\fixed\\enhanced\\outskirts2_enlarge.bmp", Vec2(6272.f, 1876.f));
	LoadPlatform(L"platform\\Outskirts2.platform");
	LoadWall(L"wall\\Outskirts2.wall");*/

	//LoadBackground(L"boss", L"texture\\background\\fixed\\enhanced\\boss.bmp", Vec2(1600.f, 900.f));
	LoadPlatform(L"platform\\debug.platform");
	LoadWall(L"wall\\debug.wall");
	LoadCeiling(L"ceiling\\debug.ceiling");

	// Player 생성
	CObj* pObj = new CPlayer;
	pObj->SetPos(Vec2(300.f, 100.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, LAYER::PLAYER);

	CMonster* cMonster = new CMonster;
	cMonster->GetMonInfo().m_iHP = 1000;
	cMonster->SetPos(Vec2(4500.f, 300.f));
	cMonster->SetScale(Vec2(100.f, 100.f));
	cMonster->GetCollider()->SetScale(Vec2(100.f, 100.f));
	AddObject(cMonster, LAYER::MONSTER);

	CObj* cDuck = new CForceDuck;
	cDuck->SetPos(Vec2(1632.f, 744.f));
	cDuck->GetCollider()->SetScale(Vec2(339.f,5.f));
	AddObject(cDuck, LAYER::PLATFORM);
	

	
	 //Monster 생성
	
	/*CMonster* pMonster = new CBat;
	pMonster->SetPos(Vec2(960.f, 700.f));
	pMonster->SetScale(Vec2(150.f, 150.f));
	pMonster->SetTarget((CPlayer*)pObj);
	AddObject(pMonster, LAYER::MONSTER);

	CMonster* pMonster2 = new CBat;
	pMonster2->SetPos(Vec2(960.f, 300.f));
	pMonster2->SetScale(Vec2(150.f, 150.f));
	pMonster2->SetTarget((CPlayer*)pObj);
	AddObject(pMonster2, LAYER::MONSTER);

	CMonster* pMonster3 = new CScareCrow;
	pMonster3->SetPos(Vec2(960.f, 300.f));
	pMonster3->SetScale(Vec2(150.f, 150.f));
	pMonster3->SetTarget((CPlayer*)pObj);
	AddObject(pMonster3, LAYER::MONSTER);*/

	 
	//CMonster* pMonster4 = new CScareCrow;
	//pMonster4->SetPos(Vec2(1500.f, 300.f));
	//pMonster4->SetScale(Vec2(150.f, 150.f));
	//pMonster4->SetTarget((CPlayer*)pObj);
	//AddObject(pMonster4, LAYER::MONSTER);

	/*CMonster* pMonster5 = new CCactus;
	pMonster5->SetPos(Vec2(1000.f, 300.f));
	pMonster5->SetScale(Vec2(150.f, 150.f));
	pMonster5->SetTarget((CPlayer*)pObj);
	AddObject(pMonster5, LAYER::MONSTER);*/

	/*CMonster* pMonster6 = new CScorpGal;
	pMonster6->SetPos(Vec2(1000.f, 300.f));
	pMonster6->SetScale(Vec2(150.f, 150.f));
	pMonster6->SetTarget((CPlayer*)pObj);
	AddObject(pMonster6, LAYER::MONSTER);*/


	/*CMonster* pBoss = new CSquidBaron;
	pBoss->SetPos(Vec2(1170.f, 800.f));
	pBoss->SetScale(Vec2(150.f, 150.f));
	pBoss->SetTarget((CPlayer*)pObj);
	AddObject(pBoss, LAYER::MONSTER);*/




	// Level 의 충돌 설정
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::MONSTER);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::MONSTER, LAYER::MONSTER);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::MONSTER_PROJECTILE);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER_PROJECTILE, LAYER::MONSTER);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER_PROJECTILE, LAYER::WALL);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER_PROJECTILE, LAYER::PLATFORM);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::PLATFORM);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::MONSTER, LAYER::PLATFORM);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::WALL);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::MONSTER, LAYER::WALL);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::CEILING);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::MONSTER, LAYER::CEILING);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::FIELD_OBJ);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER_PROJECTILE, LAYER::FIELD_OBJ);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLATFORM, LAYER::FIELD_OBJ);
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	CCamera::GetInst()->SetLook(vResolution / 2.f);
}

void CDebugLevel::tick()
{
	CLevel::tick();

	if (IsTap(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::START);
	}
	//if (IsTap(KEY::RBTN))
	//{
	//	CPlatform* pPlatform = new CPlatform;

	//	Vec2 vMousePos = MOUSE_POS;
	//	vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);

	//	Instantiate(pPlatform, vMousePos, LAYER::PLATFORM);
	//}

	if (IsTap(KEY::LBTN))
	{
		CCeiling* pWall = new CCeiling;

		Vec2 vMousePos = MOUSE_POS;
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);

		Instantiate(pWall, vMousePos, LAYER::CEILING);
	}

	/*if (IsTap(KEY::LBTN))
	{
		CObj* cExplosion = new CExplosion;

		Vec2 vMousePos = MOUSE_POS;
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);

		Instantiate(cExplosion, vMousePos, LAYER::DEATH_LEFTOVER);
	}*/
	/*if (IsTap(KEY::LBTN))
	{
		CObj* cDamage = new CDamage(5,false);

		Vec2 vMousePos = MOUSE_POS;
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);

		Instantiate(cDamage, vMousePos, LAYER::FIELD_OBJ);
	}*/

	/*if (IsTap(KEY::LBTN))
	{
		CForceDuck* pForceDuck = new CForceDuck;

		Vec2 vMousePos = MOUSE_POS;
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);

		Instantiate(pForceDuck, vMousePos, LAYER::PLATFORM);
	}*/
}

void CDebugLevel::Enter()
{
	
	//메뉴바 제거
	HWND hWnd = CEngine::GetInst()->GetMainWnd();
	SetMenu(hWnd, nullptr);
	//메뉴바가 없어졌으므로 메인 윈도우 크기를 늘린다.
	POINT ptResolution = CEngine::GetInst()->GetResolution();
	CEngine::GetInst()->ChangeWindowSize(ptResolution.x, ptResolution.y);
	CCamera::GetInst()->FadeIn(2.f);
	init();
}

void CDebugLevel::Exit()
{
	//CCamera::GetInst()->FadeOut(2.f);
	DeleteAllObject();
}
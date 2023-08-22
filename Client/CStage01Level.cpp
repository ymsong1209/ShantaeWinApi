#include "pch.h"
#include "CStage01Level.h"
#include "CEngine.h"
#include "CObj.h"
#include "CLevelMgr.h"

#include "CCamera.h"
#include "CResMgr.h"
#include "CCollisionMgr.h"
#include "CKeyMgr.h"

#include "CSound.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CForce.h"
#include "CPlatform.h"
#include "CCeiling.h"
#include "CWall.h"
#include "CForceDuck.h"
#include "CCameraBlock.h"
#include "CForceRespawn.h"

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
#include "CLevelChangeCollide.h"
CStage01Level::CStage01Level()
	: m_sbgm(nullptr)
{
	
	
}

CStage01Level::~CStage01Level()
{
}


void CStage01Level::init()
{

	LoadBackground(L"outskirts2_enlarge", L"texture\\background\\fixed\\enhanced\\outskirts2_enlarge.bmp", Vec2(6272.f, 1876.f));
	LoadPlatform(L"platform\\Outskirts2.platform");
	LoadWall(L"wall\\Outskirts2.wall");
	m_sbgm = CResMgr::GetInst()->LoadSound(L"Sequinisland", L"sound\\bgm\\Sequinisland.wav");
	m_sbgm->SetVolume(30);
	m_sbgm->PlayToBGM(true);
	

	// Player 생성
	CObj* pObj = new CPlayer;
	pObj->SetPos(Vec2(132.f, 1680.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, LAYER::PLAYER);
	//강제리스폰
	CObj* pRespawn = new CForceRespawn(Vec2(132.f, 1600.f), Vec2(6300.f, 100.f));
	pRespawn->SetPos(Vec2(3100.f,2000.f));
	AddObject(pRespawn, LAYER::PLATFORM);

	// Monster 생성
	CMonster* pMonster3 = new CScareCrow;
	pMonster3->GetMonInfo().m_bIsLeft = false;
	pMonster3->SetPos(Vec2(630.f, 800.f));
	pMonster3->SetScale(Vec2(150.f, 150.f));
	pMonster3->SetTarget((CPlayer*)pObj);
	AddObject(pMonster3, LAYER::MONSTER);


	CMonster* pMonster4 = new CScareCrow;
	pMonster4->SetPos(Vec2(1120.f, 1000.f));
	pMonster4->SetTarget((CPlayer*)pObj);
	AddObject(pMonster4, LAYER::MONSTER);

	CMonster* pMonster5 = new CScareCrow;
	pMonster5->SetPos(Vec2(1211.f, 1450.f));
	pMonster5->SetTarget((CPlayer*)pObj);
	AddObject(pMonster5, LAYER::MONSTER);

	//CMonster* pMonster5 = new CCactus;
	//pMonster5->SetPos(Vec2(930.f, 1470.f));
	//pMonster5->SetTarget((CPlayer*)pObj);
	//AddObject(pMonster5, LAYER::MONSTER);

	CMonster* pMonster6 = new CScorpGal;
	pMonster6->SetPos(Vec2(2000.f, 1200.f));
	pMonster6->SetScale(Vec2(150.f, 150.f));
	pMonster6->SetTarget((CPlayer*)pObj);
	AddObject(pMonster6, LAYER::MONSTER);

	CMonster* pMonster7 = new CScorpGal;
	pMonster7->SetPos(Vec2(3300.f, 940.f));
	pMonster7->SetScale(Vec2(150.f, 150.f));
	pMonster7->SetTarget((CPlayer*)pObj);
	AddObject(pMonster7, LAYER::MONSTER);

	CMonster* pMonster8 = new CScareCrow;
	pMonster8->SetPos(Vec2(5684.f, 1546.f));
	pMonster8->SetTarget((CPlayer*)pObj);
	AddObject(pMonster8, LAYER::MONSTER);

	//오브젝트 추가
	CObj* SquidHeart = new CSquidHeart;
	SquidHeart->SetPos(Vec2(4833.f,1070.f));
	SquidHeart->SetScale(Vec2(100.f, 100.f));
	AddObject(SquidHeart, LAYER::FIELD_OBJ);

	//LevelChange 추가
	CObj* levelChange = new CLevelChangeCollide(LEVEL_TYPE::TOWN, Vec2(200.f,500.f));
	levelChange->SetPos(Vec2(6110.f,1522.f));
	AddObject(levelChange, LAYER::FIELD_OBJ);

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

	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::FIELD_OBJ);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER_PROJECTILE, LAYER::FIELD_OBJ);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLATFORM, LAYER::FIELD_OBJ);
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	CCamera::GetInst()->SetLook(vResolution / 2.f);
}

void CStage01Level::tick()
{
	CLevel::tick();

	if (IsTap(KEY::_8)) {
		ChangeLevel(LEVEL_TYPE::START);
	}
	if (IsTap(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::NORMAL_STAGE_03);
	}

}

void CStage01Level::Enter()
{
	CCamera::GetInst()->FadeIn(1.f);
	//메뉴바 제거
	HWND hWnd = CEngine::GetInst()->GetMainWnd();
	SetMenu(hWnd, nullptr);
	//메뉴바가 없어졌으므로 메인 윈도우 크기를 늘린다.
	POINT ptResolution = CEngine::GetInst()->GetResolution();
	CEngine::GetInst()->ChangeWindowSize(ptResolution.x, ptResolution.y);
	
	init();
}

void CStage01Level::Exit()
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(GetLayer(LAYER::PLAYER)[0]);
	//CCamera::GetInst()->FadeOut(1.f);
	m_sbgm->Stop();
	DeleteAllObject();
}

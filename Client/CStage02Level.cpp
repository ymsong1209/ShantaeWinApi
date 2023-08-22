#include "pch.h"
#include "CStage02Level.h"
#include "CEngine.h"
#include "CObj.h"

#include "CCamera.h"
#include "CResMgr.h"
#include "CCollisionMgr.h"
#include "CKeyMgr.h"
#include "CCollider.h"


#include "CPlayer.h"
#include "CMonster.h"
#include "CForce.h"
#include "CPlatform.h"
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
#include "CSound.h"
#include "CLevelChangeCollide.h"

CStage02Level::CStage02Level()
{

}

CStage02Level::~CStage02Level()
{

}

void CStage02Level::init()
{
	
	LoadBackground(L"maze", L"texture\\background\\fixed\\enhanced\\maze.bmp", Vec2(3694.f, 1231.f));
	LoadPlatform(L"platform\\maze.platform");
	LoadWall(L"wall\\maze.wall");
	LoadCeiling(L"ceiling\\maze.ceiling");

	/*CSound* cbgm = CResMgr::GetInst()->LoadSound(L"SpittleMaze", L"sound\\bgm\\SpittleMaze.wav");
	cbgm->Play(true);*/

	// Player 생성
	CObj* pObj = new CPlayer;
	pObj->SetPos(Vec2(140.f, 970.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, LAYER::PLAYER);
	//강제리스폰
	CObj* pRespawn = new CForceRespawn(Vec2(140.f, 865.f), Vec2(4000.f, 100.f));
	pRespawn->SetPos(Vec2(1800.f, 1200.f));
	AddObject(pRespawn, LAYER::PLATFORM);
	//ForceDuck
	CObj* pForceDuck = new CForceDuck();
	pForceDuck->SetPos(Vec2(2751.f,849.f));
	pForceDuck->GetCollider()->SetScale(Vec2(169.f,5.f));
	AddObject(pForceDuck, LAYER::PLATFORM);

	// Monster 생성
	CMonster* pMonster1 = new CBat;
	pMonster1->GetMonInfo().m_bIsLeft = true;
	pMonster1->SetPos(Vec2(2062.f, 331.f));
	pMonster1->SetScale(Vec2(150.f, 150.f));
	pMonster1->SetTarget((CPlayer*)pObj);
	AddObject(pMonster1, LAYER::MONSTER);

	CMonster* pMonster2 = new CBat;
	pMonster2->GetMonInfo().m_bIsLeft = true;
	pMonster2->SetPos(Vec2(855.f, 315.f));
	pMonster2->SetScale(Vec2(150.f, 150.f));
	pMonster2->SetTarget((CPlayer*)pObj);
	AddObject(pMonster2, LAYER::MONSTER);

	//오브젝트 추가
	CObj* Pot = new CPot;
	Pot->SetPos(Vec2(2430.f, 814.f));
	Pot->SetScale(Vec2(100.f, 100.f));
	AddObject(Pot, LAYER::FIELD_OBJ);

	CObj* Pot2 = new CPot;
	Pot2->SetPos(Vec2(2499.f, 814.f));
	Pot2->SetScale(Vec2(100.f, 100.f));
	AddObject(Pot2, LAYER::FIELD_OBJ);

	//LevelChange 추가
	CObj* levelChange = new CLevelChangeCollide(LEVEL_TYPE::BOSS, Vec2(322.f, 251.f));
	levelChange->SetPos(Vec2(3469.f, 844.f));
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
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::CEILING);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::MONSTER, LAYER::CEILING);
	

	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::FIELD_OBJ);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER_PROJECTILE, LAYER::FIELD_OBJ);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLATFORM, LAYER::FIELD_OBJ);
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	CCamera::GetInst()->SetLook(vResolution / 2.f);
}

void CStage02Level::tick()
{
	CLevel::tick();
	if (IsTap(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::BOSS);
	}
}

void CStage02Level::Enter()
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

void CStage02Level::Exit()
{
	CSound* cbgm = CResMgr::GetInst()->LoadSound(L"SpittleMaze", L"sound\\bgm\\SpittleMaze.wav");
	cbgm->Stop(true);
	//CPlayer* pPlayer = dynamic_cast<CPlayer*>(GetLayer(LAYER::PLAYER)[0]);
	DeleteAllObject();
}



#include "pch.h"
#include "CStage03Level.h"
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
#include "CLevelChangeCollide.h"

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

CStage03Level::CStage03Level()
{

}

CStage03Level::~CStage03Level()
{

}

void CStage03Level::init()
{

	LoadBackground(L"maze2", L"texture\\background\\fixed\\enhanced\\maze2.bmp", Vec2(3240.f, 1140.f));
	LoadPlatform(L"platform\\maze2.platform");
	LoadWall(L"wall\\maze2.wall");
	LoadCeiling(L"ceiling\\maze2.ceiling");

	CSound* cbgm = CResMgr::GetInst()->LoadSound(L"SpittleMaze", L"sound\\bgm\\SpittleMaze.wav");
	cbgm->Play(true);

	// Player 생성
	CObj* pObj = new CPlayer;
	pObj->SetPos(Vec2(485.f, 123.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, LAYER::PLAYER);
	//강제리스폰
	CObj* pRespawn = new CForceRespawn(Vec2(485.f, 123.f), Vec2(4000.f, 100.f));
	pRespawn->SetPos(Vec2(1640.f, 1200.f));
	AddObject(pRespawn, LAYER::PLATFORM);
	

	// Monster 생성
	/*CMonster* pMonster1 = new CBat;
	pMonster1->GetMonInfo().m_bIsLeft = true;
	pMonster1->SetPos(Vec2(1302.f, 455.f));
	pMonster1->SetScale(Vec2(150.f, 150.f));
	pMonster1->SetTarget((CPlayer*)pObj);
	AddObject(pMonster1, LAYER::MONSTER);

	CMonster* pMonster2 = new CBat;
	pMonster2->GetMonInfo().m_bIsLeft = true;
	pMonster2->SetPos(Vec2(2600.f, 400.f));
	pMonster2->SetScale(Vec2(150.f, 150.f));
	pMonster2->SetTarget((CPlayer*)pObj);
	AddObject(pMonster2, LAYER::MONSTER);*/

	CMonster* pMonster3 = new CCactus;
	pMonster3->GetMonInfo().m_bIsLeft = true;
	pMonster3->SetPos(Vec2(1353.f, 837.f));
	pMonster3->SetScale(Vec2(150.f, 150.f));
	pMonster3->SetTarget((CPlayer*)pObj);
	AddObject(pMonster3, LAYER::MONSTER);

	CMonster* pMonster4 = new CCactus;
	pMonster4->GetMonInfo().m_bIsLeft = true;
	pMonster4->SetPos(Vec2(2532.f, 830.f));
	pMonster4->SetScale(Vec2(150.f, 150.f));
	pMonster4->SetTarget((CPlayer*)pObj);
	AddObject(pMonster4, LAYER::MONSTER);

	//오브젝트 추가
	CObj* Pot = new CPot;
	Pot->SetPos(Vec2(1654.f, 826.f));
	Pot->SetScale(Vec2(100.f, 100.f));
	AddObject(Pot, LAYER::FIELD_OBJ);

	CObj* Pot2 = new CPot;
	Pot2->SetPos(Vec2(1779.f, 826.f));
	Pot2->SetScale(Vec2(100.f, 100.f));
	AddObject(Pot2, LAYER::FIELD_OBJ);

	//LevelChange 추가
	CObj* levelChange = new CLevelChangeCollide(LEVEL_TYPE::NORMAL_STAGE_02, Vec2(227.f, 256.f));
	levelChange->SetPos(Vec2(3116.f, 781.f));
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

void CStage03Level::tick()
{
	CLevel::tick();
	if (IsTap(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::NORMAL_STAGE_02);
	}
}

void CStage03Level::Enter()
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

void CStage03Level::Exit()
{
	//CPlayer* pPlayer = dynamic_cast<CPlayer*>(GetLayer(LAYER::PLAYER)[0]);
	DeleteAllObject();
}
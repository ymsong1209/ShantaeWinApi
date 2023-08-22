#include "pch.h"
#include "CTownLevel.h"
#include "CEngine.h"
#include "CResMgr.h"
#include "CCollisionMgr.h"
#include "CKeyMgr.h"
#include "CPlayer.h"
#include "CSquidSmith.h"
#include "CTexture.h"
#include "CSound.h"
#include "CForceRespawn.h"
#include "CLevelChangeCollide.h"
#include "CLevelChangeInteract.h"

CTownLevel::CTownLevel()
{
}

CTownLevel::~CTownLevel()
{
}

void CTownLevel::init()
{
	LoadBackground(L"town", L"texture\\background\\fixed\\enhanced\\town.bmp", Vec2(4944.f, 1488.f));
	LoadPlatform(L"platform\\town.platform");
	LoadWall(L"wall\\town.wall");
	m_sbgm = CResMgr::GetInst()->LoadSound(L"Town", L"sound\\bgm\\ScuttleTown.wav");
	m_sbgm->SetVolume(40);
	m_sbgm->PlayToBGM(true);

	// Player 생성
	CObj* pObj = new CPlayer;
	if (((CPlayer*)pObj)->ReturnSpawnChange() == true) {
		pObj->SetPos(((CPlayer*)pObj)->ReturnSpawnPos());
		((CPlayer*)pObj)->SetSpawnChange(false);
		((CPlayer*)pObj)->SetAnim(PLAYER_ANIM::EXIT);
	}
	else {
		pObj->SetPos(Vec2(214.f, 1335.f));
	}
	
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, LAYER::PLAYER);
	//강제리스폰
	CObj* pRespawn = new CForceRespawn(Vec2(132.f, 1600.f), Vec2(6300.f, 100.f));
	pRespawn->SetPos(Vec2(3100.f, 2000.f));
	AddObject(pRespawn, LAYER::PLATFORM);

	//LevelChange
	CObj* pOnsen = new CLevelChangeInteract(LEVEL_TYPE::ONSEN, Vec2(71.f,123.f));
	pOnsen->SetPos(Vec2(1999.f, 1031.f));
	AddObject(pOnsen, LAYER::FIELD_OBJ);

	CObj* pSquidSmith = new CLevelChangeInteract(LEVEL_TYPE::SQUIDSMITH, Vec2(71.f, 123.f));
	pSquidSmith->SetPos(Vec2(1874.f, 1275.f));
	AddObject(pSquidSmith, LAYER::FIELD_OBJ);

	CObj* pLevel3 = new CLevelChangeCollide(LEVEL_TYPE::NORMAL_STAGE_03, Vec2(200.f, 500.f));
	pLevel3->SetPos(Vec2(4694.f, 1133.f));
	AddObject(pLevel3, LAYER::FIELD_OBJ);

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
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::NPC);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::FIELD_OBJ);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER_PROJECTILE, LAYER::FIELD_OBJ);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLATFORM, LAYER::FIELD_OBJ);
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	CCamera::GetInst()->SetLook(vResolution / 2.f);

}

void CTownLevel::tick()
{
	CLevel::tick();

	if (IsTap(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::START);
	}
}

void CTownLevel::Enter()
{
	CCamera::GetInst()->FadeIn(1.0f);
	//메뉴바 제거
	HWND hWnd = CEngine::GetInst()->GetMainWnd();
	SetMenu(hWnd, nullptr);
	//메뉴바가 없어졌으므로 메인 윈도우 크기를 늘린다.
	POINT ptResolution = CEngine::GetInst()->GetResolution();
	CEngine::GetInst()->ChangeWindowSize(ptResolution.x, ptResolution.y);
	
	init();
}

void CTownLevel::Exit()
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(GetLayer(LAYER::PLAYER)[0]);
	m_sbgm->Stop();
	
	DeleteAllObject();
}



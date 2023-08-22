#include "pch.h"
#include "CSquidSmithLevel.h"
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


CSquidSmithLevel::CSquidSmithLevel()
{
}

CSquidSmithLevel::~CSquidSmithLevel()
{
}

void CSquidSmithLevel::init()
{
	LoadBackground(L"SquidSmith", L"texture\\background\\fixed\\enhanced\\SquidSmith.bmp", Vec2(1600.f, 900.f));
	LoadPlatform(L"platform\\SquidSmith.platform");
	LoadWall(L"wall\\SquidSmith.wall");
	m_sbgm = CResMgr::GetInst()->LoadSound(L"Shop", L"sound\\bgm\\Shop.wav");
	m_sbgm->SetVolume(40);
	m_sbgm->PlayToBGM(true);

	// Player 생성
	CObj* pObj = new CPlayer;
	pObj->SetPos(Vec2(595.f, 550.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, LAYER::PLAYER);
	//강제리스폰
	CObj* pRespawn = new CForceRespawn(Vec2(132.f, 1600.f), Vec2(6300.f, 100.f));
	pRespawn->SetPos(Vec2(3100.f, 2000.f));
	AddObject(pRespawn, LAYER::PLATFORM);

	// Npc 생성
	CObj* SquidSmith = new CSquidSmith;
	SquidSmith->SetPos(Vec2(977.f, 559.f));
	//SquidSmith->SetScale(Vec2(150.f, 150.f));
	AddObject(SquidSmith, LAYER::NPC);

	//LevelChange
	CObj* pTown = new CLevelChangeCollide(LEVEL_TYPE::TOWN, Vec2(163.f, 311.f));
	pTown->SetPos(Vec2(77.f, 622.f));
	AddObject(pTown, LAYER::FIELD_OBJ);


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

void CSquidSmithLevel::tick()
{
	CLevel::tick();

	if (IsTap(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::START);
	}
}

void CSquidSmithLevel::Enter()
{
	CCamera::GetInst()->FadeIn(1.0f);
	//메뉴바 제거
	HWND hWnd = CEngine::GetInst()->GetMainWnd();
	SetMenu(hWnd, nullptr);
	//메뉴바가 없어졌으므로 메인 윈도우 크기를 늘린다.
	POINT ptResolution = CEngine::GetInst()->GetResolution();
	CEngine::GetInst()->ChangeWindowSize(ptResolution.x, ptResolution.y);
	CCamera::GetInst()->CamFix(true);
	init();
}

void CSquidSmithLevel::Exit()
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(GetLayer(LAYER::PLAYER)[0]);
	m_sbgm->Stop();
	CCamera::GetInst()->CamFix(false);
	DeleteAllObject();
}



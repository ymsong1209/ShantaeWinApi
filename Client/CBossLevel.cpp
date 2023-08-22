#include "pch.h"
#include "CBossLevel.h"
#include "CEngine.h"
#include "CObj.h"

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
#include "CSquidBaron.h"
CBossLevel::CBossLevel()
	: m_sbgm(nullptr)
{


}

CBossLevel::~CBossLevel()
{
}


void CBossLevel::init()
{

	LoadBackground(L"boss", L"texture\\background\\fixed\\enhanced\\boss.bmp", Vec2(1600.f, 920.f));
	LoadPlatform(L"platform\\boss.platform");
	LoadWall(L"wall\\boss.wall");
	m_sbgm = CResMgr::GetInst()->LoadSound(L"Boss", L"sound\\bgm\\Boss.wav");
	m_sbgm->PlayToBGM(true);

	// Player 생성
	CObj* pObj = new CPlayer;
	pObj->SetPos(Vec2(300.f, 100.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, LAYER::PLAYER);
	//강제리스폰
	CObj* pRespawn = new CForceRespawn(Vec2(132.f, 1600.f), Vec2(6300.f, 100.f));
	pRespawn->SetPos(Vec2(3100.f, 2000.f));
	AddObject(pRespawn, LAYER::PLATFORM);

	// Monster 생성
	CMonster* pBoss = new CSquidBaron;
	pBoss->SetPos(Vec2(1170.f, 800.f));
	pBoss->SetScale(Vec2(150.f, 150.f));
	pBoss->SetTarget((CPlayer*)pObj);
	AddObject(pBoss, LAYER::MONSTER);


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

void CBossLevel::tick()
{
	CLevel::tick();

	if (IsTap(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::START);
	}

}

void CBossLevel::Enter()
{
	CCamera::GetInst()->FadeIn(1.f);
	//메뉴바 제거
	HWND hWnd = CEngine::GetInst()->GetMainWnd();
	SetMenu(hWnd, nullptr);
	//메뉴바가 없어졌으므로 메인 윈도우 크기를 늘린다.
	POINT ptResolution = CEngine::GetInst()->GetResolution();
	CEngine::GetInst()->ChangeWindowSize(ptResolution.x, ptResolution.y);
	CCamera::GetInst()->CamFix(true);
	init();
}

void CBossLevel::Exit()
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(GetLayer(LAYER::PLAYER)[0]);
	m_sbgm->Stop();
	CCamera::GetInst()->CamFix(false);
	DeleteAllObject();
}
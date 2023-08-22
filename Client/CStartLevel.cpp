#include "pch.h"
#include "CEngine.h"
#include "CObj.h"

#include "CCamera.h"
#include "CResMgr.h"
#include "CCollisionMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CStartLevel.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CForce.h"
#include "CPlatform.h"
#include "CSound.h"
#include "CTitleSplash.h"

CStartLevel::CStartLevel()
	: m_sbgm(nullptr)
	, m_fTime(0)
	, m_btick(true)
	, m_bCamera(true)
{
}

CStartLevel::~CStartLevel()
{
}

void CStartLevel::init()
{
	
	

	
}
void CStartLevel::tick()
{
	if (m_bCamera) {
		CCamera::GetInst()->FadeIn(1.f);
		m_bCamera = false;
	}
	m_fTime += DT;
	if (m_fTime > 1.0 && m_btick) {
		CResMgr::GetInst()->LoadTexture(L"StartScreen", L"texture\\SplashScreens\\StartScreen.bmp");
		LoadBackground(L"StartScreen", L"texture\\SplashScreens\\StartSCreen", Vec2(1600.f, 900.f));
		m_sbgm = CResMgr::GetInst()->LoadSound(L"Title", L"sound\\bgm\\Title.wav");
		m_sbgm->SetVolume(35);
		m_sbgm->PlayToBGM(true);

		CSound* announce = CResMgr::GetInst()->LoadSound(L"TitleAnnounce", L"sound\\player\\vo_f_title_announce [1].wav");
		announce->SetVolume(20);
		announce->Play();
		m_btick = false;
		CObj* logo = new CTitleSplash();
		logo->SetPos(Vec2(793.f, 675.f));
		AddObject(logo, LAYER::DEFAULT);
	}

	CLevel::tick();

	if (IsTap(KEY::ENTER))
	{
		const vector<CObj*>& logo = GetLayer(LAYER::DEFAULT);
		((CTitleSplash*)logo[0])->transferlevel();
		//CCamera::GetInst()->FadeOut(1.f);
		//CCamera::GetInst()->FadeIn(1.f);	
		//CCamera::GetInst()->CameraShake(15.f, 600.f, 0.3f);
		//ChangeLevel(LEVEL_TYPE::NORMAL_STAGE_01);
	}
	else if (IsTap(KEY::_1)) {
		ChangeLevel(LEVEL_TYPE::EDITOR);
	}
	else if (IsTap(KEY::_2)) {
		ChangeLevel(LEVEL_TYPE::DEBUG);
	}
	//if (IsTap(KEY::LBTN))
//{
//	CForce* pForce = new CForce;
//	pForce->SetLifeTime(1.5f);
//	pForce->SetForceScale(200.f);
//	pForce->SetForceRadius(500.f);

//	Vec2 vMousePos = MOUSE_POS;
//	vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);
//	Instantiate(pForce, vMousePos, LAYER::FORCE);
//}

	
}

void CStartLevel::Enter()
{
	
	//CTimeMgr::GetInst()->init();
	HWND hWnd = CEngine::GetInst()->GetMainWnd();
	SetMenu(hWnd, nullptr);
	//메뉴바가 없어졌으므로 메인 윈도우 크기를 늘린다.
	POINT ptResolution = CEngine::GetInst()->GetResolution();
	CEngine::GetInst()->ChangeWindowSize(ptResolution.x, ptResolution.y);
	init();
}

void CStartLevel::Exit()
{
	//CCamera::GetInst()->FadeIn(1.f);
	DeleteAllObject();
	//메뉴바 제거
	HWND hWnd = CEngine::GetInst()->GetMainWnd();
	SetMenu(hWnd, nullptr);
	//메뉴바가 없어졌으므로 메인 윈도우 크기를 늘린다.
	POINT ptResolution = CEngine::GetInst()->GetResolution();
	CEngine::GetInst()->ChangeWindowSize(ptResolution.x, ptResolution.y);
	m_sbgm->Stop(true);
	m_btick = true;
	m_bCamera = true;
	m_fTime = 0.f;
}
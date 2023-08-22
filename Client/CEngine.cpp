#include "pch.h"
#include "CEngine.h"

#include "CPathMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CCollisionMgr.h"
#include "CEventMgr.h"
#include "CResMgr.h"
#include "CCamera.h"
#include "CUIMgr.h"
#include "CSoundMgr.h"
#include "CSound.h"

#include "CTexture.h"
#include "GameInstance.h"
CEngine::CEngine()
	: m_hMainWnd(nullptr)
	, m_hDC(nullptr)
	, m_ptResolution{}
	, m_arrPen{}
	, m_pMemTex(nullptr)
{

}

CEngine::~CEngine()
{
	ReleaseDC(m_hMainWnd, m_hDC);

	for (UINT i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}
}




void CEngine::init(HWND _hwnd, UINT _iWidth, UINT _iHeight)
{
	m_hMainWnd = _hwnd;
	m_ptResolution.x = _iWidth;
	m_ptResolution.y = _iHeight;

	// 윈도우 크기 설정
	RECT rt = { 0, 0, (LONG)_iWidth, (LONG)_iHeight };
	//adjustwindowrect : 적응형 윈도우 / 인자 : rt(입력과동시에출력__inout__),윈도우 스타일,메뉴의 유무
	//윈7 -> 윈 10으로 넘어오면서 윈도우 창에 테두리가 사라짐(ex: 옛날 계산기), 그 빈칸을 메꾸기 위해 사용됨
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(m_hMainWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);

	// HDC 초기화
	m_hDC = GetDC(m_hMainWnd);
	//자주 사용하는 Pen 및 Brush 생성해둠
	CreatePenBrush();



	// 백버퍼 용 비트맵 제작
	m_pMemTex = CResMgr::GetInst()->CreateTexture(L"BackBuffer", m_ptResolution.x, m_ptResolution.y);
	

	//Manager 초기화
	
	CPathMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CSoundMgr::GetInst()->init();
	CResMgr::GetInst()->init();
	CLevelMgr::GetInst()->init();
	
	
	
	/*CSound* pSound = CResMgr::GetInst()->LoadSound(L"BGM", L"sound\\BGM_Stage1.wav");


	pSound->SetPosition(99);
	pSound->PlayToBGM();*/
}



void CEngine::progress()
{
	//논리적인 연산
	tick();
	//화면 렌더링 갱신
	render();
	//다음 프레임에 적용될 이벤트 처리
	CEventMgr::GetInst()->tick();
}

void CEngine::tick()
{
	//FPS, Deltatime계산
	CTimeMgr::GetInst()->tick();
	//Key Event 체크
	CKeyMgr::GetInst()->tick();
	// Camera 
	CCamera::GetInst()->tick();
	//level을 업데이트
	CLevelMgr::GetInst()->tick();
	// 변경점 기반, 충돌체크
	CCollisionMgr::GetInst()->tick();
	// UI 이벤트 체크
	CUIMgr::GetInst()->tick();
	//
	GameInstance::GetInst()->tick();
}

void CEngine::render()
{
	/*HBRUSH hNullBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
	HBRUSH hOriginBrush = (HBRUSH)SelectObject(m_pMemTex->GetDC(), hNullBrush);*/
	
	//레벨 클리어, 테두리가 남기 때문에 일부러 펜 두께인 1픽셀만큼 늘린다.
	Rectangle(m_pMemTex->GetDC(), -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
	/*SelectObject(m_pMemTex->GetDC(), hOriginBrush);*/
	//레벨 렌더
	CLevelMgr::GetInst()->render(m_pMemTex->GetDC());
	// Camera Blind
	CCamera::GetInst()->render(m_pMemTex->GetDC());
	
	TCHAR str[100];
	Vec2 vMousePos = MOUSE_POS;
	vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);
	wsprintf(str, TEXT("X : %d, Y : %d"), (int)vMousePos.x, (int)vMousePos.y);
	TextOut(m_pMemTex->GetDC(), 10, 0, str, lstrlen(str));

	// m_pMemTex의 DC -> MainWindowBitMap으로 복사
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_pMemTex->GetDC(),0,0,SRCCOPY);
	//TimeMgr 렌더
	CTimeMgr::GetInst()->render();
	
	
}
void CEngine::CreatePenBrush()
{
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	m_arrPen[(UINT)PEN_TYPE::BLACK] = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
}

//메뉴가 추가되거나 사라질때 윈도우 해상도를 바꾸는 함수
void CEngine::ChangeWindowSize(UINT _iWidth, UINT _iHeight)
{
	m_ptResolution.x = _iWidth;
	m_ptResolution.y = _iHeight;

	RECT rt = { 0,0,m_ptResolution.x,m_ptResolution.y };
	HMENU hMenu = GetMenu(m_hMainWnd);

	if (nullptr != hMenu) {
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	}
	else {
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	}

	//백버퍼가 없으면 생성
	if (nullptr != m_pMemTex) {
		m_pMemTex = CResMgr::GetInst()->CreateTexture(L"BackBuffer", m_ptResolution.x, m_ptResolution.y);
	}
	//있으면 백버퍼도 변경된 해상도로 적용
	else {
		m_pMemTex->Resize(m_ptResolution.x, m_ptResolution.y);
	}

	SetWindowPos(m_hMainWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
}
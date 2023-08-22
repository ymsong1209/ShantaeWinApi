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

	// ������ ũ�� ����
	RECT rt = { 0, 0, (LONG)_iWidth, (LONG)_iHeight };
	//adjustwindowrect : ������ ������ / ���� : rt(�Է°����ÿ����__inout__),������ ��Ÿ��,�޴��� ����
	//��7 -> �� 10���� �Ѿ���鼭 ������ â�� �׵θ��� �����(ex: ���� ����), �� ��ĭ�� �޲ٱ� ���� ����
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(m_hMainWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);

	// HDC �ʱ�ȭ
	m_hDC = GetDC(m_hMainWnd);
	//���� ����ϴ� Pen �� Brush �����ص�
	CreatePenBrush();



	// ����� �� ��Ʈ�� ����
	m_pMemTex = CResMgr::GetInst()->CreateTexture(L"BackBuffer", m_ptResolution.x, m_ptResolution.y);
	

	//Manager �ʱ�ȭ
	
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
	//������ ����
	tick();
	//ȭ�� ������ ����
	render();
	//���� �����ӿ� ����� �̺�Ʈ ó��
	CEventMgr::GetInst()->tick();
}

void CEngine::tick()
{
	//FPS, Deltatime���
	CTimeMgr::GetInst()->tick();
	//Key Event üũ
	CKeyMgr::GetInst()->tick();
	// Camera 
	CCamera::GetInst()->tick();
	//level�� ������Ʈ
	CLevelMgr::GetInst()->tick();
	// ������ ���, �浹üũ
	CCollisionMgr::GetInst()->tick();
	// UI �̺�Ʈ üũ
	CUIMgr::GetInst()->tick();
	//
	GameInstance::GetInst()->tick();
}

void CEngine::render()
{
	/*HBRUSH hNullBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
	HBRUSH hOriginBrush = (HBRUSH)SelectObject(m_pMemTex->GetDC(), hNullBrush);*/
	
	//���� Ŭ����, �׵θ��� ���� ������ �Ϻη� �� �β��� 1�ȼ���ŭ �ø���.
	Rectangle(m_pMemTex->GetDC(), -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
	/*SelectObject(m_pMemTex->GetDC(), hOriginBrush);*/
	//���� ����
	CLevelMgr::GetInst()->render(m_pMemTex->GetDC());
	// Camera Blind
	CCamera::GetInst()->render(m_pMemTex->GetDC());
	
	TCHAR str[100];
	Vec2 vMousePos = MOUSE_POS;
	vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);
	wsprintf(str, TEXT("X : %d, Y : %d"), (int)vMousePos.x, (int)vMousePos.y);
	TextOut(m_pMemTex->GetDC(), 10, 0, str, lstrlen(str));

	// m_pMemTex�� DC -> MainWindowBitMap���� ����
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_pMemTex->GetDC(),0,0,SRCCOPY);
	//TimeMgr ����
	CTimeMgr::GetInst()->render();
	
	
}
void CEngine::CreatePenBrush()
{
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	m_arrPen[(UINT)PEN_TYPE::BLACK] = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
}

//�޴��� �߰��ǰų� ������� ������ �ػ󵵸� �ٲٴ� �Լ�
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

	//����۰� ������ ����
	if (nullptr != m_pMemTex) {
		m_pMemTex = CResMgr::GetInst()->CreateTexture(L"BackBuffer", m_ptResolution.x, m_ptResolution.y);
	}
	//������ ����۵� ����� �ػ󵵷� ����
	else {
		m_pMemTex->Resize(m_ptResolution.x, m_ptResolution.y);
	}

	SetWindowPos(m_hMainWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
}
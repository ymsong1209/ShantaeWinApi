#include "pch.h"
#include "CKeyMgr.h"
#include "CEngine.h"

int g_arrVK[(UINT)KEY::END]
=
{
	 VK_UP,
	 VK_DOWN,
	 VK_LEFT,
	 VK_RIGHT,
	 VK_SPACE,
	 VK_RETURN,
	 VK_ESCAPE,
	 VK_LMENU,
	 VK_LCONTROL,
	 VK_LSHIFT,
	 VK_TAB,
	 VK_LBUTTON,
	 VK_RBUTTON,

	 'Q',
	 'W',
	 'E',
	 'R',
	 'A',
	 'S',
	 'D',
	 'F',
	 'G',
	 'H',
	 'J',
	 'K',
	 'L',
	 'Z',
	 'X',
	 'C',

	 '0',
	 '1',
	 '2',
	 '3',
	 '4',
	 '5',
	 '6',
	 '7',
	 '8',
	 '9',

	 VK_ADD,
	 VK_SUBTRACT,
	 VK_DELETE
};
CKeyMgr::CKeyMgr()
{

}

CKeyMgr::~CKeyMgr()
{

}
void CKeyMgr::init()
{
	//키값을 일단 안누른 상태로 초기화해서 벡터에 집어넣음
	for (int i = 0; i < (int)KEY::END; ++i)
	{		
		m_vecKey.push_back(tKeyInfo{ (KEY)i  , KEY_STATE::NONE });
	}
}

void CKeyMgr::tick()
{
	//getfocus: 포커싱중인 윈도우의 핸들값을 알려줌
	if (GetFocus())
	{
		
		for (size_t i = 0; i < m_vecKey.size(); ++i)
		{
			//m_vecKey의 키값 위치는 g_arrVK 키값의 위치랑 동일
			if (GetAsyncKeyState(g_arrVK[(UINT)m_vecKey[i].key]) & 0x8000)
			{
				// 이전에는 눌리지 않았다.
				if (false == m_vecKey[i].bPrev)
				{
					m_vecKey[i].state = KEY_STATE::TAP;
					m_vecKey[i].bPrev = true;
				}
				else
				{
					// 지금도 눌려있고, 이전 프레임에서도 눌려있었다.
					m_vecKey[i].state = KEY_STATE::PRESSED;
				}
			}
			else
			{
				// 이전에도 안누려있었고 지금도 눌려있지 않다.
				if (false == m_vecKey[i].bPrev)
				{
					m_vecKey[i].state = KEY_STATE::NONE;
				}
				else
				{
					//이전엔 눌렸는데 지금 버튼을 땠다.
					m_vecKey[i].state = KEY_STATE::RELEASE;
					m_vecKey[i].bPrev = false;
				}
			}
		}
		// Mouse 위치 갱신
		POINT ptMousePos = {};
		//현재 모니터 해상도 기준 마우스 포지션
		GetCursorPos(&ptMousePos);
		// 모니터 해상도 -> 현재 프로그램 창 해상도
		ScreenToClient(CEngine::GetInst()->GetMainWnd(), &ptMousePos);
		m_vMousePos = ptMousePos;
	}

	// Window 가 focus 상태가 아니다
	else
	{
		//모든 key의 상태를 none으로 되돌림
		for (size_t i = 0; i < m_vecKey.size(); ++i)
		{
			if (KEY_STATE::TAP == m_vecKey[i].state || KEY_STATE::PRESSED == m_vecKey[i].state)
			{
				m_vecKey[i].state = KEY_STATE::RELEASE;
			}

			else if (KEY_STATE::RELEASE == m_vecKey[i].state)
			{
				m_vecKey[i].state = KEY_STATE::NONE;
			}
		}
	}
}

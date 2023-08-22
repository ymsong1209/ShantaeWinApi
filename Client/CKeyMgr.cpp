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
	//Ű���� �ϴ� �ȴ��� ���·� �ʱ�ȭ�ؼ� ���Ϳ� �������
	for (int i = 0; i < (int)KEY::END; ++i)
	{		
		m_vecKey.push_back(tKeyInfo{ (KEY)i  , KEY_STATE::NONE });
	}
}

void CKeyMgr::tick()
{
	//getfocus: ��Ŀ������ �������� �ڵ鰪�� �˷���
	if (GetFocus())
	{
		
		for (size_t i = 0; i < m_vecKey.size(); ++i)
		{
			//m_vecKey�� Ű�� ��ġ�� g_arrVK Ű���� ��ġ�� ����
			if (GetAsyncKeyState(g_arrVK[(UINT)m_vecKey[i].key]) & 0x8000)
			{
				// �������� ������ �ʾҴ�.
				if (false == m_vecKey[i].bPrev)
				{
					m_vecKey[i].state = KEY_STATE::TAP;
					m_vecKey[i].bPrev = true;
				}
				else
				{
					// ���ݵ� �����ְ�, ���� �����ӿ����� �����־���.
					m_vecKey[i].state = KEY_STATE::PRESSED;
				}
			}
			else
			{
				// �������� �ȴ����־��� ���ݵ� �������� �ʴ�.
				if (false == m_vecKey[i].bPrev)
				{
					m_vecKey[i].state = KEY_STATE::NONE;
				}
				else
				{
					//������ ���ȴµ� ���� ��ư�� ����.
					m_vecKey[i].state = KEY_STATE::RELEASE;
					m_vecKey[i].bPrev = false;
				}
			}
		}
		// Mouse ��ġ ����
		POINT ptMousePos = {};
		//���� ����� �ػ� ���� ���콺 ������
		GetCursorPos(&ptMousePos);
		// ����� �ػ� -> ���� ���α׷� â �ػ�
		ScreenToClient(CEngine::GetInst()->GetMainWnd(), &ptMousePos);
		m_vMousePos = ptMousePos;
	}

	// Window �� focus ���°� �ƴϴ�
	else
	{
		//��� key�� ���¸� none���� �ǵ���
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

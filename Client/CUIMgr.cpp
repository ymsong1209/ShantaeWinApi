#include "pch.h"
#include "CUIMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CUI.h"

#include "CKeyMgr.h"


CUIMgr::CUIMgr()
	: m_pFocusedUI(nullptr)
	, m_pPriorityUI(nullptr)
{

}

CUIMgr::~CUIMgr()
{

}

void CUIMgr::tick()
{
	bool bLbtnPressed = IsTap(KEY::LBTN);
	bool bLbtnReleased = IsRelease(KEY::LBTN);


	// ���� ���� ����
	// UI Layer ��������
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	const vector<CObj*>& vecUI = pCurLevel->GetLayer(LAYER::UI);

	for (int i = (int)vecUI.size() - 1; 0 <= i; --i)
	{
		m_pPriorityUI = GetPriorityUI((CUI*)vecUI[i]);

		if (nullptr == m_pPriorityUI)
			continue;

		// ���콺�� �̺�Ʈ ȣ��
		m_pPriorityUI->MouseOn();

		// �̹��� LBTN �� ���ȴ�
		if (bLbtnPressed)
		{
			// LbtnDown �̺�Ʈ ȣ��
			m_pPriorityUI->MouseLbtnDown();

			// �θ�UI �� FocusedUI �� ����
			m_pFocusedUI = (CUI*)vecUI[i];
			pCurLevel->SetFocusedUI(m_pFocusedUI);
			break;
		}

		// �̹��� LBTN �� ������
		else if (bLbtnReleased)
		{
			// ������ �������� �ִ�.
			if (m_pPriorityUI->m_bLbtnDown)
			{
				// Ŭ�� �̺�Ʈ ȣ��
				m_pPriorityUI->MouseLbtnClicked();
				m_pPriorityUI->m_bLbtnDown = false;
			}
		}
	}
}
CUI* CUIMgr::GetPriorityUI(CUI* _pParentUI)
{
	bool bLbtnReleased = IsRelease(KEY::LBTN);

	CUI* pPriorityUI = nullptr;

	static list<CUI*> queue;
	queue.clear();
	queue.push_back(_pParentUI);


	while (!queue.empty())
	{
		CUI* pUI = queue.front();
		queue.pop_front();

		const vector<CUI*>& vecChild = pUI->GetChildUI();
		for (size_t i = 0; i < vecChild.size(); ++i)
		{
			queue.push_back(vecChild[i]);
		}

		// UI �� ���� Ȯ��
		if (pUI->IsMouseOn())
		{
			// �켱���� UI �� ����������, �� ���� �켱������ ���� �ٸ� UI �� ���� ���.
			// ���� UI �� LBTNDown ���¸� �����Ѵ�.
			if (bLbtnReleased && nullptr != pPriorityUI && pPriorityUI->IsLbtnDown())
			{
				pPriorityUI->m_bLbtnDown = false;
			}

			// �켱���� UI �� ����
			pPriorityUI = pUI;
		}

		// �켱���� UI �� ���� �ȵ� UI �� ���콺 ���������� �߻��ϸ� LBtnDown �� �����س��´�.
		else if (bLbtnReleased)
		{
			pUI->m_bLbtnDown = false;
		}
	}

	return pPriorityUI;
}

#include "pch.h"
#include "CButton.h"

#include "CLevelMgr.h"
#include "CEditorLevel.h"

#include "CTexture.h"

CButton::CButton()
	: m_pFunc(nullptr)
	, m_pPressedTex(nullptr)
	, m_pHighlightTex(nullptr)
	, m_pInst(nullptr)
	, m_pDelegateFunc(nullptr)
{
}

CButton::~CButton()
{
}

void CButton::MouseLbtnClicked()
{
	// button에 설정되어있는 함수를 실행
	if (nullptr != m_pFunc)
		m_pFunc();
	// button에 설정되어있는 delegate함수를 실행
	if (m_pInst && m_pDelegateFunc)
	{
		(m_pInst->*m_pDelegateFunc)();
	}
}

void CButton::render(HDC _dc)
{
	CTexture* pTargetTex = GetIdleTex();

	if (IsLbtnDown())
	{
		if (m_pPressedTex)
			pTargetTex = m_pPressedTex;
	}
	else if (IsMouseOn())
	{
		if (m_pHighlightTex)
			pTargetTex = m_pHighlightTex;
	}

	if (!pTargetTex)
	{
		CUI::render(_dc);
		return;
	}

	Vec2 vPos = GetFinalPos();
	BitBlt(_dc, vPos.x, vPos.y, pTargetTex->Width(), pTargetTex->Height(), pTargetTex->GetDC(), 0, 0, SRCCOPY);

	render_childUI(_dc);
}
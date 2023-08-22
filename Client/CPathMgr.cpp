#include "pch.h"
#include "CEngine.h"
#include "CPathMgr.h"

CPathMgr::CPathMgr()
	:m_szContentPath{}
{

}
CPathMgr::~CPathMgr()
{

}

void CPathMgr::init()
{
	GetCurrentDirectory(256, m_szContentPath);
	//상위폴더로 감
	int iLen = (int)wcslen(m_szContentPath);
	// \\으로 구분되어있기 때문에 맨 마지막 꼬리잘라내기
	for (int i = iLen-1; iLen >= 0; --i) {
		if (L'\\' == m_szContentPath[i]) {
			m_szContentPath[i] = 0;
			break;
		}
	}
	// +bin\\content
	wcscat_s(m_szContentPath,L"\\bin\\content\\");
	
	
	render();
}


void CPathMgr::render()
{
	
	SetWindowText(CEngine::GetInst()->GetMainWnd(), m_szContentPath);
}

#include "pch.h"
#include "CTimeMgr.h"
#include "CEngine.h"

CTimeMgr::CTimeMgr()
	: m_llPrevCount{}
	, m_llCurCount{}
	, m_llFrequency{}
	, m_iCallCount(0)
	, m_fDeltaTime(0.f)
	, m_fTime(0.f)
{

}
CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::init()
{
	//1초당 진동수를 반환
	QueryPerformanceFrequency(&m_llFrequency);
	//일정 시간안에 몇번 진동하였는가를 나타냄
	QueryPerformanceCounter(&m_llCurCount);
	QueryPerformanceCounter(&m_llPrevCount);
	
}

void CTimeMgr::tick()
{
	QueryPerformanceCounter(&m_llCurCount);

	// tick 간격 시간
	//(현재까지 얼마 진동했나 - 이전에 얼마 진동했나)/(1초당 진동수)
	m_fDeltaTime = (float)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (float)m_llFrequency.QuadPart;

	// 누적 시간
	m_fTime += m_fDeltaTime;

	// tick 함수 호출 횟수
	++m_iCallCount;

	

	// 이전 카운트 값을 현재 카운트로 갱신
	m_llPrevCount = m_llCurCount;
}

void CTimeMgr::render()
{
	// 1초에 한번
	if (1.f <= m_fTime)
	{
		

		wchar_t szBuff[256] = {};
		swprintf_s(szBuff, L"FPS : %d, DT : %f", m_iCallCount, m_fDeltaTime);
		SetWindowText(CEngine::GetInst()->GetMainWnd(), szBuff);

		m_fTime = 0.f;
		m_iCallCount = 0;
	}
}
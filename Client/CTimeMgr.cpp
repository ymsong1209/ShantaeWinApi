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
	//1�ʴ� �������� ��ȯ
	QueryPerformanceFrequency(&m_llFrequency);
	//���� �ð��ȿ� ��� �����Ͽ��°��� ��Ÿ��
	QueryPerformanceCounter(&m_llCurCount);
	QueryPerformanceCounter(&m_llPrevCount);
	
}

void CTimeMgr::tick()
{
	QueryPerformanceCounter(&m_llCurCount);

	// tick ���� �ð�
	//(������� �� �����߳� - ������ �� �����߳�)/(1�ʴ� ������)
	m_fDeltaTime = (float)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (float)m_llFrequency.QuadPart;

	// ���� �ð�
	m_fTime += m_fDeltaTime;

	// tick �Լ� ȣ�� Ƚ��
	++m_iCallCount;

	

	// ���� ī��Ʈ ���� ���� ī��Ʈ�� ����
	m_llPrevCount = m_llCurCount;
}

void CTimeMgr::render()
{
	// 1�ʿ� �ѹ�
	if (1.f <= m_fTime)
	{
		

		wchar_t szBuff[256] = {};
		swprintf_s(szBuff, L"FPS : %d, DT : %f", m_iCallCount, m_fDeltaTime);
		SetWindowText(CEngine::GetInst()->GetMainWnd(), szBuff);

		m_fTime = 0.f;
		m_iCallCount = 0;
	}
}
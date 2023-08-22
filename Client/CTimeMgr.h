#pragma once
class CTimeMgr
{

SINGLE(CTimeMgr);
private:
	LARGE_INTEGER m_llPrevCount;
	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llFrequency;
	UINT			m_iCallCount;
	float			m_fDeltaTime;
	float			m_fTime;
public:
	void init();
	void tick();
	void render();
	float ReturnCurCount() { return float(m_llCurCount.QuadPart); }
	UINT  ReturnCallCount() { return m_iCallCount; }
	float ReturnDeltaTime() { return m_fDeltaTime; }
	
public:
	float GetDeltaTime() { return m_fDeltaTime; }

};


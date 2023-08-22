#pragma once

class CTexture;
class CEngine
{
SINGLE(CEngine);
private:
	// static CEngine* m_pInst;
	HWND		m_hMainWnd;
	//hdc: device context
	HDC			m_hDC;
	//해상도
	POINT		m_ptResolution;
	HPEN		m_arrPen[(UINT)PEN_TYPE::END];

	CTexture*	 m_pMemTex;

public:

	HWND GetMainWnd() { return m_hMainWnd; }
	HDC	 GetMainDC() { return m_hDC; }
	HPEN GetPen(PEN_TYPE _type) { return m_arrPen[(UINT)_type]; }
	POINT GetResolution() { return m_ptResolution; }
	void ChangeWindowSize(UINT _iWidth, UINT _iHeight);
	

public:
	//void init:해상도 설정->가로,세로픽셀갯수
	void init(HWND _hwnd, UINT _iWidth, UINT _iHeight);
	void progress();

private:
	void tick();	// 갱신
	void render();	// 렌더링
	void CreatePenBrush();

};

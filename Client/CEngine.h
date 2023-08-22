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
	//�ػ�
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
	//void init:�ػ� ����->����,�����ȼ�����
	void init(HWND _hwnd, UINT _iWidth, UINT _iHeight);
	void progress();

private:
	void tick();	// ����
	void render();	// ������
	void CreatePenBrush();

};

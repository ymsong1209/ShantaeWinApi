#pragma once
#include "CRes.h"

#include "CSoundMgr.h"

class CSound :
	public CRes
{
private:
	LPDIRECTSOUNDBUFFER		m_pSoundBuffer;
	DSBUFFERDESC			m_tBuffInfo;
	int						m_iVolume;

private:
	virtual int Load(const wstring& _strFilePath);

public:
	// �Ϲ� ���
	void Play(bool _bLoop = false);

	// BGM ���� ���
	void PlayToBGM(bool _bLoop = false);

	void Stop(bool _bReset = false);

	// ���� ���� (0 ~ 100)
	void SetVolume(float _fVolume);

	// ���� ���� (0~100)
	int GetVolume() { return m_iVolume; }

	// �������� ��ġ ���� (0 ~ 100)
	void SetPosition(float _fPosition); // 0 ~ 100 ����

private:
	bool LoadWaveSound(const wstring& _strPath);
	int GetDecibel(float _fVolume);



public:
	CSound();
	virtual ~CSound();
};
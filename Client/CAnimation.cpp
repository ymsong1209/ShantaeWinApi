#include "pch.h"
#include "CAnimation.h"

#include "CObj.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CCamera.h"
#include "CTimeMgr.h"
#include "CPathMgr.h"
#include "CResMgr.h"

CAnimation::CAnimation(CAnimator* _pAnimator)
	: m_pAnimator(_pAnimator)
	//, m_vecFrm{}
	, m_pAtlas(nullptr)
	, m_iCurFrm(0)
	, m_fAccTime(0.f)
	, m_bFinish(false)
	//, m_bPlayerPlay(false)
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::init(const wstring& _strName, CTexture* _pAtlas, Vec2 _vLeftTop, Vec2 _vSize, Vec2 _vOffset, Vec2 _vSpace, int _iMaxFrmCount, int _iline, int _iFrmPerLine, float _fDuration)
{
	//assert(_iMaxFrmCount > _iFrmPerLine);
	SetName(_strName);	// Animation �̸�
	m_pAtlas = _pAtlas;	// Animation �� ��Ʋ�� �̹���
	int CurLine = 0;
	for (CurLine; CurLine < _iMaxFrmCount/_iFrmPerLine; ++CurLine)
	{	
		for (int CurFrm = 0; CurFrm < _iFrmPerLine; ++CurFrm) {
			//vLeftTop,vSize,vOffset,fDuration	
			tAnimFrm frm = {};

			frm.vLeftTop = Vec2(_vLeftTop.x + (float)CurFrm * _vSize.x + (float)CurFrm * _vSpace.x, _vLeftTop.y+ (float)CurLine * (_vSize.y + _vSpace.y));
			frm.vSize = _vSize;
			frm.vOffset = _vOffset;
			frm.vSpace = _vSpace;
			frm.fDuration = _fDuration;
			

			m_vecFrm.push_back(frm);
			
		}
		
	}
	for (int CurFrm = 0; CurFrm < _iMaxFrmCount%_iFrmPerLine; ++CurFrm) {
		//vLeftTop,vSize,vOffset,fDuration	
		tAnimFrm frm = {};

		frm.vLeftTop = Vec2(_vLeftTop.x + (float)CurFrm * _vSize.x + (float)CurFrm * _vSpace.x, _vLeftTop.y + (float)CurLine * _vSize.y+ (float)CurLine * _vSpace.y);
		frm.vSize = _vSize;
		frm.vOffset = _vOffset;
		frm.vSpace = _vSpace;
		frm.fDuration = _fDuration;
		

		m_vecFrm.push_back(frm);

	}
}

void CAnimation::tick()
{
	if (m_bFinish)
		return;

	m_fAccTime += DT;

	if (m_vecFrm[m_iCurFrm].fDuration < m_fAccTime)
	{
		++m_iCurFrm;
		m_fAccTime = 0.f;
		//������ �����ӿ��� ���߱�
		if (m_vecFrm.size() <= m_iCurFrm)
		{
			m_iCurFrm = (int)m_vecFrm.size() - 1;
			m_bFinish = true;
		}
	}
}

void CAnimation::render(HDC _dc, bool _mAlphablend, bool _mFloorPlay)
{
	CObj* pOwnerObj = m_pAnimator->GetOwner();
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(pOwnerObj->GetPos());

	tAnimFrm frm = m_vecFrm[m_iCurFrm];

	// �߽���ǥ�� �ִϸ��̼��� �ٴ��̴�
	if (_mFloorPlay) {
		if (_mAlphablend) {
			static float fRatio = 0.f;
			static float Dir = 1.f;
			fRatio += DT * Dir * 8.f;

			if (1.f < fRatio)
			{
				fRatio = 1.f;
				Dir = -1.f;
			}
			else if (fRatio < 0.f)
			{
				fRatio = 0.f;
				Dir = 1;
			}

			BLENDFUNCTION tBlend = {};

			tBlend.AlphaFormat = AC_SRC_ALPHA;
			tBlend.BlendFlags = 0;
			tBlend.BlendOp = AC_SRC_OVER;
			tBlend.SourceConstantAlpha = (int)(255.f * fRatio);

			AlphaBlend(_dc
				, int(vPos.x - frm.vSize.x / 2.f + frm.vOffset.x)
				, int(vPos.y - frm.vSize.y + frm.vOffset.y)
				, int(frm.vSize.x)
				, int(frm.vSize.y)
				, m_pAtlas->GetDC()
				, int(frm.vLeftTop.x)
				, int(frm.vLeftTop.y)
				, int(frm.vSize.x)
				, int(frm.vSize.y)
				, tBlend);
		}
		else {
			TransparentBlt(_dc
				, int(vPos.x - frm.vSize.x / 2.f + frm.vOffset.x)
				, int(vPos.y - frm.vSize.y + frm.vOffset.y)
				, int(frm.vSize.x)
				, int(frm.vSize.y)
				, m_pAtlas->GetDC()
				, int(frm.vLeftTop.x)
				, int(frm.vLeftTop.y)
				, int(frm.vSize.x)
				, int(frm.vSize.y)
				, RGB(0, 248, 0));
		}
	}
	// �߽���ǥ 0.0
	else {
		if (_mAlphablend) {
			static float fRatio = 0.f;
			static float Dir = 1.f;
			fRatio += DT * Dir * 8.f;

			if (1.f < fRatio)
			{
				fRatio = 1.f;
				Dir = -1.f;
			}
			else if (fRatio < 0.f)
			{
				fRatio = 0.f;
				Dir = 1;
			}

			BLENDFUNCTION tBlend = {};

			tBlend.AlphaFormat = AC_SRC_ALPHA;
			tBlend.BlendFlags = 0;
			tBlend.BlendOp = AC_SRC_OVER;
			tBlend.SourceConstantAlpha = (int)(255.f * fRatio);

			AlphaBlend(_dc
				, int(vPos.x - frm.vSize.x / 2.f + frm.vOffset.x)
				, int(vPos.y - frm.vSize.y / 2.f + frm.vOffset.y)
				, int(frm.vSize.x)
				, int(frm.vSize.y)
				, m_pAtlas->GetDC()
				, int(frm.vLeftTop.x)
				, int(frm.vLeftTop.y)
				, int(frm.vSize.x)
				, int(frm.vSize.y)
				, tBlend);
		}
		else {
			TransparentBlt(_dc
				, int(vPos.x - frm.vSize.x / 2.f + frm.vOffset.x)
				, int(vPos.y - frm.vSize.y / 2.f + frm.vOffset.y)
				, int(frm.vSize.x)
				, int(frm.vSize.y)
				, m_pAtlas->GetDC()
				, int(frm.vLeftTop.x)
				, int(frm.vLeftTop.y)
				, int(frm.vSize.x)
				, int(frm.vSize.y)
				, RGB(0, 248, 0));
		}
	}
	
}

void CAnimation::Save(const wstring& _strRelativePath)
{
	wstring strFilepath = CPathMgr::GetInst()->GetContentPath();
	strFilepath += _strRelativePath;

	// ���� �����
	FILE* pFile = nullptr;
	errno_t iErrNum = _wfopen_s(&pFile, strFilepath.c_str(), L"wb");

	if (nullptr == pFile)
	{
		wchar_t szStr[256] = {};
		wsprintf(szStr, L"Animation Save ����, Error Number : %d", iErrNum);
		MessageBox(nullptr, szStr, L"���� ���� ����", MB_OK);
		return;
	}

	// Animation �̸� ����
	fwprintf_s(pFile, L"\n");

	fwprintf_s(pFile, L"[ANIMATION_NAME]\n");
	fwprintf_s(pFile, GetName().c_str());
	fwprintf_s(pFile, L"\n\n");

	// ��Ʋ�� �ؽ��� Ű�� ����	
	fwprintf_s(pFile, L"[ATLAS_KEY]\n");
	fwprintf_s(pFile, m_pAtlas->GetKey().c_str());
	fwprintf_s(pFile, L"\n\n");

	fwprintf_s(pFile, L"[ATLAS_PATH]\n");
	fwprintf_s(pFile, m_pAtlas->GetRelativePath().c_str());
	fwprintf_s(pFile, L"\n\n");


	// ������ ���� ����
	wchar_t szNum[50] = {};

	fwprintf_s(pFile, L"[FRAME_COUNT]\n");

	size_t iFrmCount = m_vecFrm.size();
	_itow_s((int)iFrmCount, szNum, 50, 10);

	fwprintf_s(pFile, szNum);
	fwprintf_s(pFile, L"\n\n");

	for (size_t i = 0; i < iFrmCount; ++i)
	{
		fwprintf_s(pFile, L"[%zd_FRAME]\n", i);

		// LEFT_TOP
		fwprintf_s(pFile, L"[LEFT_TOP]\n");
		fwprintf_s(pFile, L"%.1f %.1f\n", m_vecFrm[i].vLeftTop.x, m_vecFrm[i].vLeftTop.y);

		// SIZE
		fwprintf_s(pFile, L"[SIZE]\n");
		fwprintf_s(pFile, L"%.1f %.1f\n", m_vecFrm[i].vSize.x, m_vecFrm[i].vSize.y);

		// OFFSET
		fwprintf_s(pFile, L"[OFFSET]\n");
		fwprintf_s(pFile, L"%.1f %.1f\n", m_vecFrm[i].vOffset.x, m_vecFrm[i].vOffset.y);

		// DURATION
		fwprintf_s(pFile, L"[DURATION]\n");
		fwprintf_s(pFile, L"%.2f\n", m_vecFrm[i].fDuration);

		// SPACE
		fwprintf_s(pFile, L"[SPACE]\n");
		fwprintf_s(pFile, L"%.1f %.1f\n", m_vecFrm[i].vSpace.x, m_vecFrm[i].vSpace.y);

		fwprintf_s(pFile, L"\n");
	}

	fclose(pFile);
}

void CAnimation::Load(const wstring& _strRelativePath)
{
	wstring strFilepath = CPathMgr::GetInst()->GetContentPath();
	strFilepath += _strRelativePath;

	// ���� �����
	FILE* pFile = nullptr;
	errno_t iErrNum = _wfopen_s(&pFile, strFilepath.c_str(), L"rb");

	if (nullptr == pFile)
	{
		wchar_t szStr[256] = {};
		wsprintf(szStr, L"Animation Save ����, Error Number : %d", iErrNum);
		MessageBox(nullptr, szStr, L"���� ���� ����", MB_OK);
		return;
	}

	size_t iFrameCount = 0;
	wstring strAtlasKey;
	wstring strAltasRelativePath;

	while (true)
	{
		wchar_t szBuffer[256] = {};
		fwscanf_s(pFile, L"%s", szBuffer, 256);

		if (!wcscmp(szBuffer, L"[ANIMATION_NAME]"))
		{
			fwscanf_s(pFile, L"%s", szBuffer, 256);
			SetName(szBuffer);
		}

		else if (!wcscmp(szBuffer, L"[ATLAS_KEY]"))
		{
			fwscanf_s(pFile, L"%s", szBuffer, 256);
			strAtlasKey = szBuffer;
		}

		else if (!wcscmp(szBuffer, L"[ATLAS_PATH]"))
		{
			fwscanf_s(pFile, L"%s", szBuffer, 256);
			strAltasRelativePath = szBuffer;
		}

		else if (!wcscmp(szBuffer, L"[FRAME_COUNT]"))
		{
			fwscanf_s(pFile, L"%zd", &iFrameCount);

			for (size_t i = 0; i < iFrameCount; ++i)
			{
				tAnimFrm frm = {};

				while (true)
				{
					wchar_t szBuffer[256] = {};
					fwscanf_s(pFile, L"%s", szBuffer, 256);

					if (!wcscmp(szBuffer, L"[LEFT_TOP]"))
					{
						fwscanf_s(pFile, L"%f %f", &frm.vLeftTop.x, &frm.vLeftTop.y);
					}

					else if (!wcscmp(szBuffer, L"[SIZE]"))
					{
						fwscanf_s(pFile, L"%f %f", &frm.vSize.x, &frm.vSize.y);
					}

					else if (!wcscmp(szBuffer, L"[OFFSET]"))
					{
						fwscanf_s(pFile, L"%f %f", &frm.vOffset.x, &frm.vOffset.y);
					}

					else if (!wcscmp(szBuffer, L"[DURATION]"))
					{
						fwscanf_s(pFile, L"%f", &frm.fDuration);
						
					}
					else if (!wcscmp(szBuffer, L"[SPACE]"))
					{
						fwscanf_s(pFile, L"%f %f", &frm.vSpace.x, &frm.vSpace.y);
						break;
					}
				}

				m_vecFrm.push_back(frm);
			}

			break;
		}
	}

	m_pAtlas = CResMgr::GetInst()->LoadTexture(strAtlasKey, strAltasRelativePath);

	fclose(pFile);
}
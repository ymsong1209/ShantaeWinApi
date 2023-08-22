#include "pch.h"
#include "CLevel.h"
#include "CObj.h"
#include "CTile.h"
#include "CPlatform.h"
#include "CEngine.h"
#include "CCamera.h"
#include "CPlatform.h"
#include "CWall.h"
#include "CCeiling.h"
#include "CBackground.h"
#include "CPathMgr.h"
#include "CResMgr.h"

CLevel::CLevel()
	: m_iTileXCount(0)
	, m_iTileYCount(0)
{
}

CLevel::~CLevel()
{
	// ������Ʈ ����
	DeleteAllObject();
}

void CLevel::tick()
{
	//���� ȭ�� ���� �ִ� tile��������
	FindTileScreen();

	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		//Tile�߿��� ȭ�� ���� �ִ� Tile�� tick
		if (i == (UINT)LAYER::TILE)
		{
			for (size_t j = 0; j < m_vecTile.size(); ++j)
			{
				m_vecTile[j]->tick();
			}
		}

		else
		{
			for (UINT j = 0; j < m_arrLayer[i].size(); ++j)
			{
				m_arrLayer[i][j]->tick();
			}
		}
	}
}

void CLevel::final_tick()
{
	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		if (i == (UINT)LAYER::TILE)
		{
			for (size_t j = 0; j < m_vecTile.size(); ++j)
			{
				m_vecTile[j]->final_tick();
			}
		}
		else
		{
			for (UINT j = 0; j < m_arrLayer[i].size(); ++j)
			{
				m_arrLayer[i][j]->final_tick();
			}
		}
	}
}

void CLevel::render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		if (i == (UINT)LAYER::TILE)
		{
			for (size_t j = 0; j < m_vecTile.size(); ++j)
			{
				m_vecTile[j]->render(_dc);
			}
		}
		else
		{
			vector<CObj*>::iterator iter = m_arrLayer[i].begin();

			for (; iter != m_arrLayer[i].end();)
			{
				if ((*iter)->IsDead())
				{
					iter = m_arrLayer[i].erase(iter);
				}
				else
				{
					(*iter)->render(_dc);
					++iter;
				}
			}
		}
	}
}


void CLevel::DeleteAllObject()
{
	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		for (UINT j = 0; j < m_arrLayer[i].size(); ++j)
		{
			if (m_arrLayer[i][j]->IsDead())
				continue;

			DEL(m_arrLayer[i][j]);
		}

		// �����Ҵ� ������Ų �ּҰ����� ���ͳ����� �������
		m_arrLayer[i].clear();
	}
}


void CLevel::ReleaseIsChosen()
{
	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		for (UINT j = 0; j < m_arrLayer[i].size(); ++j)
		{
			if (m_arrLayer[i][j]->IsDead())
				continue;

			m_arrLayer[i][j]->SetChosen(false);
		}
	}
}
void CLevel::DeleteObject(LAYER _eLayer)
{
	for (size_t i = 0; i < m_arrLayer[(UINT)_eLayer].size(); ++i) {
		delete m_arrLayer[(UINT)_eLayer][i];
	}
	m_arrLayer[(UINT)_eLayer].clear();
}



void CLevel::CreateTile(UINT _X, UINT _Y)
{
	//���� Ÿ�� ��� ����
	DeleteObject(LAYER::TILE);

	m_iTileXCount = _X;
	m_iTileYCount = _Y;

	//������ ���� ���� ���ڿ� ���߾� Ÿ�� ��ġ
	for (UINT iRow = 0; iRow < m_iTileYCount; ++iRow) {
		for (UINT iCol = 0; iCol < m_iTileXCount; ++iCol)
		{
			CTile* pTile = new CTile;
			pTile->SetPos(Vec2((float)(TILE_SIZE * iCol), (float)(TILE_SIZE * iRow)));
			AddObject(pTile,LAYER::TILE);
		}
	}

}

void CLevel::CreatePlatform(int _PlatformCount)
{
	//���� �÷��� ��� ����
	DeleteObject(LAYER::PLATFORM);
	
	//�÷��� �� ��ŭ defualt �÷��� �����
	for (int i = 0; i < _PlatformCount; ++i) {
		CPlatform* pPlatform = new CPlatform;
		AddObject(pPlatform, LAYER::PLATFORM);
	}
}
void CLevel::CreateWall(int _WallCount)
{
	//���� Wall ��� ����
	DeleteObject(LAYER::WALL);

	//�÷��� �� ��ŭ defualt �÷��� �����
	for (int i = 0; i < _WallCount; ++i) {
		CWall* pWall = new CWall;
		AddObject(pWall, LAYER::WALL);
	}
}
void CLevel::CreateCeiling(int _CeilingCount)
{
	//���� Ceiling ��� ����
	DeleteObject(LAYER::CEILING);

	//�÷��� �� ��ŭ defualt �÷��� �����
	for (int i = 0; i < _CeilingCount; ++i) {
		CCeiling* pCeiling = new CCeiling;
		AddObject(pCeiling, LAYER::CEILING);
	}
}
void CLevel::SetFocusedUI(CObj* _pUI)
{
	vector<CObj*>& vecUI = m_arrLayer[(UINT)LAYER::UI];

	if (vecUI.back() == _pUI)
		return;

	vector<CObj*>::iterator iter = vecUI.begin();
	for (; iter != vecUI.end(); ++iter)
	{
		if ((*iter) == _pUI)
		{
			vecUI.erase(iter);
			vecUI.push_back(_pUI);
			return;
		}
	}

	// Focused ó���� UI �� ������ ������?!?!?!?
	assert(nullptr);
}

void CLevel::LoadBackground(const wstring& _strKey, const wstring& _strRelativePath, Vec2 _vSize)
{
	DeleteObject(LAYER::BACKGROUND);
	CTexture* backgroundtex = CResMgr::GetInst()->LoadTexture(_strKey, _strRelativePath);
	CObj* background = new CBackground(backgroundtex, _vSize);
	AddObject(background, LAYER::BACKGROUND);
}

void CLevel::LoadPlatform(const wstring& _strRelativePath)
{
	wstring strFilepath = CPathMgr::GetInst()->GetContentPath();
	strFilepath += _strRelativePath;

	// ���� �����
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilepath.c_str(), L"rb");

	//�÷��� ���� �б�
	int platformCount = 0;
	wchar_t szBuffer[256] = {};
	fwscanf_s(pFile, L"%s", szBuffer, 256);
	if (!wcscmp(szBuffer, L"[PLATFORM_COUNT]"))
	{
		fwscanf_s(pFile, L"%d", &platformCount);
	}


	// ���� ������ �°� �ٽ� �÷��� ��ġ
	CreatePlatform(platformCount);


	// ��ġ�� ������ �÷����� ������ �е���
	const vector<CObj*>& vecTile = GetLayer(LAYER::PLATFORM);
	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CPlatform*)vecTile[i])->Load(pFile, i);
	}

	fclose(pFile);
}

void CLevel::LoadWall(const wstring& _strRelativePath)
{
	wstring strFilepath = CPathMgr::GetInst()->GetContentPath();
	strFilepath += _strRelativePath;

	// ���� �����
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilepath.c_str(), L"rb");

	//�÷��� ���� �б�
	int wallCount = 0;
	wchar_t szBuffer[256] = {};
	fwscanf_s(pFile, L"%s", szBuffer, 256);
	if (!wcscmp(szBuffer, L"[WALL_COUNT]"))
	{
		fwscanf_s(pFile, L"%d", &wallCount);
	}


	// ���� ������ �°� �ٽ� �÷��� ��ġ
	CreateWall(wallCount);


	// ��ġ�� ������ �÷����� ������ �е���
	const vector<CObj*>& vecWall = GetLayer(LAYER::WALL);
	for (size_t i = 0; i < vecWall.size(); ++i)
	{
		((CWall*)vecWall[i])->Load(pFile, i);
	}

	fclose(pFile);
}

void CLevel::LoadCeiling(const wstring& _strRelativePath)
{
	wstring strFilepath = CPathMgr::GetInst()->GetContentPath();
	strFilepath += _strRelativePath;

	// ���� �����
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilepath.c_str(), L"rb");

	//�÷��� ���� �б�
	int platformCount = 0;
	wchar_t szBuffer[256] = {};
	fwscanf_s(pFile, L"%s", szBuffer, 256);
	if (!wcscmp(szBuffer, L"[CEILING_COUNT]"))
	{
		fwscanf_s(pFile, L"%d", &platformCount);
	}


	// ���� ������ �°� �ٽ� �÷��� ��ġ
	CreateCeiling(platformCount);


	// ��ġ�� ������ �÷����� ������ �е���
	const vector<CObj*>& vecTile = GetLayer(LAYER::CEILING);
	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CCeiling*)vecTile[i])->Load(pFile, i);
	}

	fclose(pFile);
}


void CLevel::FindTileScreen()
{
	m_vecTile.clear();


	Vec2 vLeftTop = CCamera::GetInst()->GetLook();
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	vLeftTop -= (vResolution / 2.f);

	//LeftTop Col, Row-> Ÿ���� �� ��ǥ/Ÿ���� ũ�� -> Ÿ���� ���޸������� Ȯ�� ����
	int iLTCol = (int)vLeftTop.x / TILE_SIZE;
	int iLTRow = (int)vLeftTop.y / TILE_SIZE;
	//Ÿ���� ������ ������ 0���� �ʱ�ȭ
	if (vLeftTop.x < 0.f)
		iLTCol = 0;
	if (vLeftTop.y < 0.f)
		iLTRow = 0;

	UINT iMaxCol = ((int)vResolution.x / TILE_SIZE) + iLTCol + 1;
	UINT iMaxRow = ((int)vResolution.y / TILE_SIZE) + iLTRow + 1;

	if (m_iTileXCount < iMaxCol)
		iMaxCol = m_iTileXCount;
	if (m_iTileYCount < iMaxRow)
		iMaxRow = m_iTileYCount;

	for (UINT iRow = iLTRow; iRow < iMaxRow; ++iRow)
	{
		for (UINT iCol = iLTCol; iCol < iMaxCol; ++iCol)
		{
			UINT iTileIdx = iRow * m_iTileXCount + iCol;

			m_vecTile.push_back(m_arrLayer[(UINT)LAYER::TILE][iTileIdx]);
		}
	}
}


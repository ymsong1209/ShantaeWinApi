#include "pch.h"
#include "CTile.h"

#include "CResMgr.h"
#include "CTexture.h"

CTile::CTile()
	: m_pAtlas(nullptr)
	, m_iImgIdx(-1)
{
}

CTile::~CTile()
{
}

void CTile::tick()
{

}

void CTile::render(HDC _dc)
{
	if (-1 == m_iImgIdx || m_pAtlas == nullptr)
		return;

	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());
	/*Rectangle(_dc
		, (int)(vPos.x)
		, (int)(vPos.y)
		, (int)(vPos.x + TILE_SIZE)
		, (int)(vPos.y + TILE_SIZE));*/


	int iMaxCol = m_pAtlas->Width() / TILE_SIZE;

	int iCurRow = m_iImgIdx / iMaxCol;
	int iCurCol = m_iImgIdx % iMaxCol;

	BitBlt(_dc
		, (int)vPos.x
		, (int)vPos.y
		, TILE_SIZE, TILE_SIZE
		, m_pAtlas->GetDC()
		, iCurCol * TILE_SIZE
		, iCurRow * TILE_SIZE
		, SRCCOPY);

}



void CTile::SetImgIdx(int _imgidx)
{
	assert(m_pAtlas);

	int iCol = m_pAtlas->Width() / TILE_SIZE;
	int iRow = m_pAtlas->Height() / TILE_SIZE;
	int iImgMaxCount = iCol * iRow;

	assert(!(iImgMaxCount <= _imgidx));

	m_iImgIdx = _imgidx;
}

//���� Ÿ�� ��ȣ ����
void CTile::AddImgIdx()
{
	assert(m_pAtlas);

	int iCol = m_pAtlas->Width() / TILE_SIZE;
	int iRow = m_pAtlas->Height() / TILE_SIZE;
	int iImgMaxCount = iCol * iRow;

	++m_iImgIdx;

	// �ִ� �̹��� �ʰ��ϴ� ���, �ٽ� ó������...
	if (iImgMaxCount <= m_iImgIdx)
	{
		m_iImgIdx = 0;
	}
}

void CTile::Save(FILE* _pFile)
{
	// ��ġ
	Vec2 vPos = GetPos();
	fwrite(&vPos, sizeof(Vec2), 1, _pFile);

	// ��Ʋ�� �̹��� ����
	bool bAtlas = m_pAtlas;
	fwrite(&bAtlas, sizeof(bool), 1, _pFile);

	if (bAtlas)
	{
		// Ű�� ����,
		wstring strKey = m_pAtlas->GetKey();
		SaveWString(strKey, _pFile);

		// ����� ����,
		wstring strRelativePath = m_pAtlas->GetRelativePath();
		SaveWString(strRelativePath, _pFile);
	}

	// �̹��� �ε���
	fwrite(&m_iImgIdx, sizeof(int), 1, _pFile);
}

void CTile::Load(FILE* _pFile)
{
	// ��ġ
	Vec2 vPos;
	fread(&vPos, sizeof(Vec2), 1, _pFile);
	SetPos(vPos);

	// ��Ʋ�� �̹��� ����
	bool bAtlas = false;
	fread(&bAtlas, sizeof(bool), 1, _pFile);

	if (bAtlas)
	{
		//Ű�� �θ���
		wstring strKey;
		LoadWString(strKey, _pFile);
		//����� �θ���
		wstring strRelativePath;
		LoadWString(strRelativePath, _pFile);
		m_pAtlas = CResMgr::GetInst()->LoadTexture(strKey, strRelativePath);
	}

	// �̹��� �ε���
	fread(&m_iImgIdx, sizeof(int), 1, _pFile);
}
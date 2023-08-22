#include "pch.h"
#include "CTexture.h"
#include "CEngine.h"
CTexture::CTexture()
    : m_hBit(nullptr)
    , m_hDC(nullptr)
    , m_tBitmapInfo{}
{
}

CTexture::~CTexture()
{
    DeleteObject(m_hBit);
    DeleteDC(m_hDC);
}



int CTexture::Load(const wstring& _strFilePath)
{
    //Bitmap �ε�
    m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
    GetObject(m_hBit, sizeof(BITMAP), &m_tBitmapInfo);

    // Bitmap �� ���� ��ų DC ����
    m_hDC = CreateCompatibleDC(CEngine::GetInst()->GetMainDC());
    HBITMAP hPrevBit = (HBITMAP)SelectObject(m_hDC, m_hBit);
    DeleteObject(hPrevBit);

    return S_OK;
}

void CTexture::Create(UINT _iWidth, UINT _iHeight)
{	
    //������ ��Ʈ���� ������� ������ �ػ󵵷� ������Ŵ
    //�� ��Ʈ�ʿ� �׸��� �׷� �̰��� ������ ���� �����쿡 ������Ʈ��Ų��.
    //compatible : ȣȯ ������    
    m_hBit = CreateCompatibleBitmap(CEngine::GetInst()->GetMainDC(), _iWidth, _iHeight);

    // ������Ų ��Ʈ���� �������� �ϴ� DC �� ������
    m_hDC = CreateCompatibleDC(CEngine::GetInst()->GetMainDC());
    //selectobject: m_hDC�� m_hBit�ڸ��� nullptr���� �� �Լ����� ���� m_hBit���� ä���ִ´�.
    //��ȯ�ϴ� ���� ���� �ִ� nullptr������ �̰��� HBITMAP���� ĳ�������ش�.
    HBITMAP hPrevBit = (HBITMAP)SelectObject(m_hDC, m_hBit);
    //���� ��ȯ�� hPrevBit�� �����Ѵ�.
    DeleteObject(hPrevBit);

    GetObject(m_hBit, sizeof(BITMAP), &m_tBitmapInfo);
}

//�ؽ����� �ػ󵵸� �ٲٷ��� ������ �ִ� �׸��� �ѹ� �Űܾ��Ѵ�.
void CTexture::Resize(UINT _iWidth, UINT _iHeight)
{
    //���ο� ��Ʈ�ʰ� DC ����
    HBITMAP hnewBitmap = CreateCompatibleBitmap(CEngine::GetInst()->GetMainDC(), _iWidth, _iHeight);
    HDC hNewDC = CreateCompatibleDC(CEngine::GetInst()->GetMainDC());
    HBITMAP hPrevBitmap = (HBITMAP)SelectObject(hNewDC, hnewBitmap);
    DeleteObject(hPrevBitmap);

    //������ �ִ� �׸��� ���ο� ���� ����
    BitBlt(hNewDC, 0, 0, m_tBitmapInfo.bmWidth, m_tBitmapInfo.bmHeight, m_hDC, 0, 0, SRCCOPY);
    //���� bitmap, dc����
    DeleteObject(m_hDC);
    DeleteObject(m_hBit);

    //���ο� bitmap, dc�� ��ü
    m_hDC = hNewDC;
    m_hBit = hnewBitmap;

    //��Ʈ�� ���� ����
    GetObject(m_hBit, sizeof(BITMAP), &m_tBitmapInfo);
}

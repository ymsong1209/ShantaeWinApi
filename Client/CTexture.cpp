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
    //Bitmap 로딩
    m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
    GetObject(m_hBit, sizeof(BITMAP), &m_tBitmapInfo);

    // Bitmap 과 연결 시킬 DC 생성
    m_hDC = CreateCompatibleDC(CEngine::GetInst()->GetMainDC());
    HBITMAP hPrevBit = (HBITMAP)SelectObject(m_hDC, m_hBit);
    DeleteObject(hPrevBit);

    return S_OK;
}

void CTexture::Create(UINT _iWidth, UINT _iHeight)
{	
    //별도의 비트맵을 윈도우와 동일한 해상도로 생성시킴
    //이 비트맵에 그림을 그려 이것을 복사해 메인 윈도우에 업데이트시킨다.
    //compatible : 호환 가능한    
    m_hBit = CreateCompatibleBitmap(CEngine::GetInst()->GetMainDC(), _iWidth, _iHeight);

    // 생성시킨 비트맵을 목적지로 하는 DC 를 생성함
    m_hDC = CreateCompatibleDC(CEngine::GetInst()->GetMainDC());
    //selectobject: m_hDC의 m_hBit자리를 nullptr에서 이 함수에서 만든 m_hBit으로 채워넣는다.
    //반환하는 것은 원래 있던 nullptr이지만 이것을 HBITMAP으로 캐스팅해준다.
    HBITMAP hPrevBit = (HBITMAP)SelectObject(m_hDC, m_hBit);
    //이후 반환된 hPrevBit을 제거한다.
    DeleteObject(hPrevBit);

    GetObject(m_hBit, sizeof(BITMAP), &m_tBitmapInfo);
}

//텍스쳐의 해상도를 바꾸려면 기존에 있던 그림을 한번 옮겨야한다.
void CTexture::Resize(UINT _iWidth, UINT _iHeight)
{
    //새로운 비트맵과 DC 생성
    HBITMAP hnewBitmap = CreateCompatibleBitmap(CEngine::GetInst()->GetMainDC(), _iWidth, _iHeight);
    HDC hNewDC = CreateCompatibleDC(CEngine::GetInst()->GetMainDC());
    HBITMAP hPrevBitmap = (HBITMAP)SelectObject(hNewDC, hnewBitmap);
    DeleteObject(hPrevBitmap);

    //기존에 있던 그림을 새로운 곳에 복사
    BitBlt(hNewDC, 0, 0, m_tBitmapInfo.bmWidth, m_tBitmapInfo.bmHeight, m_hDC, 0, 0, SRCCOPY);
    //기존 bitmap, dc삭제
    DeleteObject(m_hDC);
    DeleteObject(m_hBit);

    //새로운 bitmap, dc로 대체
    m_hDC = hNewDC;
    m_hBit = hnewBitmap;

    //비트맵 정보 갱신
    GetObject(m_hBit, sizeof(BITMAP), &m_tBitmapInfo);
}

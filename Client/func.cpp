#include "pch.h"
#include "func.h"

#include "CEventMgr.h"
#include "CObj.h"

#include "CAnimation.h"
#include "CAnimator.h"

bool IsValid(CObj*& _pTarget)
{
    if (nullptr == _pTarget || _pTarget->IsDead())
    {
        _pTarget = nullptr;
        return false;
    }

    return true;
}
void Instantiate(CObj* _pNewObj, Vec2 _vPos, LAYER _eLayer)
{
    _pNewObj->SetPos(_vPos);

    tEvent _evn = {};
    _evn.eType = EVENT_TYPE::CREATE_OBJECT;
    _evn.wParam = (DWORD_PTR)_pNewObj;
    _evn.lParam = (DWORD_PTR)_eLayer;

    CEventMgr::GetInst()->AddEvent(_evn);
}
void ChangeLevel(LEVEL_TYPE _eNextLevel)
{
    tEvent _evn = {};
    _evn.eType = EVENT_TYPE::LEVEL_CHANGE;
    _evn.wParam = (DWORD_PTR)_eNextLevel;
    CEventMgr::GetInst()->AddEvent(_evn);
}

void Saturate(float& _float)
{
    if (1.f < _float)
        _float = 1.f;
    if (_float < 0.f)
        _float = 0.f;
}

//포인터를 저장하는것이 아닌, 메모리 주소에 저장되어 있는 값을 저장하고싶다.
//즉, 시작 주소로부터 갯수만큼 그대로 복사해야한다.
void SaveWString(const wstring& _str, FILE* _pFile)
{
    size_t iLen = _str.length();
    fwrite(&iLen, sizeof(size_t), 1, _pFile);
    fwrite(_str.c_str(), sizeof(wchar_t), iLen, _pFile);
}

void LoadWString(wstring& _str, FILE* _pFile)
{
    size_t iLen = 0;
    fread(&iLen, sizeof(size_t), 1, _pFile);

    wchar_t szBuff[256] = {};
    fread(szBuff, sizeof(wchar_t), iLen, _pFile);
    _str = szBuff;
}


int ccw(Vec2 A, Vec2 B, Vec2 C) {
    int result = (int)((B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x));
    if (result > 0) return 1;
    else if (result == 0) return 0;
    else return -1;
}

int relation(Vec2 A, Vec2 B, Vec2 C, Vec2 D) {

    int line1_2 = ccw(A, B, C) * ccw(A, B, D);
    int line2_1 = ccw(C, D, A) * ccw(C, D, B);

    // 4개의 점이 모두 한 직선위에 존재하는 경우
    if (line1_2 == 0 && line2_1 == 0) {
        if (A.x > B.x || A.y > B.y) {
            std::swap(A, B);
        }
        if (C.x > D.x || C.y > D.y) {
            std::swap(C, D);
        }

        // 만나지 않는 경우 : 관계 1
        //if ((B < C) || (D < A)) return 1;
        if ((B.x < C.x) || (B.y) < (C.y) || (D.x < A.x) || (D.y < A.y)) return 1;

        // 한 점에서 만나는 경우 : 관계 2
        //if ((A < C && B == C) || (C < A && D == A)) return 2;
        if (
            ((A.x < C.x || A.y < C.y) && (B.x==C.x&&B.y==C.y)) || ((C.x<A.x||C.y<A.y) && (D.x==A.x&&D.y==A.y))
           ) return 2;
       
        // 두 선분의 일부가 겹치는 경우 : 관계 3
        //if ((A < C && C < B && B < D) || (C < A && A < D && D < B)) return 3;
        if (
            ((A.x < C.x || A.y < B.y) && (C.x < B.x || C.y < B.y) && (B.x < D.x || B.y < D.y)) ||
            ((C.x < A.x || C.y < A.y) && (A.x < D.x || A.y < D.y) && (D.x < B.x || D.y < B.y))
            ) return 3;
       
        // 한 선분이 다른 선분에 포함 됨
        // 여기 등호 꼭 넣어줘야 함 !! 이것 때문에 엄청 헤맸음 !!
        //if ((A <= C && D <= B) || (C <= A && B <= D)) return 4;
        if (
            ((A.x <= C.x || A.y <= C.y) && (D.x <= B.x || D.y <= B.y)) ||
            ((C.x <= A.x || C.y <= A.y) && (B.x <= D.x || B.y <= D.y))
            )return 4;
        

    }

    // 모두 그렇지는 않은 경우
    if (line1_2 <= 0 && line2_1 <= 0) return 2;
    else return 1;
}
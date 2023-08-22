#pragma once
#include "CObj.h"
class CCeiling :
    public CObj
{
public:
    virtual void BeginOverlap(CCollider* _pOther);
    virtual void OnOverlap(CCollider* _pOther);
    virtual void EndOverlap(CCollider* _pOther);

    virtual void render(HDC _dc);

    void Save(FILE* _pFile);
    void Load(FILE* _pFile, int _PlatformCount);

    CLONE(CCeiling);
public:
    CCeiling();
    ~CCeiling();
};


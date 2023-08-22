#pragma once
#include "CObj.h"
class CPlatform :
    public CObj
{
private:
    /*Vec2 m_vLeftTop;
    Vec2 m_vRightTop;
    Vec2 m_vLeftBottom;
    Vec2 m_vRightBottom;*/

public:
    virtual void BeginOverlap(CCollider* _pOther);
    virtual void OnOverlap(CCollider* _pOther);
    virtual void EndOverlap(CCollider* _pOther);

    virtual void render(HDC _dc);
    
    void Save(FILE* _pFile);
    void Load(FILE* _pFile, int _PlatformCount);

    CLONE(CPlatform);
public:
    CPlatform();
    ~CPlatform();
};


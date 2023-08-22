#pragma once
#include "CObj.h"
class CCameraBlock :
    public CObj
{
private:
    //CCamera* CCamera;
public:
    virtual void BeginOverlap(CCollider* _pOther);
    virtual void OnOverlap(CCollider* _pOther);
    virtual void EndOverlap(CCollider* _pOther);


    CLONE(CCameraBlock);
public:
    CCameraBlock();
    ~CCameraBlock();

};


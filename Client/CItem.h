#pragma once
#include "CObj.h"
class CItem :
    public CObj
{

private:
    virtual void tick() override;
    virtual void render(HDC _dc) override;
    virtual void BeginOverlap(CCollider* _pOther) override;

public:


public:
    CLONE(CItem);
public:
    CItem();
    ~CItem();


};


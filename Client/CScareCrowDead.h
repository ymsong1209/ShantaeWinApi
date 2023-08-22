#pragma once
#include "CObj.h"
class CScareCrow;
class CSound;
class CScareCrowDead :
    public CObj
{
public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;
    bool        IsLeft;
    CSound* m_sDeath;
public:
    CLONE(CScareCrowDead);
public:

    CScareCrowDead(CScareCrow* _pOwner);
    ~CScareCrowDead();

};


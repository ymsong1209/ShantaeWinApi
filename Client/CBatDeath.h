#pragma once
#include "CObj.h"
class CBat;
class CSound;
class CBatDeath :
    public CObj
{
public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;
    bool        IsLeft;
    CSound* m_sDeath;

public:
    CLONE(CBatDeath);
public:

    CBatDeath(CBat* _pOwner);
    ~CBatDeath();

};


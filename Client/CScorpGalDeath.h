#pragma once
#include "CObj.h"
class CScorpGal;
class CScorpGalDeath :
    public CObj
{
public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;
    bool        IsLeft;

public:
    CLONE(CScorpGalDeath);
public:

    CScorpGalDeath(CScorpGal* _pOwner);
    ~CScorpGalDeath();

};


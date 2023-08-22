#pragma once
#include "CObj.h"
class CCactus;
class CCactusDeath :
    public CObj
{
public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;
    bool        IsLeft;

public:
    CLONE(CCactusDeath);
public:

    CCactusDeath(CCactus* _pOwner);
    ~CCactusDeath();
};


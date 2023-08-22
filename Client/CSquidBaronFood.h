#pragma once
#include "CObj.h"
class CSquidBaron;
class CSquidBaronFood :
    public CObj
{
private:
    CSquidBaron* m_pOwner;
    CTexture*  m_pAtlas;
public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;
   

public:
    CLONE(CSquidBaronFood);
public:

    CSquidBaronFood(CSquidBaron* _pOwner);
    ~CSquidBaronFood();
};

